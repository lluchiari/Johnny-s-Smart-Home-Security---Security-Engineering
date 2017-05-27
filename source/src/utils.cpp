#include <include/utils.hh>
#include <include/millerRabin.hh>

namespace utils {
	InfInt gcd(InfInt x, InfInt y) {
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

	InfInt infAbs(InfInt a) {
		return (a < 0 ? a *= -1 : a);
	}

	void genRandomString(char *s, const int len) {
		static const char num[] = "0123456789";

		for (int i = 0; i < len; ++i) {
			s[i] = num[rand() % (sizeof(num) - 1)];
			if(!i && s[i]=='0'){s[i] = '1';}
		}
		s[len] = 0;
	}
}
