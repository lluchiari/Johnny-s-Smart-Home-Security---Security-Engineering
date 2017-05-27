#ifndef __MILLER_RABIN__
#define __MILLER_RABIN__

#include "InfInt.h"

#include <iostream>
#include <ostream>
#include <cstdlib>
#include <cmath>
#include <ctime>


/* This code was based on a code found in
 * <http://www.geeksforgeeks.org/primality-test-set-3-miller-rabin/> */

/**
 * @brief power is a utility function to do modular exponentiation.
 * @param x is the base
 * @param y is the exponent
 * @param p is the modulus
 * @return (x^y) % p
 */
InfInt power(InfInt x, InfInt y, InfInt p);


/**
 * @brief miillerTest is a mathematical probabilistic test to verify primality. For more
 * information, please read <https://en.wikipedia.org/wiki/Miller–Rabin_primality_test>
 * @param d is an odd number such that  d*2<sup>r</sup> = n-1
 * @param n is the number itself to be verified primality
 * @return 'true' if n is probably prime and 'false' if n is composite
 */
bool miillerTest(InfInt d, InfInt n);


/**
 * @brief isPrime verifies if a number is prime or not
 * @param n is the number itself to be verified primality
 * @param k is an input parameter that determines accuracy level. Higher value of k indicates more accuracy.
 * @return 'true' if n is probably prime and 'false' if n is composite
 */
bool isPrime(InfInt n, int k);

#endif
