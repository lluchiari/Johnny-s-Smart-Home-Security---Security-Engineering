#ifndef _RSA_HH_
#define _RSA_HH_

/* This is the DATA structure for the private key */
typedef int DATA_PRIVATE;

/* This is the DATA structure for the private key */
typedef int DATA_PUBLIC;

class RSA
{
public:
    RSA();
    ~RSA();
public:
    void gerateKey();

private:
    /*This function gerates the primes. Firs see a method*/
    int geratePrime();

public:
    DATA_PUBLIC publicKey;

private:
    /* This is the private key gerated. The data type is */
    DATA_PRIVATE _privateKey;
    int _p, _q;
};

#endif _RSA_HH_
