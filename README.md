# DESCRIPTION
Mirror is a minimalistic C++20 reflection library. It contains utilities for
counting the non-static data members in types, and for viewing objects as
tuples.

Implementation uses the same basic idea as Antony Polukhin's
[magic_get](https://github.com/apolukhin/magic_get), and has the same
limitations.

Hopefully, this library will become obsolete by the time C++26 comes out.

# INSTALLATION
The library consists of one module file in the `src` directory. By default only
types with up to 32 non-static data members can be viewed as tuples. To increase
this number the `generate.sh` script can be used (requires python3 and
clang-format).

For example, to increase the limit to 255, the following command can be executed
in a terminal:
```
./generate.sh 255
```

# USAGE
To obtain the number of non-static data members in a type, use the
`data_member_count` variable template:

```
struct custom_type {
    int x, y, z;
    float w;
};

static_assert(mirror::data_member_count<custom_type> == 4);
```

To view an object of some type as a tuple of references to its non-static data
members, use the `reflect` function:

```
auto x = custom_type{1, 2, 3, 4.0f};
auto t = mirror::reflect(x);

// The following expression evaluates to true.
// (std::get<0>(t) == x.x) && (&(std::get<0>(t)) == &(x.x))
```

# LICENSE
Copyright Nezametdinov E. Ildus 2023.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
https://www.boost.org/LICENSE_1_0.txt)
