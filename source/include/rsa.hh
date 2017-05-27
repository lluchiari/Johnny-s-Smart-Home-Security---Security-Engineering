#ifndef _RSA_HH_
#define _RSA_HH_

#include <include/InfInt.h>
#include <include/utils.hh>
#include <include/millerRabin.hh>

/// DATA structure for the private key
typedef struct {
    InfInt d;
    InfInt n;
} DATA_PRIVATE;

/* This is the DATA structure for the public key */
typedef struct {
    InfInt e;
    InfInt n;
} DATA_PUBLIC;

class RSA {
public:
    RSA();
	RSA(int p, int q);
    ~RSA();
    void generateKey();
	void setPublicKey(DATA_PUBLIC p) { _publicKey.e = p.e; _publicKey.n = p.n; }
	DATA_PUBLIC getPublicKey() { return _publicKey; }
private:
    /**
     * @brief giveMeAClosedLowPrime gives the first prime lower than a supposed number
     * @param supposed is a integer used as base number
     * @return the closest lower prime integer to supposed
     */
    InfInt giveMeAClosedLowPrime(InfInt supposed);

    /**
     * @brief giveMeAClosedHighPrime gives the first prime higer than a supposed number
     * @param supposed is a integer used as base number
     * @return the closest higher prime integer to supposed
     */
    InfInt giveMeAClosedHighPrime(InfInt supposed);

    /**
     * @brief giveMeARandonPrime gives a prime generated randomically with a specific length
     * @param k is the integer length
     * @return the randomically integer prime generated with k length
     */
    InfInt giveMeARandonPrime(int k);

private:
    /* This is the private key generated */
    DATA_PRIVATE _privateKey;
	DATA_PUBLIC _publicKey;
    int _p, _q;
};

#endif
