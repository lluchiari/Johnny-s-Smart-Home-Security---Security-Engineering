#include <include/rsa.hh>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string.h>

RSA::RSA(int bits) {
	_p = MillerRabin::randomPrime(bits);
	usleep(1000000); // necessário para garantir primos diferentes entre si
	_q = MillerRabin::randomPrime(bits);
	_slice = NULL;
}

RSA::RSA(InfInt p, InfInt q) {
	_p = p;
	_q = q;
	_slice =  NULL;
}

RSA::~RSA() {
	if(_slice != NULL)
		free(_slice);
}

void RSA::saveKeys() {
	std::ofstream keysFile;
	keysFile.open("keys.txt");
	if(keysFile.is_open()) {
		keysFile << "Private: " << _privateKey << "\n";
		keysFile << "Public: " << _publicKey << "\n";
		keysFile << "Modulus: " << _modulus << "\n";
		keysFile.close();
	}
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
	InfInt n, x, e;
	std::pair<InfInt, InfInt> privValues;

	e = 65537; // Foi percebido que o número 65537(2^16 + 1) quase sempre é coprimo de x
	n = _p*_q; // n será o módulo da função
	x = (_p-1)*(_q-1); // x é o totiente de n, ou seja, o tamanho do conjunto de coprimos de n

    /* Cálculo do maior divisor comum entre 'e' e 'x' */
	if(e >= n) e = 3;
	utils::gcd(privValues, e, x);
	while(privValues.second != 1) {
		e += 2;
		utils::gcd(privValues, e, x);
	}
	_privateKey = privValues.first;
	_publicKey = e;
	_modulus = n;
	std::cout << "Private key: d = " << _privateKey.toString() << "\nPublic key: e = " << _publicKey.toString() << std::endl;
	std::cout << "Modulus: n = " << _modulus.toString() << std::endl;
	saveKeys();
}

InfInt *RSA::encryption(const std::__cxx11::string &message) {
	InfInt *cryptogram;
	std::string crypto;
//    std::cout << "Encrypting: \"" << message << "\"" << std::endl;

    InfInt aux;
	_slice = (int*) malloc(message.size() * sizeof(int));
//	std::cout << "Encrypting!" << std::endl;
	for(unsigned int i=0; i < message.size(); i++) {
		aux = message[i];
//		std::cout << "Aux before mod: " << aux << std::endl;
		aux = utils::modPow(aux, _publicKey, _modulus);
//		std::cout << "Aux after mod: " << aux.toString() << '\n';
		_slice[i] = aux.numberOfDigits();
//		std::cout << "Slice value: " << _slice[i] << std::endl;
		crypto += aux.toString();
    }
	cryptogram = new InfInt(crypto);
	return cryptogram;
}

void RSA::decryption(std::__cxx11::string &dec, InfInt *criptogram) {
	std::string interm = criptogram->toString();
//	std::cout << "Decrypting!" << std::endl;
	std::cout << interm << std::endl;
	for(unsigned int i = 0, j = 0; i < criptogram->numberOfDigits(); i += _slice[j], j++) {
//		std::cout << "i = " << i << " j = " << j << " i + slice: " << i + _slice[j] << std::endl;
		InfInt aux = interm.substr(i, _slice[j]);
//		std::cout << "Slice value: " << _slice[j] << std::endl;
//		std::cout << "Aux substring: " << aux.toString() << std::endl;
		aux = utils::modPow(aux, _privateKey, _modulus);
//		std::cout << "Aux after pow: " << aux.toString() << std::endl;
		dec += (char) aux.toInt();
	}
}
