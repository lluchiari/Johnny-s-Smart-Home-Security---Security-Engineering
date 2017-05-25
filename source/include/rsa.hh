#ifndef _RSA_HH_
#define _RSA_HH_

// This is the DATA structure for the private key
typedef int DATA_PRIVATE;

// This is the DATA structure for the private key
typedef int DATA_PUBLIC;

class RSA
{
public:
    RSA();
    ~RSA();
public:
    void gerateKey();

private:
    DATA_PRIVATE _privateKey;         //This is the private key gerated. The data type is
    int _p, _q;

public:
    DATA_PUBLIC publicKey;
};

#endif _RSA_HH_
