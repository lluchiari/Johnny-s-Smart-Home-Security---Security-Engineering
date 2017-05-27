#ifndef UTILS_HH
#define UTILS_HH

#include <include/InfInt.h>

namespace utils {
	/**
	 * @brief gcd, método de cálculo do maior divisor comum (greatest common divisor) entre dois números.
	 * São calculados os valores a, b e v, aplicados na equação ax + by = v, onde v é o maior divisor comum entre x e y.
	 * @param x, Primeiro número
	 * @param y, Segundo número
	 * @return Maior divisor comum entre x e y
	 */
	InfInt gcd(InfInt x, InfInt y);

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
	 * @param p is the modulus
	 * @return (x^y) % p
	 */
	InfInt modPow(InfInt x, InfInt y, InfInt p);

	/**
	 * @brief genRandomString, gera uma string com caracteres aleatórios
	 * @param s
	 * @param len
	 */
	void genRandomString(char *s, const int len);
}


#endif // UTILS_HH
