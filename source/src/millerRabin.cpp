#include <include/millerRabin.hh>
#include <include/utils.hh>

namespace MillerRabin {

	bool millerTest(InfInt d, InfInt n) {
		// Pick a random number in [2..n-2]
		// Corner cases make sure that n > 4
		//int a = 2 + (rand() % (n - 4));
		InfInt random = rand();
		InfInt aux = (random % (n-4));
		InfInt a = aux + 2;

		// Compute a^d % n
		InfInt x = utils::modPow(a, d, n);

		if (x == 1  || x == n-1)
		   return true;

		// Keep squaring x while one of the following doesn't
		// happen
		// (i)   d does not reach n-1
		// (ii)  (x^2) % n is not 1
		// (iii) (x^2) % n is not n-1
		while (d != n-1) {
			x = (x * x) % n;
			d *= 2;

			if (x == 1)      return false;
			if (x == n-1)    return true;
		}

		// Return composite
		return false;
	}

	bool isPrime(InfInt n, int k) {
		// Corner cases
		if (n <= 1 || n == 4)  return false;
		if (n <= 3) return true;

		// Find r such that n = 2^d * r + 1 for some r >= 1
		InfInt d = n - 1;
		while (d % 2 == 0)
			d /= 2;

		// Iterate given nber of 'k' times
		for (int i = 0; i < k; i++)
			 if (millerTest(d, n) == false)
				  return false;

		return true;
	}

	InfInt closedLowPrime(InfInt supposed) {
		while(!isPrime(supposed, MILLER_RABIN_CONSTANT)) {
			supposed -= 1;
		}
		return supposed;
	}

	InfInt closedHighPrime(InfInt supposed) {
		while(!isPrime(supposed, MILLER_RABIN_CONSTANT)) {
			supposed += 1;
		}
		return supposed;
	}

	InfInt randomPrime(int k) {
		srand(time(NULL));
		char *aux;
		aux = (char *) malloc(sizeof(char)*k);
		utils::genRandomString(aux, k);
		InfInt number = (const char*) aux;
		free(aux);
		return closedHighPrime(number);
	}
}
