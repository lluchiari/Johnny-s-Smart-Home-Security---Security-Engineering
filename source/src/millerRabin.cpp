#include "include/millerRabin.hh"

using namespace std;

 
InfInt power(InfInt x, InfInt y, InfInt p)
{
    /* Just for Garantie */
    if(p == 1){return 0;}
    InfInt res = 1;      // Initialize result
    x = x % p;  // Update x if it is more than or
                // equal to p
    while (y > 0)
    {
        // If y is odd, multiply x with result
	//if (y & 1)
	InfInt aux = y%2;
	if(aux == 1)
            res = (res*x) % p;
 
        // y must be even now
	y = y/2; //y = y>>1;
        x = (x*x) % p;
    }
    return res;
}

bool miillerTest(InfInt d, InfInt n)
{
    // Pick a random number in [2..n-2]
    // Corner cases make sure that n > 4
    //int a = 2 + (rand() % (n - 4));
    InfInt random = rand();
    InfInt aux = (random % (n-4));
    InfInt a = aux + 2;
 
    // Compute a^d % n
    InfInt x = power(a, d, n);
 
    if (x == 1  || x == n-1)
       return true;
 
    // Keep squaring x while one of the following doesn't
    // happen
    // (i)   d does not reach n-1
    // (ii)  (x^2) % n is not 1
    // (iii) (x^2) % n is not n-1
    while (d != n-1)
    {
        x = (x * x) % n;
        d *= 2;
 
        if (x == 1)      return false;
        if (x == n-1)    return true;
    }
 
    // Return composite
    return false;
}

bool isPrime(InfInt n, int k)
{
    // Corner cases
    if (n <= 1 || n == 4)  return false;
    if (n <= 3) return true;
 
    // Find r such that n = 2^d * r + 1 for some r >= 1
    InfInt d = n - 1;
    while (d % 2 == 0)
        d /= 2;
 
    // Iterate given nber of 'k' times
    for (int i = 0; i < k; i++)
         if (miillerTest(d, n) == false)
              return false;
 
    return true;
}
