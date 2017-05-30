#ifndef UTILS_HH
#define UTILS_HH

#include <iostream>
#include <fstream>
#include "InfInt.h"
#include "millerRabin.hh"

namespace utils {
	/**
	 * @brief gcd, função de cálculo do maior divisor comum (greatest common divisor) entre dois números.
	 * São calculados os valores a, b e v, aplicados na equação ax + by = v (mod n), onde v é o maior divisor comum
	 * entre x e y. Caso v = 1, b é divisível por n, logo, x é o inverso multiplicativo modular de a.
	 * Aplicando à foŕmula, temos ex + ny = 1, então d, o valor da chave privada, é o próprio valor x.
	 * @param x, Primeiro número
	 * @param y, Segundo número
	 * @return Maior divisor comum entre x e y
	 */
	void gcd(std::pair<InfInt, InfInt> &results, InfInt x, InfInt y);

	/**
	 * @brief invMul, função de cálculo do multiplicativo inverso de 'a', módulo 'n'
	 * @param a, número a ser 'invertido'
	 * @param n, módulo sobre o qual a conta é feita
	 * @return multiplicativo inverso de 'a' ou 0, caso 'a' não seja inversível
	 */
	InfInt invMul(InfInt a, InfInt n);

	/**
	 * @brief infAbs, calcula o valor absoluto do número 'a'
	 * @param a
	 * @return Valor absoluto de 'a'
	 */
	InfInt infAbs(InfInt a);

	/**
	 * @brief power is a utility function to do modular exponentiation.
	 * @param x is the base
	 * @param y is the exponent
	 * @param m is the modulus
	 * @return (x^y) % m
	 */
	InfInt modPow(InfInt x, InfInt y, InfInt m);

	/**
	 * @brief genRandomString, gera uma string com caracteres aleatórios
	 * @param s
	 * @param len
	 */
	void genRandomString(char *s, const int len);

	/**
	 * @brief loadFromFile function to read all contents of received file
	 * @param filename name of the file to be read
	 * @return contents of the file
	 */
    std::string loadFromFile(std::string filename);

	/**
	 * @brief writeToFile function to write contents in file named 'filename'
	 * @param info entire string of data to be written to file
	 * @param filename name of the filee to be created or overwritten
	 */
	void writeToFile(std::string &info, std::string filename);
}


#endif // UTILS_HH
