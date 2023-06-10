// Copyright Nezametdinov E. Ildus 2023.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)
//
module; // Global module fragment.

#include <limits.h>
#include <stddef.h>

#include <concepts>
#include <utility>
#include <tuple>
#include <type_traits>

export module mirror;
export namespace mirror {

////////////////////////////////////////////////////////////////////////////////
// Definition of a concept that models types which can be reflected.
////////////////////////////////////////////////////////////////////////////////

template <typename T>
concept reflexible = //
    std::is_aggregate_v<T> && std::default_initializable<T> &&
    (std::copy_constructible<T> || std::move_constructible<T>);

////////////////////////////////////////////////////////////////////////////////
// Non-static data member counting utilities.
////////////////////////////////////////////////////////////////////////////////

namespace detail {

// Special type which is convertible to any other type, except for possibly
// cv-qualified versions of itself, and corresponding reference types.
template <typename T, size_t I>
struct universal {
    template <typename U>
    operator U() const noexcept
        requires(!std::same_as<T, std::remove_cvref_t<U>>);
};

// A concept for a type which is constructible with a sequence of arguments. The
// size of the sequence is the same as the size of the non-type template
// parameter pack.
template <typename T, size_t... Indices>
concept constructible_from =
    requires { T{std::declval<universal<T, Indices>>()...}; };

// A predicate which shows if the given type is constructible with the given
// number of arguments.
template <typename T, size_t N>
constexpr auto is_constructible =
    []<size_t... Indices>(std::index_sequence<Indices...>) {
        return constructible_from<T, Indices...>;
    }(std::make_index_sequence<N>{});

// A median between two values.
template <size_t L, size_t R>
constexpr auto median = ((L / 2) + (R / 2) + ((1 + (L % 2) + (R % 2)) / 2));

// Performs compile-time binary search.
template <typename T, size_t L, size_t M, size_t R>
constexpr auto
bisect() noexcept -> size_t {
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
    constexpr auto bit_size = size_t{sizeof(T) * CHAR_BIT};
    static_assert(bit_size / sizeof(T) == CHAR_BIT);

    // Run binary search.
    return bisect<T, 0, median<0, bit_size>, bit_size>();
}

} // namespace detail

////////////////////////////////////////////////////////////////////////////////
// Reflection interface.
////////////////////////////////////////////////////////////////////////////////

// Count of the non-static data members in the given type.
template <reflexible T>
constexpr auto data_member_count = detail::count_data_members<T>();

// Returns a tuple of references to non-static data members of the given object.
template <reflexible T>
constexpr auto
reflect(T& x) noexcept
    requires(data_member_count<T> <= 32) {
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
    }
}

} // namespace mirror
