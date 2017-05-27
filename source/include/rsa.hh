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

/// DATA structure for the public key
typedef struct {
    InfInt e;
    InfInt n;
} DATA_PUBLIC;

class RSA {
public:
    RSA();
	RSA(InfInt p, InfInt q);
    ~RSA();
    void generateKey();
	void setPublicKey(DATA_PUBLIC p) { _publicKey.e = p.e; _publicKey.n = p.n; }
	DATA_PUBLIC getPublicKey() { return _publicKey; }
private:
    /* This is the private key generated */
    DATA_PRIVATE _privateKey;
	DATA_PUBLIC _publicKey;
	InfInt _p, _q;

	void setPrivateKey(DATA_PRIVATE p) { _privateKey.d = p.d; _privateKey.n = p.n; }
};

#endif
