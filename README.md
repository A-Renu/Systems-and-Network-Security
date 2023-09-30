The following functions are implemented using GMP library in C.
The GMP (GNU Multiple Precision Arithmetic Library) is a C library for arbitrary-precision arithmetic. It allows us to perform mathematical operations with very large numbers, numbers with many digits beyond what standard data types like int or double can represent. GMP is a powerful tool for handling integers and floating-point numbers with arbitrary precision.

All of the programs take input from the command line.

prg 1 - [Common divisors] 
Given n, {mi} i=1 to n integers, prints all common divisors of (m1,m2,…,mn).

Compile - gcc prg1.c -o prg1 -lgmp  
Run - ./prg1 <integer1> <integer2> ... <integerN>

prg 2 - [Extended Euclidean algorithm] 
Outputs x,y when a,b is given, such ax+by=gcd(a,b).

Compile - gcc prg2.c -o prg2 -lgmp  
Run - ./prg2 <value_a> <value_b>

prg 3 - [Fundamental Theorem of Arithmetic] 
Given any integer outputs the product of primes.

Compile - gcc prg3.c -o prg3 -lgmp  
Run - ./prg3 <integer>

prg 4 - [Reduced Residue System Modulo m] 
Given an integer m, outputs the RRSM_m set of integers and the value of φ(m) where φ is the totient function.

Compile - gcc prg4.c -o prg4 -lgmp  
Run - ./prg4 <value_m>

prg 5 - [Fermats little theorem]
Given a, x and n, outputs a^x (mod n).

Compile - gcc prg5.c -o prg5 -lgmp  
Run - ./prg5 <value_a> <value_x> <value_n>

prg 6 - [Modular Inverse]
Given a and m, prints whether multiplicative inverse of a (mod m) exist Y/N then outputs its inverse, if exist.

Compile - gcc prg6.c -o prg6 -lgmp  
Run - ./prg6 <value_a> <value_m>

prg 7 - [Solutions of congruence] 
Given a, b and m, prints whether solution to the congruence ax≡b(modm) exist Y/N. If Yes then outputs the number of solutions and all the solutions.

Compile - gcc prg7.c -o prg7 -lgmp  
Run - ./prg7 <value_a> <value_b> <value_m>

prg 8 - [Solution to system of congruences (Chinese Remainder theorem)] 
Given set of integers {(a_i,b_i,m_i )} where i=1 to n, prints whether there exist common solution x which satisfy the system of congruences of the form a_i*x≡b_i (mod m_i ). If exist, then prints all the solutions.

Compile - gcc prg8.c -o prg2 -lgmp  
Run - ./prg8 <value_a1> <value_b1> <value_m1> <value_a2> <value_b2> <value_m2> ... <value_an> <value_bn> <value_mn>

prg 9 - [Order] 
Given a and m, prints order of a under modulo m.

Compile - gcc prg9.c -o prg9 -lgmp  
Run - ./prg9 <value_a> <value_m>

prg 10 - [Primitive roots] 
Given m, prints the total number of primitive roots exist and the primitive roots, under modulo m.

Compile - gcc prg10.c -o prg10 -lgmp  
Run - ./prg10 <value_m>
