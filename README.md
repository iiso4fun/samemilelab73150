# samemilelab73150

# Lab 7 – BigInts and Timing Cost

Samuel Emile  
April 8, 2025  

---

## Overview

This lab demonstrates how to work with very large integers using a custom `BigInt` library in C++. It explores the representation of fractions using `std::pair<bigint, bigint>`, implements operations on fractions (sum and product), and benchmarks performance differences between built-in types (`int`, `long`) and `BigInt`.

The program also includes unit testing and an interactive mode for user input. It highlights how built-in integer types can overflow, while `BigInt` safely handles large calculations.

---

## Features

- Uses a single-header `bigint.h` library for arbitrary-precision arithmetic
- Represents fractions using `std::pair<bigint, bigint>`
- Implements:
  - Addition of two BigInt fractions
  - Multiplication of two BigInt fractions
- Benchmarks:
  - Multiplication using `int`, `long int`, and `BigInt`
- Demonstrates overflow with built-in `int`
- Includes unit testing with `doctest`
- Supports interactive input and output

---

## How to Compile and Run

Make sure `samlab7.cpp`, `bigint.h`, and `doctest.h` are in the same folder.

### Compile:
```bash
g++ -std=c++11 -o lab samlab7.cpp
