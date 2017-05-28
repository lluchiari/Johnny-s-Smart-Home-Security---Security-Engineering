#include <include/rsa.hh>
#include <iostream>
#include <unistd.h>
#include <string.h>

RSA::RSA(int bits) {
	_p = MillerRabin::randomPrime(bits);
	usleep(1000000); // necessário para garantir primos diferentes entre si
	_q = MillerRabin::randomPrime(bits);
}

RSA::RSA(InfInt p, InfInt q) {
	_p = p;
	_q = q;
}

RSA::~RSA() {

}

/**
 * @brief RSA::generateKey método de geração de chaves pública e privada
 * @variable n, módulo da chave
 * @variable x, totiente de n
 * @variable e, expoente da fórmula da chave pública
 * @variable d, expoente da fórmula da chave privada
 */
void RSA::generateKey() {

	/* Calculating Parameters based on generated primes */
	InfInt n, x, e, d;
	e = 65537; // Foi percebido que o número 65537(2^16 + 1) quase sempre é coprimo de x
	n = _p*_q; // n será o módulo da função
	x = (_p-1)*(_q-1); // x é o totiente de n, ou seja, o tamanho do conjunto de coprimos de n

    /* Cálculo do maior divisor comum entre 'e' e 'x' */
	while(utils::gcd(e, x) != 1)
		e += 2;

	/* Multiplicativo inverso de 'e', módulo 'n' */
	d = utils::invMul(e, n);
	std::cout << "Private key: d = " << d.toString() << "\nPublic key: e = " << e.toString() << std::endl;
	std::cout << "Modulus: n = " << n.toString() << std::endl;
	_privateKey = d;
	_publicKey = e;
	_modulus = n;
}

InfInt *RSA::encryption(const char *message)
{
    int messageLen = strlen(message);
    InfInt *cryptogram = (InfInt *) malloc(sizeof(InfInt)*messageLen);
    std::cout << "Allocating Memory [" << messageLen << "]*"<< sizeof(InfInt)<< "\n";
    InfInt aux;
    for(int i=0; i<messageLen; i++)
    {
        std::cout << "Loop: {\n";
		aux = (int) message[i];
        std::cout << "Aux:" << aux << "\n";
        cryptogram[i] = utils::modPow(aux, this->_publicKey, this->_modulus);
        std::cout << "Encripted: ";
        std::cout << cryptogram[i];
        std::cout << "\n}\n";
    }
    return cryptogram;
}

char *RSA::decryption(InfInt *criptogram)
{
    return NULL;

}
