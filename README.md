Seventh: Two's Complement Binary Representation Converter

This C program converts decimal numbers into their two's complement binary representation. It takes input from a file and processes each line to generate the binary representation.

Usage

Clone the repository or download the source code.

Compile the program using a C compiler (e.g., GCC).

gcc -o seventh seventh.c

Create an input file (e.g., input.txt) with lines containing a decimal number and the desired number of bits for representation, separated by a space.

42 7

16 4

-9 4

Run the program, passing the input file as a command-line argument.

./seventh input.txt

The program will output the two's complement binary representation of each number in the input file, followed by a newline character.

Example Execution

For the provided input file input.txt, the program will produce the following output:

0101010

0111

1000

Notes:

If a given number cannot be represented with the specified number of bits because it is too large or too small, the program will print the representation for the largest positive value or the smallest negative value, respectively, with the given number of bits in two's complement representation.

Eighth: Decimal Fraction to Canonical Binary Fraction Converter

This C program converts a decimal fraction to a binary fraction in the canonical representation (−1)^s × M × 2^E. It takes input from a file and processes each line to generate the canonical binary representation.

Usage

Clone the repository or download the source code.

Compile the program using a C compiler (e.g., GCC).

gcc -o eighth eighth.c

Create an input file (e.g., input.txt) with lines containing a decimal fraction and the number of bits to represent it, separated by a space.

6.25 6

12.5 3

Run the program, passing the input file as a command-line argument.

./eighth input.txt

The program will output the M and E values in the canonical representation, separated by a space, for each input, followed by a newline character.

Example Execution

For the provided input file input.txt, the program will produce the following output:

1.100100 2

1.100 3

Notes:

The program assumes all input fractions are positive; no negative numbers will be provided.
The program does not perform any rounding; it prints as many digits after the decimal point as specified by the input.

Ninth: Decimal to IEEE-754 Floating Point Converter with Rounding

This C program converts a decimal fraction to the IEEE-754 floating-point representation in a given configuration with rounding to the nearest with ties-to-even rounding mode. It takes input from a file and processes each line to generate the IEEE-754 representation.

Usage

Clone the repository or download the source code.

Compile the program using a C compiler (e.g., GCC).

gcc -o ninth ninth.c

Create an input file (e.g., input.txt) with lines containing a decimal fraction, the number of bits in the IEEE-754 FP representation, the number of bits for the exponent, and the number of fraction bits, separated by spaces.

6.5 8 4 3

0.0546875 8 4 3

0.013671875 8 4 3

6.375 8 4 3

8.5 8 4 3

9.5 8 4 3

Run the program, passing the input file as a command-line argument.

./ninth input.txt

The program will output the IEEE-754 representation with the specified number of bits for each input, followed by a newline character.

Example Execution

For the provided input file input.txt, the program will produce the following output:

01001101

00010110

00000111

01001101

01010000

01010010

Notes:

The program assumes that input values will not result in NaNs, and no value will round up or down to infinities.
It uses the IEEE-754 rounding to the nearest with ties-to-even rounding mode to convert decimal fractions to their floating-point representation.
The program follows the specified number of bits for the IEEE-754 representation, exponent, and fraction bits as provided in the input.

Tenth: Hexadecimal Bit-Pattern to Decimal Fraction Converter

This C program converts a hexadecimal bit-pattern in the IEEE-754 floating-point format to its corresponding decimal fractional value. It takes input from a file and processes each line to generate the decimal fraction.

Usage

Clone the repository or download the source code.

Compile the program using a C compiler (e.g., GCC).

gcc -o tenth tenth.c
Create an input file (e.g., input.txt) with lines containing the total number of bits, the number of bits for the exponent, the number of bits for the fraction, the hexadecimal bit-pattern (prefixed with "0x"), and the number of precision bits after the decimal point in the decimal fraction, separated by spaces.

8 4 3 0x4d 2

8 4 3 0x16 7

Run the program, passing the input file as a command-line argument.

./tenth input.txt

The program will output the decimal fraction value with the specified number of precision bits for each input, followed by a newline character.

Example Execution
For the provided input file input.txt, the program will produce the following output:

6.50

0.0546875

Notes:

The program follows the IEEE-754 floating-point format to convert the hexadecimal bit-pattern to its decimal fractional value.
It allows specifying the precision (number of digits after the decimal point) for the resulting decimal fraction.


