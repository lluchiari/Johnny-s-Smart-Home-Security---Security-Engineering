#ifndef _RSA_HH_
#define _RSA_HH_

#include <iostream>
#include <string>
#include <cstring>
#include <include/InfInt.h>
#include <include/utils.hh>
#include <include/millerRabin.hh>

class RSA {
public:
	RSA(int bits);
	RSA(InfInt p, InfInt q);
    ~RSA();
    void generateKey();
	InfInt getPublicKey() { return _publicKey; }
	InfInt *encryption(std::string message);
	char *decryption(InfInt *criptogram);

private:
	InfInt _privateKey;
	InfInt _publicKey;
	InfInt _modulus;
	InfInt _p, _q;
};

#endif
