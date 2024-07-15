/**
 * 64 Bit Banging Library
 * Began 7/7/2024
 * Lead Developer: B3N $T^CK5
 * Developed with AI assistance from:
 *    GPT-4o
 *    GitHub CoPilot
 */
#ifndef _BIT64_H__
#define _BIT64_H__
#include <stdint.h>

/*
 ⑇  BASIC OPERATIONS
    ∘  Set a specific bit
    ∘  Clear a specific bit
    ∘  Toggle a specific bit
    ∘  Check if a specific bit is set
*/
/* Set a specific bit */
#define SET_BIT(qword, pos) ((qword) |= (1ULL << (pos)))

/* Clear a specific bit */
#define CLEAR_BIT(qword, pos) ((qword) &= ~(1ULL << (pos)))

/* Toggle a specific bit */
#define TOGGLE_BIT(qword, pos) ((qword) ^= (1ULL << (pos)))

/* Check if a specific bit is set */
#define CHECK_BIT(qword, pos) (!!((qword) & (1ULL << (pos))))

/*
 ⑇  BITWISE OPERATIONS
    ∘  Bitwise AND
    ∘  Bitwise OR
    ∘  Bitwise XOR
    ∘  Bitwise NOT
*/
/* Bitwise AND */
#define BITWISE_AND(a, b) ((a) & (b))

/* Bitwise OR */
#define BITWISE_OR(a, b) ((a) | (b))

/* Bitwise XOR */
#define BITWISE_XOR(a, b) ((a) ^ (b))

/* Bitwise NOT */
#define BITWISE_NOT(a) (~(a))
/*
 ⑇  BIT SHIFTING
    ∘  Left shift
    ∘  Right shift, logical (fills vacated bits with 0's)
    ∘  Right shift, arithmetic (fills vacated bits with original sign bit)
*/

/* Left shift */
#define LEFT_SHIFT(value, shift) ((value) << (shift))

/* Right shift (logical) */
#define RIGHT_SHIFT_LOGICAL(value, shift)                                     \
  (((unsigned long long)(value)) >> (shift))

/* Right shift (arithmetic) */
#define RIGHT_SHIFT_ARITHMETIC(value, shift) ((value) >> (shift))

/*
 ⑇  BIT ROTATION
    ∘  Rotate left
    ∘  Rotate right
*/
#define ROTATE_LEFT(value, shift, bits)                                       \
  (((value) << (shift)) | ((value) >> ((bits) - (shift))))

#define ROTATE_RIGHT(value, shift, bits)                                      \
  (((value) >> (shift)) | ((value) << ((bits) - (shift))))
/*

 ⑇  BIT COUNTING
    ∘  Count number of set bits (population count)
    ∘  Count leading zeros
    ∘  Count trailing zeros
*/
// Count number of set bits (population count)
#define POPCOUNT(x) __builtin_popcountll (x)

// Count leading zeros
#define COUNT_LEADING_ZEROS(x) __builtin_clzll (x)

// Count trailing zeros
#define COUNT_TRAILING_ZEROS(x) __builtin_ctzll (x)

/*
 ⑇  BIT MASKS
    ∘  Create a bit mask for a given range
    ∘  Apply a bit mask to a value
    ∘  Clear bits in a range
*/
#define CREATE_BIT_MASK(low, high)                                            \
  (((1ULL << ((high) - (low) + 1)) - 1) << (low))

// Apply a bit mask to a value
#define APPLY_BIT_MASK(value, mask) ((value) & (mask))

// Clear bits in a range [low, high] (inclusive) in a value
#define CLEAR_BITS_IN_RANGE(value, low, high)                                 \
  ((value) & ~CREATE_BIT_MASK (low, high))

/*
 ⑇  BIT EXTRACTION & INSERTION
    ∘  Extract bits from a specified position and length
    ∘  Insert bits into a specified position and length
*/

// Extract bits from a specified position and length
#define EXTRACT_BITS(value, position, length)                                 \
  (((value) >> (position)) & ((1ULL << (length)) - 1))

// Insert bits into a specified position and length
#define INSERT_BITS(original, bitsToInsert, position, length)                 \
  (((original) & ~(((1ULL << (length)) - 1) << (position)))                   \
   | ((bitsToInsert) << (position)))

/*
 ⑇  SIGN MANIPULATION
    ∘  Compute the absolute value without branching
    ∘  Compute the sign of a number (-1, 0, 1)
    ∘  Detect if two integers have opposite signs
*/

// Compute the absolute value without branching
#define ABS_NO_BRANCH(x) (((x) ^ ((x) >> 63)) - ((x) >> 63))

// Compute the sign of a number (-1, 0, 1)
#define SIGN(x) (((x) > 0) - ((x) < 0))

// Detect if two integers have opposite signs
#define OPPOSITE_SIGNS(x, y) (((x) ^ (y)) < 0)

/*
 ⑇  ENDIANESS CONVERSION
    ∘  Convert between little-endian and big-endian
*/

