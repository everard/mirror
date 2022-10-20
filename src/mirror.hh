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
reflect(T& x) noexcept -> decltype(auto) requires(data_member_count<T> <= 127) {
    if constexpr(data_member_count<T> == 0) {
        return std::tuple<>{};
    } else if constexpr(data_member_count<T> == 1) {
        // Obtain references to member objects using structural bindings.
        auto& [e00] = x;

        // Construct a tuple from these references.
        return std::tie(e00);
    } else if constexpr(data_member_count<T> == 2) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01);
    } else if constexpr(data_member_count<T> == 3) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02);
    } else if constexpr(data_member_count<T> == 4) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03);
    } else if constexpr(data_member_count<T> == 5) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04);
    } else if constexpr(data_member_count<T> == 6) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05);
    } else if constexpr(data_member_count<T> == 7) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06);
    } else if constexpr(data_member_count<T> == 8) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07);
    } else if constexpr(data_member_count<T> == 9) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08);
    } else if constexpr(data_member_count<T> == 10) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09);
    } else if constexpr(data_member_count<T> == 11) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A);
    } else if constexpr(data_member_count<T> == 12) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B] = x;

        // Construct a tuple from these references.
        return std::tie(
            e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B);
    } else if constexpr(data_member_count<T> == 13) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B,
               e0C] = x;

        // Construct a tuple from these references.
        return std::tie(
            e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C);
    } else if constexpr(data_member_count<T> == 14) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D);
    } else if constexpr(data_member_count<T> == 15) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E);
    } else if constexpr(data_member_count<T> == 16) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F);
    } else if constexpr(data_member_count<T> == 17) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10);
    } else if constexpr(data_member_count<T> == 18) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11);
    } else if constexpr(data_member_count<T> == 19) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12);
    } else if constexpr(data_member_count<T> == 20) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13);
    } else if constexpr(data_member_count<T> == 21) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14);
    } else if constexpr(data_member_count<T> == 22) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15);
    } else if constexpr(data_member_count<T> == 23) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16);
    } else if constexpr(data_member_count<T> == 24) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17);
    } else if constexpr(data_member_count<T> == 25) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18);
    } else if constexpr(data_member_count<T> == 26) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18,
               e19] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19);
    } else if constexpr(data_member_count<T> == 27) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A);
    } else if constexpr(data_member_count<T> == 28) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B);
    } else if constexpr(data_member_count<T> == 29) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C);
    } else if constexpr(data_member_count<T> == 30) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D);
    } else if constexpr(data_member_count<T> == 31) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E);
    } else if constexpr(data_member_count<T> == 32) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F);
    } else if constexpr(data_member_count<T> == 33) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20);
    } else if constexpr(data_member_count<T> == 34) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21);
    } else if constexpr(data_member_count<T> == 35) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22);
    } else if constexpr(data_member_count<T> == 36) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23);
    } else if constexpr(data_member_count<T> == 37) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24);
    } else if constexpr(data_member_count<T> == 38) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25);
    } else if constexpr(data_member_count<T> == 39) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25,
               e26] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26);
    } else if constexpr(data_member_count<T> == 40) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27);
    } else if constexpr(data_member_count<T> == 41) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28);
    } else if constexpr(data_member_count<T> == 42) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29);
    } else if constexpr(data_member_count<T> == 43) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A);
    } else if constexpr(data_member_count<T> == 44) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B);
    } else if constexpr(data_member_count<T> == 45) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C);
    } else if constexpr(data_member_count<T> == 46) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D);
    } else if constexpr(data_member_count<T> == 47) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E);
    } else if constexpr(data_member_count<T> == 48) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F);
    } else if constexpr(data_member_count<T> == 49) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30);
    } else if constexpr(data_member_count<T> == 50) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31);
    } else if constexpr(data_member_count<T> == 51) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32);
    } else if constexpr(data_member_count<T> == 52) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32,
               e33] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33);
    } else if constexpr(data_member_count<T> == 53) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34);
    } else if constexpr(data_member_count<T> == 54) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35);
    } else if constexpr(data_member_count<T> == 55) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36);
    } else if constexpr(data_member_count<T> == 56) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37);
    } else if constexpr(data_member_count<T> == 57) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38);
    } else if constexpr(data_member_count<T> == 58) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39);
    } else if constexpr(data_member_count<T> == 59) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A);
    } else if constexpr(data_member_count<T> == 60) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B);
    } else if constexpr(data_member_count<T> == 61) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C);
    } else if constexpr(data_member_count<T> == 62) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D);
    } else if constexpr(data_member_count<T> == 63) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E);
    } else if constexpr(data_member_count<T> == 64) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F);
    } else if constexpr(data_member_count<T> == 65) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F,
               e40] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40);
    } else if constexpr(data_member_count<T> == 66) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41);
    } else if constexpr(data_member_count<T> == 67) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42);
    } else if constexpr(data_member_count<T> == 68) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43);
    } else if constexpr(data_member_count<T> == 69) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44);
    } else if constexpr(data_member_count<T> == 70) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44, e45);
    } else if constexpr(data_member_count<T> == 71) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44, e45, e46);
    } else if constexpr(data_member_count<T> == 72) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44, e45, e46, e47);
    } else if constexpr(data_member_count<T> == 73) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44, e45, e46, e47, e48);
    } else if constexpr(data_member_count<T> == 74) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44, e45, e46, e47, e48, e49);
    } else if constexpr(data_member_count<T> == 75) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44, e45, e46, e47, e48, e49, e4A);
    } else if constexpr(data_member_count<T> == 76) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B);
    } else if constexpr(data_member_count<T> == 77) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C);
    } else if constexpr(data_member_count<T> == 78) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C,
               e4D] = x;

        // Construct a tuple from these references.
        return std::tie(
            e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
            e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
            e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
            e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
            e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
            e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D);
    } else if constexpr(data_member_count<T> == 79) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C,
                        e4D, e4E);
    } else if constexpr(data_member_count<T> == 80) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C,
                        e4D, e4E, e4F);
    } else if constexpr(data_member_count<T> == 81) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C,
                        e4D, e4E, e4F, e50);
    } else if constexpr(data_member_count<T> == 82) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C,
                        e4D, e4E, e4F, e50, e51);
    } else if constexpr(data_member_count<T> == 83) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C,
                        e4D, e4E, e4F, e50, e51, e52);
    } else if constexpr(data_member_count<T> == 84) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C,
                        e4D, e4E, e4F, e50, e51, e52, e53);
    } else if constexpr(data_member_count<T> == 85) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C,
                        e4D, e4E, e4F, e50, e51, e52, e53, e54);
    } else if constexpr(data_member_count<T> == 86) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C,
                        e4D, e4E, e4F, e50, e51, e52, e53, e54, e55);
    } else if constexpr(data_member_count<T> == 87) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C,
                        e4D, e4E, e4F, e50, e51, e52, e53, e54, e55, e56);
    } else if constexpr(data_member_count<T> == 88) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C,
                        e4D, e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57);
    } else if constexpr(data_member_count<T> == 89) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58] = x;

        // Construct a tuple from these references.
        return std::tie(
            e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
            e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
            e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
            e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
            e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
            e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
            e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58);
    } else if constexpr(data_member_count<T> == 90) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59] = x;

        // Construct a tuple from these references.
        return std::tie(
            e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
            e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
            e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
            e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
            e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
            e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
            e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59);
    } else if constexpr(data_member_count<T> == 91) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59,
               e5A] = x;

        // Construct a tuple from these references.
        return std::tie(
            e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
            e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
            e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
            e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
            e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
            e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
            e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A);
    } else if constexpr(data_member_count<T> == 92) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
               e5B] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C,
                        e4D, e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57,
                        e58, e59, e5A, e5B);
    } else if constexpr(data_member_count<T> == 93) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
               e5B, e5C] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C,
                        e4D, e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57,
                        e58, e59, e5A, e5B, e5C);
    } else if constexpr(data_member_count<T> == 94) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
               e5B, e5C, e5D] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C,
                        e4D, e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57,
                        e58, e59, e5A, e5B, e5C, e5D);
    } else if constexpr(data_member_count<T> == 95) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
               e5B, e5C, e5D, e5E] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C,
                        e4D, e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57,
                        e58, e59, e5A, e5B, e5C, e5D, e5E);
    } else if constexpr(data_member_count<T> == 96) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
               e5B, e5C, e5D, e5E, e5F] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C,
                        e4D, e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57,
                        e58, e59, e5A, e5B, e5C, e5D, e5E, e5F);
    } else if constexpr(data_member_count<T> == 97) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
               e5B, e5C, e5D, e5E, e5F, e60] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C,
                        e4D, e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57,
                        e58, e59, e5A, e5B, e5C, e5D, e5E, e5F, e60);
    } else if constexpr(data_member_count<T> == 98) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
               e5B, e5C, e5D, e5E, e5F, e60, e61] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C,
                        e4D, e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57,
                        e58, e59, e5A, e5B, e5C, e5D, e5E, e5F, e60, e61);
    } else if constexpr(data_member_count<T> == 99) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
               e5B, e5C, e5D, e5E, e5F, e60, e61, e62] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C,
                        e4D, e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57,
                        e58, e59, e5A, e5B, e5C, e5D, e5E, e5F, e60, e61, e62);
    } else if constexpr(data_member_count<T> == 100) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
               e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63] = x;

        // Construct a tuple from these references.
        return std::tie(
            e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
            e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
            e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
            e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
            e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
            e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
            e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
            e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63);
    } else if constexpr(data_member_count<T> == 101) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
               e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64] = x;

        // Construct a tuple from these references.
        return std::tie(
            e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
            e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
            e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
            e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
            e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
            e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
            e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
            e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64);
    } else if constexpr(data_member_count<T> == 102) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
               e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65] = x;

        // Construct a tuple from these references.
        return std::tie(
            e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
            e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
            e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
            e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
            e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
            e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
            e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
            e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65);
    } else if constexpr(data_member_count<T> == 103) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
               e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66] = x;

        // Construct a tuple from these references.
        return std::tie(
            e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
            e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
            e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
            e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
            e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
            e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
            e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
            e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66);
    } else if constexpr(data_member_count<T> == 104) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
               e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66,
               e67] = x;

        // Construct a tuple from these references.
        return std::tie(
            e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
            e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
            e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
            e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
            e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
            e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
            e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
            e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67);
    } else if constexpr(data_member_count<T> == 105) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
               e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67,
               e68] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C,
                        e4D, e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57,
                        e58, e59, e5A, e5B, e5C, e5D, e5E, e5F, e60, e61, e62,
                        e63, e64, e65, e66, e67, e68);
    } else if constexpr(data_member_count<T> == 106) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
               e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67,
               e68, e69] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C,
                        e4D, e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57,
                        e58, e59, e5A, e5B, e5C, e5D, e5E, e5F, e60, e61, e62,
                        e63, e64, e65, e66, e67, e68, e69);
    } else if constexpr(data_member_count<T> == 107) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
               e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67,
               e68, e69, e6A] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C,
                        e4D, e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57,
                        e58, e59, e5A, e5B, e5C, e5D, e5E, e5F, e60, e61, e62,
                        e63, e64, e65, e66, e67, e68, e69, e6A);
    } else if constexpr(data_member_count<T> == 108) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
               e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67,
               e68, e69, e6A, e6B] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C,
                        e4D, e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57,
                        e58, e59, e5A, e5B, e5C, e5D, e5E, e5F, e60, e61, e62,
                        e63, e64, e65, e66, e67, e68, e69, e6A, e6B);
    } else if constexpr(data_member_count<T> == 109) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
               e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67,
               e68, e69, e6A, e6B, e6C] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C,
                        e4D, e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57,
                        e58, e59, e5A, e5B, e5C, e5D, e5E, e5F, e60, e61, e62,
                        e63, e64, e65, e66, e67, e68, e69, e6A, e6B, e6C);
    } else if constexpr(data_member_count<T> == 110) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
               e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67,
               e68, e69, e6A, e6B, e6C, e6D] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C,
                        e4D, e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57,
                        e58, e59, e5A, e5B, e5C, e5D, e5E, e5F, e60, e61, e62,
                        e63, e64, e65, e66, e67, e68, e69, e6A, e6B, e6C, e6D);
    } else if constexpr(data_member_count<T> == 111) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
               e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67,
               e68, e69, e6A, e6B, e6C, e6D, e6E] = x;

        // Construct a tuple from these references.
        return std::tie(
            e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
            e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
            e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
            e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
            e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
            e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
            e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
            e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67,
            e68, e69, e6A, e6B, e6C, e6D, e6E);
    } else if constexpr(data_member_count<T> == 112) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
               e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67,
               e68, e69, e6A, e6B, e6C, e6D, e6E, e6F] = x;

        // Construct a tuple from these references.
        return std::tie(
            e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
            e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
            e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
            e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
            e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
            e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
            e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
            e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67,
            e68, e69, e6A, e6B, e6C, e6D, e6E, e6F);
    } else if constexpr(data_member_count<T> == 113) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
               e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67,
               e68, e69, e6A, e6B, e6C, e6D, e6E, e6F, e70] = x;

        // Construct a tuple from these references.
        return std::tie(
            e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
            e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
            e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
            e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
            e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
            e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
            e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
            e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67,
            e68, e69, e6A, e6B, e6C, e6D, e6E, e6F, e70);
    } else if constexpr(data_member_count<T> == 114) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
               e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67,
               e68, e69, e6A, e6B, e6C, e6D, e6E, e6F, e70, e71] = x;

        // Construct a tuple from these references.
        return std::tie(
            e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
            e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
            e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
            e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
            e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
            e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
            e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
            e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67,
            e68, e69, e6A, e6B, e6C, e6D, e6E, e6F, e70, e71);
    } else if constexpr(data_member_count<T> == 115) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
               e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67,
               e68, e69, e6A, e6B, e6C, e6D, e6E, e6F, e70, e71, e72] = x;

        // Construct a tuple from these references.
        return std::tie(
            e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
            e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
            e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
            e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
            e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
            e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
            e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
            e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67,
            e68, e69, e6A, e6B, e6C, e6D, e6E, e6F, e70, e71, e72);
    } else if constexpr(data_member_count<T> == 116) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
               e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67,
               e68, e69, e6A, e6B, e6C, e6D, e6E, e6F, e70, e71, e72, e73] = x;

        // Construct a tuple from these references.
        return std::tie(
            e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
            e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
            e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
            e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
            e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
            e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
            e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
            e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67,
            e68, e69, e6A, e6B, e6C, e6D, e6E, e6F, e70, e71, e72, e73);
    } else if constexpr(data_member_count<T> == 117) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
               e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67,
               e68, e69, e6A, e6B, e6C, e6D, e6E, e6F, e70, e71, e72, e73,
               e74] = x;

        // Construct a tuple from these references.
        return std::tie(
            e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
            e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
            e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
            e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
            e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
            e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
            e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
            e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67,
            e68, e69, e6A, e6B, e6C, e6D, e6E, e6F, e70, e71, e72, e73, e74);
    } else if constexpr(data_member_count<T> == 118) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
               e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67,
               e68, e69, e6A, e6B, e6C, e6D, e6E, e6F, e70, e71, e72, e73, e74,
               e75] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C,
                        e4D, e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57,
                        e58, e59, e5A, e5B, e5C, e5D, e5E, e5F, e60, e61, e62,
                        e63, e64, e65, e66, e67, e68, e69, e6A, e6B, e6C, e6D,
                        e6E, e6F, e70, e71, e72, e73, e74, e75);
    } else if constexpr(data_member_count<T> == 119) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
               e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67,
               e68, e69, e6A, e6B, e6C, e6D, e6E, e6F, e70, e71, e72, e73, e74,
               e75, e76] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C,
                        e4D, e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57,
                        e58, e59, e5A, e5B, e5C, e5D, e5E, e5F, e60, e61, e62,
                        e63, e64, e65, e66, e67, e68, e69, e6A, e6B, e6C, e6D,
                        e6E, e6F, e70, e71, e72, e73, e74, e75, e76);
    } else if constexpr(data_member_count<T> == 120) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
               e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67,
               e68, e69, e6A, e6B, e6C, e6D, e6E, e6F, e70, e71, e72, e73, e74,
               e75, e76, e77] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C,
                        e4D, e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57,
                        e58, e59, e5A, e5B, e5C, e5D, e5E, e5F, e60, e61, e62,
                        e63, e64, e65, e66, e67, e68, e69, e6A, e6B, e6C, e6D,
                        e6E, e6F, e70, e71, e72, e73, e74, e75, e76, e77);
    } else if constexpr(data_member_count<T> == 121) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
               e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67,
               e68, e69, e6A, e6B, e6C, e6D, e6E, e6F, e70, e71, e72, e73, e74,
               e75, e76, e77, e78] = x;

        // Construct a tuple from these references.
        return std::tie(e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A,
                        e0B, e0C, e0D, e0E, e0F, e10, e11, e12, e13, e14, e15,
                        e16, e17, e18, e19, e1A, e1B, e1C, e1D, e1E, e1F, e20,
                        e21, e22, e23, e24, e25, e26, e27, e28, e29, e2A, e2B,
                        e2C, e2D, e2E, e2F, e30, e31, e32, e33, e34, e35, e36,
                        e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40, e41,
                        e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C,
                        e4D, e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57,
                        e58, e59, e5A, e5B, e5C, e5D, e5E, e5F, e60, e61, e62,
                        e63, e64, e65, e66, e67, e68, e69, e6A, e6B, e6C, e6D,
                        e6E, e6F, e70, e71, e72, e73, e74, e75, e76, e77, e78);
    } else if constexpr(data_member_count<T> == 122) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
               e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67,
               e68, e69, e6A, e6B, e6C, e6D, e6E, e6F, e70, e71, e72, e73, e74,
               e75, e76, e77, e78, e79] = x;

        // Construct a tuple from these references.
        return std::tie(
            e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
            e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
            e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
            e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
            e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
            e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
            e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
            e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67,
            e68, e69, e6A, e6B, e6C, e6D, e6E, e6F, e70, e71, e72, e73, e74,
            e75, e76, e77, e78, e79);
    } else if constexpr(data_member_count<T> == 123) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
               e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67,
               e68, e69, e6A, e6B, e6C, e6D, e6E, e6F, e70, e71, e72, e73, e74,
               e75, e76, e77, e78, e79, e7A] = x;

        // Construct a tuple from these references.
        return std::tie(
            e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
            e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
            e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
            e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
            e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
            e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
            e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
            e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67,
            e68, e69, e6A, e6B, e6C, e6D, e6E, e6F, e70, e71, e72, e73, e74,
            e75, e76, e77, e78, e79, e7A);
    } else if constexpr(data_member_count<T> == 124) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
               e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67,
               e68, e69, e6A, e6B, e6C, e6D, e6E, e6F, e70, e71, e72, e73, e74,
               e75, e76, e77, e78, e79, e7A, e7B] = x;

        // Construct a tuple from these references.
        return std::tie(
            e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
            e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
            e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
            e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
            e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
            e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
            e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
            e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67,
            e68, e69, e6A, e6B, e6C, e6D, e6E, e6F, e70, e71, e72, e73, e74,
            e75, e76, e77, e78, e79, e7A, e7B);
    } else if constexpr(data_member_count<T> == 125) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
               e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67,
               e68, e69, e6A, e6B, e6C, e6D, e6E, e6F, e70, e71, e72, e73, e74,
               e75, e76, e77, e78, e79, e7A, e7B, e7C] = x;

        // Construct a tuple from these references.
        return std::tie(
            e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
            e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
            e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
            e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
            e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
            e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
            e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
            e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67,
            e68, e69, e6A, e6B, e6C, e6D, e6E, e6F, e70, e71, e72, e73, e74,
            e75, e76, e77, e78, e79, e7A, e7B, e7C);
    } else if constexpr(data_member_count<T> == 126) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
               e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67,
               e68, e69, e6A, e6B, e6C, e6D, e6E, e6F, e70, e71, e72, e73, e74,
               e75, e76, e77, e78, e79, e7A, e7B, e7C, e7D] = x;

        // Construct a tuple from these references.
        return std::tie(
            e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
            e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
            e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
            e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
            e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
            e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
            e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
            e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67,
            e68, e69, e6A, e6B, e6C, e6D, e6E, e6F, e70, e71, e72, e73, e74,
            e75, e76, e77, e78, e79, e7A, e7B, e7C, e7D);
    } else if constexpr(data_member_count<T> == 127) {
        // Obtain references to member objects using structural bindings.
        auto& [e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
               e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
               e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
               e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
               e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
               e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
               e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
               e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67,
               e68, e69, e6A, e6B, e6C, e6D, e6E, e6F, e70, e71, e72, e73, e74,
               e75, e76, e77, e78, e79, e7A, e7B, e7C, e7D, e7E] = x;

        // Construct a tuple from these references.
        return std::tie(
            e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0A, e0B, e0C,
            e0D, e0E, e0F, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19,
            e1A, e1B, e1C, e1D, e1E, e1F, e20, e21, e22, e23, e24, e25, e26,
            e27, e28, e29, e2A, e2B, e2C, e2D, e2E, e2F, e30, e31, e32, e33,
            e34, e35, e36, e37, e38, e39, e3A, e3B, e3C, e3D, e3E, e3F, e40,
            e41, e42, e43, e44, e45, e46, e47, e48, e49, e4A, e4B, e4C, e4D,
            e4E, e4F, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e5A,
            e5B, e5C, e5D, e5E, e5F, e60, e61, e62, e63, e64, e65, e66, e67,
            e68, e69, e6A, e6B, e6C, e6D, e6E, e6F, e70, e71, e72, e73, e74,
            e75, e76, e77, e78, e79, e7A, e7B, e7C, e7D, e7E);
    }
}

} // namespace mirror

#endif // H_488DC17251AA4A0D8D8B3994795442DA
