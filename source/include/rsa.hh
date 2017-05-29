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
	RSA();
    RSA(int bits);
	RSA(InfInt p, InfInt q);
    ~RSA();
    int loadPrivateKey(std::string filename);
    int loadPublicKey(std::string filename);
    void generateKey();
	InfInt getPublicKey() { return _publicKey; }
	InfInt *encryption(const std::__cxx11::string &message);
	void decryption(std::__cxx11::string &dec, InfInt *criptogram);
    int saveKeys();

private:
	InfInt _privateKey;
	InfInt _publicKey;
	InfInt _modulus;
	InfInt _p, _q;
	int *_slice;
	bool _canGenerate;
};

#endif
