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
	inline InfInt gcd(InfInt x, InfInt y) {
		InfInt g = 1;
		InfInt a, b, u, v;
		InfInt A, B, C, D;

		while((x % 2 == 0) && (y % 2 == 0)) {
			x /= 2;
			y /= 2;
			g *= 2;
		}

		u = x;
		v = y;
		A = D = 1;
		B = C = 0;

		do {
			while(u % 2 == 0) {
				u /= 2;
				if((A % 2 == 0) && (B % 2 == 0)) {
					A /= 2;
					B /= 2;
				} else {
					A = (A + y)/2;
					B = (B - x)/2;
				}
			}

			while(v % 2 == 0) {
				v /= 2;
				if((C % 2 == 0) && (D % 2 == 0)) {
					C /= 2;
					D /= 2;
				} else {
					C = (C + y)/2;
					D = (D - x)/2;
				}
			}

			if(u >= v) {
				u -= v;
				A -= C;
				B -= D;
			} else {
				v -= u;
				C -= A;
				D -= B;
			}
		} while(u != 0);

		a = C;
		b = D;
		return g*v;
	}

	/**
	 * @brief infAbs, calcula o valor absoluto do número 'a'
	 * @param a
	 * @return Valor absoluto de 'a'
	 */
	inline InfInt infAbs(InfInt a) {
		return (a < 0 ? a *= -1 : a);
	}
}


#endif // UTILS_HH
