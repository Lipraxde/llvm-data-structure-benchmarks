/**
 * Simple utilities for the data types we'll benchmark
 */

#ifndef LLVM_DATA_STRUCTURE_BENCHMARKS_DATA_TYPES_H
#define LLVM_DATA_STRUCTURE_BENCHMARKS_DATA_TYPES_H

#include <cstdint>

/* A generic struct whose sizeof == 16 bytes */
struct size_16 {
	size_16() : a(0), b(0) { }
	size_16(double a, double b) : a(a), b(b) { }
	bool operator<(const size_16 &other) const { return a < other.a && b < other.b; }
	bool operator==(const size_16 &other) const { return a == other.a && b == other.b; }
	bool operator!=(const size_16 &other) const { return !(*this == other); }
	double a;
	double b;

    size_16 &operator+=(const size_16 &rhs) // compound assignment (does not need to be a member,
    {                           // but often is, to modify the private members)
      /* addition of rhs to *this takes place here */
      a += rhs.a;
      b += rhs.b;
      return *this; // return the result by reference
    }

    // friends defined inside class body are inline and are hidden from non-ADL lookup
    friend size_16 operator+(size_16 lhs,        // passing lhs by value helps optimize chained a+b+c
                       const size_16 &rhs) // otherwise, both parameters may be const references
    {
      lhs += rhs; // reuse compound assignment
      return lhs; // return the result by value (uses move constructor)
    }
};

/* A generic struct whose sizeof == 64 bytes */
struct size_64 {
	size_64() { }
	size_64(const size_16 &a, const size_16 &b, const size_16 &c, const size_16 &d) : a(a), b(b), c(c), d(d) { }
	bool operator<(const size_64 &other) const { return a < other.a && b < other.b && c < other.c && d < other.d; }
	bool operator==(const size_64 &other) const { return a == other.a && b == other.b && c == other.c && d == other.d; }
	bool operator!=(const size_64 &other) const { return !(*this == other); }
	size_16 a;
	size_16 b;
	size_16 c;
	size_16 d;

    size_64 &operator+=(const size_64 &rhs) // compound assignment (does not need to be a member,
    {                           // but often is, to modify the private members)
      /* addition of rhs to *this takes place here */
      a += rhs.a;
      b += rhs.b;
      c += rhs.c;
      d += rhs.d;
      return *this; // return the result by reference
    }
 
    // friends defined inside class body are inline and are hidden from non-ADL lookup
    friend size_64 operator+(size_64 lhs,        // passing lhs by value helps optimize chained a+b+c
                       const size_64 &rhs) // otherwise, both parameters may be const references
    {
      lhs += rhs; // reuse compound assignment
      return lhs; // return the result by value (uses move constructor)
    }
};

// Template method to generate unique values for the data types we'll be testing.
// This lets us write *one* test function that covers *all* our types, rather than
// having separate methods for test_int(), test_size_16(), test_size_64(), etc.
template<class T> T       generate_value         (int32_t iteration);
template<>        int32_t generate_value<int32_t>(int32_t iteration) { return iteration; }
template<>        int64_t generate_value<int64_t>(int32_t iteration) { return iteration + ((int64_t)iteration << 32); }
template<>        size_16 generate_value<size_16>(int32_t iteration) { return size_16(iteration, iteration + 1); }
template<>        size_64 generate_value<size_64>(int32_t iteration) { return size_64(size_16(iteration, iteration + 1), size_16(iteration + 2, iteration + 3), size_16(iteration + 4, iteration + 5), size_16(iteration + 6, iteration + 7)); }


#endif //LLVM_DATA_STRUCTURE_BENCHMARKS_DATA_TYPES_H
