// Copyright Nezametdinov E. Ildus 2022.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)
//
#ifndef H_488DC17251AA4A0D8D8B3994795442DA
#define H_488DC17251AA4A0D8D8B3994795442DA

#include <climits>
#include <concepts>

#include <utility>
#include <tuple>
#include <type_traits>

namespace mirror {

////////////////////////////////////////////////////////////////////////////////
// A concept that models types which can be reflected.
////////////////////////////////////////////////////////////////////////////////

// clang-format off
template <typename T>
concept reflexible =
    (std::is_aggregate_v<T> && std::default_initializable<T>) &&
    (std::copy_constructible<T> || std::move_constructible<T>);
// clang-format on

////////////////////////////////////////////////////////////////////////////////
// Non-static data member counting.
////////////////////////////////////////////////////////////////////////////////

namespace detail {

// Special type which is convertible to any other type, except for possibly
// cv-qualified versions of itself and corresponding reference types.
template <typename T, std::size_t I>
struct universal {
    template <typename U>
    operator U() const noexcept
        requires(!std::same_as<T, std::remove_cvref_t<U>>);
};

// A concept for a type which is constructible with a sequence of arguments. The
// size of the sequence is the same as the size of the non-type template
// parameter pack.
template <typename T, std::size_t... Indices>
concept constructible_from = requires {
    T{std::declval<universal<T, Indices>>()...};
};

// A predicate which shows if the given type is constructible with the given
// number of arguments.
//
// clang-format off
template <typename T, std::size_t N>
constexpr auto
is_constructible =
    []<std::size_t... Indices>(std::index_sequence<Indices...>) {
        return constructible_from<T, Indices...>;
    }(std::make_index_sequence<N>{});
// clang-format on

// A median between two values.
template <std::size_t L, std::size_t R>
constexpr auto median = ((L / 2) + (R / 2) + ((1 + (L % 2) + (R % 2)) / 2));

// Performs compile-time binary search.
template <typename T, std::size_t L, std::size_t M, std::size_t R>
constexpr auto
bisect() noexcept -> std::size_t {
    if constexpr(L == R) {
        return L;
    } else {
        if constexpr(is_constructible<T, M>) {
            return bisect<T, M, median<M, R>, R>();
        } else {
            return bisect<T, L, median<L, M - 1>, M - 1>();
        }
    }
}

// Counts the number of non-static data members in the given type.
template <typename T>
constexpr auto
count_data_members() noexcept {
    // Compute the size of the type in bits. This will be the upper bound for
    // binary search.
    constexpr auto bit_size = std::size_t{sizeof(T) * CHAR_BIT};
    static_assert(bit_size / sizeof(T) == CHAR_BIT);

    // Run binary search.
    return bisect<T, 0, median<0, bit_size>, bit_size>();
}

} // namespace detail

// Count of the non-static data members in the given type.
template <reflexible T>
constexpr auto data_member_count = detail::count_data_members<T>();

////////////////////////////////////////////////////////////////////////////////
// Tuple construction.
////////////////////////////////////////////////////////////////////////////////

// Returns a tuple of references to non-static data members of the given object.
template <reflexible T>
constexpr auto
reflect(T& x) noexcept
    -> decltype(auto) requires(data_member_count<T> <= (@limit@)) {
    if constexpr(data_member_count<T> == 0) {
        return std::tuple<>{};
    } (@generate_specializations@)
}

} // namespace mirror

#endif // H_488DC17251AA4A0D8D8B3994795442DA
