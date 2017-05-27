#include <include/rsa.hh>

RSA::RSA() {

}

RSA::RSA(int p, int q) {
	_p = p;
	_q = q;
}

RSA::~RSA() {

}

void RSA::generateKey() {
    /* Gerating the High primes */
//	this->_p = generatePrime();
//	this->_q = generatePrime();

	/* Calculating Parameters based on generated primes */
    int n, x;
    n = _p*_q;
	x = (_p-1)*(_q-1);

    /* Calculate the Gratest Common Divisor */
	utils::gcd(_p, _q);
}

InfInt RSA::giveMeAClosedLowPrime(InfInt supposed)
{
    while(!isPrime(supposed, MILLER_RABIN_CONSTANT))
    {
        supposed -= 1;
    }
    return supposed;
}

InfInt RSA::giveMeAClosedHighPrime(InfInt supposed)
{
    while(!isPrime(supposed, MILLER_RABIN_CONSTANT))
    {
        supposed += 1;
    }
    return supposed;
}

InfInt RSA::giveMeARandonPrime(int k)
{
    srand(time(NULL));
    char *aux;
    aux = (char *) malloc(sizeof(char)*k);
    utils::genRandomString(aux, k);
    InfInt number = (const char*) aux;
    free(aux);
    return giveMeAClosedHighPrime(number);
}
