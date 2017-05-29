#include <include/rsa.hh>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string.h>

RSA::RSA() {
	_canGenerate = false;
}

RSA::RSA(int bits) {
	_canGenerate = true;
	_p = MillerRabin::randomPrime(bits / 8);
	usleep(1000000); // necessário para garantir primos diferentes entre si
	_q = MillerRabin::randomPrime(bits / 8);
//    std::cout << "P: " << _p << "\nQ: " << _q << std::endl;
	_slice = NULL;
}

RSA::RSA(InfInt p, InfInt q) {
	_canGenerate = true;
	_p = p;
	_q = q;
	_slice =  NULL;
}

RSA::~RSA() {
	if(_slice != NULL)
		free(_slice);
}

int RSA::loadPublicKey(std::string filename) {
    std::ifstream file(filename);
	std::string line, key, mod;
	if(file.is_open()) {
		std::getline(file, line);
		std::size_t found = line.find("Public");
		if(found != std::string::npos) {
			// A chave privada está no arquivo
            while(std::getline(file, line) && line.find("Modulus") == std::string::npos) { // Lendo chave pública
				key.append(line);
			}
			while(std::getline(file, line)) { // Lendo módulo
				mod.append(line);
			}
            std::cout << "Key-_: " <<key << "\n";
            std::cout << "Modulus__: " << mod << "\n";
			_publicKey = key;
			_modulus = mod;
        }
        else {
			std::cerr << "Error on load public key! Corrupt file\n";
			return -2;
		}
	} else {
		std::cerr << "Error on load public key! Unable to open file\n";
        return -1;
    }
    return 1;
}

int RSA::loadPrivateKey(std::string filename) {
    std::ifstream file(filename);
	std::string line;
	std::string key;
	std::string mod;
	if(file.is_open()) {
		std::getline(file, line);
        std::size_t found = line.find("Private");
		if(found != std::string::npos) {
			// A chave privada está no arquivo
            while(std::getline(file, line) && line.find("Modulus") == std::string::npos) { // Lendo chave privada
				key.append(line);
			}
			while(std::getline(file, line)) { // Lendo módulo
				mod.append(line);
			}
            std::cout << "Key: " <<key << "\n";
            std::cout << "Modulus: " << mod << "\n";
			_privateKey = key;
			_modulus = mod;
		} else {
			std::cerr << "Error on load private key! Corrupt file\n";
			return -2;
		}
	} else {
		std::cerr << "Error on load private key! Unable to open file\n";
        return -1;
    }
    return 1;
}

int RSA::saveKeys() {
    std::ofstream pubKey, privKey;

    /* Opening Public Key File */
    pubKey.open("keys.pub");
    if(pubKey.is_open()) {
        pubKey << "Public:\n" << _publicKey << "\n";
        pubKey << "Modulus:\n" << _modulus << "\n";
        pubKey.close();
	}
    else
    {
        std::cerr << "Error on opening file\n";
        return -1;
    }
    privKey.open("keys.pri");

    /* Opening Private Key File */
    if(privKey.is_open()) {
        privKey << "Private:\n" << _privateKey << "\n";
        privKey << "Modulus:\n" << _modulus << "\n";
        privKey.close();
    }
    else
    {
        std::cerr << "Error on opening file\n";
        return -1;
    }
    pubKey.close();
    privKey.close();
    return 1;
}

/**
 * @brief RSA::generateKey método de geração de chaves pública e privada
 * @variable n, módulo da chave
 * @variable x, totiente de n
 * @variable e, expoente da fórmula da chave pública
 * @variable d, expoente da fórmula da chave privada
 */
void RSA::generateKey() {
	if(!_canGenerate) /// Adicionar retorno de erro!
		return;
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
	if(privValues.first < 0)
		privValues.first += n;
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

    InfInt aux;
	_slice = (int*) malloc(message.size() * sizeof(int));
	for(unsigned int i=0; i < message.size(); i++) {
		aux = message[i];
		aux = utils::modPow(aux, _publicKey, _modulus);
		_slice[i] = aux.numberOfDigits();
		crypto += aux.toString();
    }
	cryptogram = new InfInt(crypto);
	return cryptogram;
}

void RSA::decryption(std::__cxx11::string &dec, InfInt *criptogram) {
	std::string interm = criptogram->toString();
	std::cout << interm << std::endl;
	for(unsigned int i = 0, j = 0; i < criptogram->numberOfDigits(); i += _slice[j], j++) {
		InfInt aux = interm.substr(i, _slice[j]);
		aux = utils::modPow(aux, _privateKey, _modulus);
		dec += (char) aux.toInt();
	}
}
