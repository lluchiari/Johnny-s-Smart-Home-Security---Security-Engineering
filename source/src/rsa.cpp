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
