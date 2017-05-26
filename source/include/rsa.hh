#ifndef _RSA_HH_
#define _RSA_HH_

#include <include/InfInt.h>
#include <include/utils.hh>

/// DATA structure for the private key
typedef struct {
	int d;
	int n;
} DATA_PRIVATE;

/// DATA structure for the public key
typedef struct {
	int e;
	int n;
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
	DATA_PRIVATE _privateKey;         //This is the private key generated.
	DATA_PUBLIC _publicKey;
    int _p, _q;
};

#endif
