#ifndef _RSA_HH_
#define _RSA_HH_

#include <iostream>
#include <string>
#include <cstring>
#include "InfInt.h"
#include "utils.hh"
#include "millerRabin.hh"

class RSA {
public:
	RSA();
	/**
	 * @brief RSA::RSA  construtor da classe em que o número de bits de cada número primo é passado para que sejam gerados.
	 * A chave resultante terá o dobro de bits.
	 * @param bits número de bits de cada número primo.
	 */
    RSA(int bits);

	/**
	 * @brief RSA::RSA construtor da classe em que os dois números primos são enviados para geração da chave
	 * @param p primeiro primo
	 * @param q segundo primo
	 */
	RSA(InfInt p, InfInt q);
    ~RSA();

	/**
	 * @brief RSA::loadPrivateKey método de leitura da chave privada salva em um arquivo localmente
	 * @param filename nome do arquivo contendo a chave
	 * @return	1, caso a leitura tenha sido bem sucedida
	 *			-1, caso não tenha sido possível abrir o arquivo
	 *			-2, caso o arquivo esteja corrompido ou não salvo corretamente
	 */
    int loadPrivateKey(std::string filename);

	/**
	 * @brief RSA::loadPublicKey método de leitura da chave pública salva em um arquivo localmente
	 * @param filename nome do arquivo contendo a chave
	 * @return	1, caso a leitura tenha sido bem sucedida
	 *			-1, caso não tenha sido possível abrir o arquivo
	 *			-2, caso o arquivo esteja corrompido ou não salvo corretamente
	 */
    int loadPublicKey(std::string filename);

	/**
	 * @brief RSA::generateKey método de geração de chaves pública e privada
	 * @variable n, módulo da chave
	 * @variable x, totiente de n
	 * @variable e, expoente da fórmula da chave pública
	 * @variable d, expoente da fórmula da chave privada
	 */
    void generateKey();

	/**
	 * @brief encryption método de encriptação de mensagens. Recebe a mensagem em texto plano ASCII e gera um novo
	 * arquivo de mesmo nome do recebido, mas com a extensão .crypt, contendo as separações e a cifra da mensagem.
	 * @param message mensagem a ser encriptada
	 * @param filename nome do arquivo contendo o texto plano
	 * @return retorna a ciffra completa da mensagem.
	 */
	InfInt *encryption(const std::__cxx11::string &message, std::__cxx11::string filename);

	/**
	 * @brief decryption método de decriptação de mensagens, lê a cifra em um arquivo e, a partir da chave privada,
	 * gera de volta o texto plano.
	 * @param dec string onde o texto plano será inserido e retornado
	 * @param filedata nome do arquivo .crypto
	 */
	void decryption(std::string &dec, std::string &filedata);

	/**
	 * @brief RSA::saveKeys método de salvamento das chaves em dois arquivos, keys.pub e keys.pri,
	 * contendo a chave pública e a privada, respectivamente.
	 * @return
	 */
    int saveKeys();



private:
	InfInt _privateKey;
	InfInt _publicKey;
	InfInt _modulus;
	InfInt _p, _q;
	std::vector<int> _slice;
	bool _canGenerate;

	InfInt interpretCypherFile(std::string &data);
};

#endif
