#ifndef _RSA_HH_
#define _RSA_HH_

// This is the DATA structure for the private key
typedef struct {
	int d;
	int n;
} DATA_PRIVATE;

// This is the DATA structure for the public key
typedef struct {
	int e;
	int n;
} DATA_PUBLIC;

class RSA {
public:
    RSA();
    ~RSA();
public:
    void generateKey();

private:
	DATA_PRIVATE _privateKey;         //This is the private key generated.
	DATA_PUBLIC _publicKey;
    int _p, _q;

public:
	void setPublicKey(DATA_PUBLIC p) { _publicKey.e = p.e; _publicKey.n = p.n; }
	DATA_PUBLIC getPublicKey() { return _publicKey; }
};

#endif
