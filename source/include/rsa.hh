#ifndef _RSA_HH_
#define _RSA_HH_

#include <include/InfInt.h>
#include <include/utils.hh>
#include <include/millerRabin.hh>

class RSA {
public:
    RSA();
	RSA(InfInt p, InfInt q);
    ~RSA();
    void generateKey();
	void setPublicKey(InfInt p) { _publicKey = p; }
	InfInt getPublicKey() { return _publicKey; }

private:
	InfInt _privateKey;
	InfInt _publicKey;
	InfInt _modulus;
	InfInt _p, _q;

	void setPrivateKey(InfInt p) { _privateKey = p; }
};

#endif
