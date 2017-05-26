#include "../include/rsa.hh"

RSA::RSA() {

}

void RSA::generateKey() {
    /* Gerating the High primes */
    this->_p = generatePrime(1);
    this->_q = generatePrime(0);

    /* Calculating Paramters based on gerated primes */
    InfInt n, z, e, d;
    n = _p*_q;
    z = (_p-1)*(_q-1);
    e = 17;


    /* Calculate the Gratest Common Divisor */
    //gdc();
}

InfInt RSA::generatePrime(int teste)
{
    if (teste)
    {
        return 11;
    }
    return 13;
}
