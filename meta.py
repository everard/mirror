# Copyright Nezametdinov E. Ildus 2023.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# https://www.boost.org/LICENSE_1_0.txt)
#
import argparse

# Parse command line arguments.
parser = argparse.ArgumentParser()
parser.add_argument("input", help = "input file name")
parser.add_argument("output", help = "output file name")
parser.add_argument(\
    "limit",\
    help = "maximum number of non-static data members in types",\
    nargs='?',\
    type = int,\
    choices = range(1, 256), metavar="[1-255]")

args = parser.parse_args()

# Read the input file to a string.
source_code = ""
with open(args.input, 'r') as file:
    source_code = "\n".join([line.rstrip() for line in file])

# Generate output file.
with open(args.output, 'w') as file:
    # Writes the string to the file.
    def write(string):
        print(string, file=file)

    # Writes maximum number of non-static data members in types to the file.
    def limit():
        write(args.limit)

    # Writes view_as_tuple specializations to the file.
    def generate_specializations():
        for n in range(1, args.limit+1):
            # Generate comma-separated list of variables with different names.
            variables = ", ".join([f"e{i:0>2X}" for i in range(0, n)])

            # Write function definition.
            write(f"else if constexpr(data_member_count<T> == {n}) {{")
            write(f"// Obtain references to member objects using structural"\
                  f" bindings.")
            write(f"auto& [{variables}] = x;")
            write("")
            write(f"// Construct a tuple from these references.")
            write(f"return std::tie({variables});")
            write(f"}}")

    # Find the first template parameter in the input file's source code.
    i, j = (source_code.find("(@"), source_code.find("@)"))

    # Write the output file by substituting template parameters in the input
    # file's source code.
    while i != -1:
        if i > j:
            raise RuntimeError("Error: syntax error in input file")

        # Write the part of the source code which comes before template
        # parameter.
        write(source_code[:i])

        # Execute the template parameter.
        globals()[source_code[i+2:j]]()

        # Shrink the source code.
        source_code = source_code[j+2:]

        # Find the next template parameter in the remaining source code.
        i, j = (source_code.find("(@"), source_code.find("@)"))

    # Write the remaining source code.
    write(source_code)