// Convert between little-endian and big-endian for a 64-bit integer
#define ENDIAN_SWAP_64(x)                                                     \
  ((((x)&0xFF00000000000000ULL) >> 56) | (((x)&0x00FF000000000000ULL) >> 40)  \
   | (((x)&0x0000FF0000000000ULL) >> 24) | (((x)&0x000000FF00000000ULL) >> 8) \
   | (((x)&0x00000000FF000000ULL) << 8) | (((x)&0x0000000000FF0000ULL) << 24) \
   | (((x)&0x000000000000FF00ULL) << 40)                                      \
   | (((x)&0x00000000000000FFULL) << 56))
/*
 ⑇  PARITY CHECKING
    ∘  Check the parity (odd or even) of the number of set bits
*/
// Check the parity (odd or even) of the number of set bits
#define CHECK_PARITY(x) (__builtin_parityll (x))
/*
 ⑇  MULTIPLICATION & DIVISION BY 2ⁿ
    ∘  Efficient multiplication by powers of two using bit shifts
    ∘  Efficient division by powers of two using bit shifts
*/
// Efficient multiplication by powers of two using bit shifts
#define MULTIPLY_BY_POW2(x, n) ((x) << (n))

// Efficient division by powers of two using bit shifts
// Note: For signed integers, right shifting can behave differently on
// different platforms due to arithmetic shift.
#define DIVIDE_BY_POW2(x, n) ((x) >> (n))
/*
 ⑇  MINIMUM & MAXIMUM
    ∘  Compute the minimum of two integers without branching
    ∘  Compute the maximum of two integers without branching
*/
// Compute the minimum of two integers without branching
#define MIN_WITHOUT_BRANCHING(x, y) ((y) ^ (((x) ^ (y)) & -((x) < (y))))

// Compute the maximum of two integers without branching
#define MAX_WITHOUT_BRANCHING(x, y) ((x) ^ (((x) ^ (y)) & -((x) < (y))))
/*
 ⑇  BYTE SWAPPING
    ∘  Swap the bytes in a 64-bit integer
*/
// Swap the bytes in a 64-bit integer
#define SWAP_BYTES_64(x)                                                      \
  (((x) >> 56) | ((x) << 56) | (((x)&0x00FF000000000000) >> 40)               \
   | (((x)&0x000000000000FF00) << 40) | (((x)&0x0000FF0000000000) >> 24)      \
   | (((x)&0x0000000000FF0000) << 24) | (((x)&0x000000FF00000000) >> 8)       \
   | (((x)&0x00000000FF000000) << 8))
/*
 ⑇  BIT REVERSAL
    ∘  Reverse the bits in a 64-bit integer
*/
// Reverse the bits in a 64-bit integer
#define REVERSE_BITS_64(x) (((x)*0x0202020202ULL & 0x010884422010ULL) % 1023)

/*
 ⑇  BIT PATTERNS & SEQUENCES
    ∘  Find the longest sequence of consecutive set bits
    ∘  Find the longest sequence of consecutive clear bits
*/

/*
 ⑇  BIT GROUPING
    ∘  Pack and unpack bits into groups
    ∘  Group bits by specified patterns
*/

/*
 ⑇  BIT TESTING & MANIPULATION
    ∘  Test multiple bits at once
    ∘  Set or clear multiple bits at once
*/
// Test if multiple bits are set in a value
#define TEST_MULTIPLE_BITS(value, mask) (((value) & (mask)) == (mask))

// Set multiple bits in a value
#define SET_MULTIPLE_BITS(value, mask) ((value) |= (mask))

// Clear multiple bits in a value
#define CLEAR_MULTIPLE_BITS(value, mask) ((value) &= ~(mask))
/*
 ⑇  LOGICAL OPERATIONS
    ∘  Logical implication
    ∘  Logical equivalence
*/
// Logical implication (if A then B)
#define LOGICAL_IMPLICATION(A, B) (!(A) || (B))

// Logical equivalence (A if and only if B)
#define LOGICAL_EQUIVALENCE(A, B) (!((A) ^ (B)))
/*
 ⑇  MASK GENERATION
    ∘  Generate masks for high bits, low bits, and middle bits
*/
// Generate a mask for the high bits
#define HIGH_BITS_MASK(high) (~((1ULL << (64 - (high))) - 1))

// Generate a mask for the low bits
#define LOW_BITS_MASK(low) ((1ULL << (low)) - 1)

// Generate a mask for the middle bits, given low and high bit positions
#define MIDDLE_BITS_MASK(low, high)                                           \
  (LOW_BITS_MASK (high) ^ LOW_BITS_MASK (low))
/*
 ⑇  MISCELLANEOUS
    ∘  Find the next power of two
    ∘  Compute the modulus of a power of two
    ∘  Multiply without using multiplication (e.g., using shifts and adds)
*/

#endif // _BIT64_H__
