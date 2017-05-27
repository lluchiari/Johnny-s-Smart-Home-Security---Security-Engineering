#ifndef __MILLER_RABIN__
#define __MILLER_RABIN__

#include "InfInt.h"

#include <iostream>
#include <ostream>
#include <cstdlib>
#include <cmath>
#include <ctime>

#define MILLER_RABIN_CONSTANT 90


/* Code based on a code found in
 * <http://www.geeksforgeeks.org/primality-test-set-3-miller-rabin/> */

namespace MillerRabin {

	/**
	 * @brief millerTest is a mathematical probabilistic test to verify primality. For more
	 * information, please read <https://en.wikipedia.org/wiki/Miller–Rabin_primality_test>
	 * @param d is an odd number such that  d*2<sup>r</sup> = n-1
	 * @param n is the number itself to be verified primality
	 * @return 'true' if n is probably prime and 'false' if n is composite
	 */
	bool millerTest(InfInt d, InfInt n);


	/**
	 * @brief isPrime verifies if a number is prime or not
	 * @param n is the number itself to be verified primality
	 * @param k is an input parameter that determines accuracy level. Higher value of k indicates more accuracy.
	 * @return 'true' if n is probably prime and 'false' if n is composite
	 */
	bool isPrime(InfInt n, int k);

	/**
	 * @brief closedLowPrime gives the first prime lower than a supposed number
	 * @param supposed is an integer used as base number
	 * @return the closest lower prime to supposed
	 */
	InfInt closedLowPrime(InfInt supposed);

	/**
	 * @brief closedHighPrime gives the first prime higer than a supposed number
	 * @param supposed is an integer used as base number
	 * @return the closest higher prime to supposed
	 */
	InfInt closedHighPrime(InfInt supposed);

	/**
	 * @brief randomPrime generates a prime randomically with a specific length
	 * @param k is the prime length
	 * @return the randomically generated prime with k length
	 */
	InfInt randomPrime(int k);
}

#endif
