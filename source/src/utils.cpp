#include "../include/utils.hh"

namespace utils {

	void gcd(std::pair<InfInt, InfInt> &results, InfInt x, InfInt y) {
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
		results.first = a;
		results.second = g * v;
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

	InfInt modPow(InfInt x, InfInt y, InfInt m) {
		/* Just to Guarantee */
		if(m == 1){ return 0; }
		InfInt res = 1;      // Initialize result
		x %= m;  // Update x if it is more than or
					// equal to p
        while (y > 0) {
			// If y is odd, multiply x with result
			if(y % 2 == 1)
				res = (res*x) % m;

			// y must be even now
			y = y/2; //y = y>>1;
			x = (x*x) % m;
		}
		return res;
	}

	std::string loadFromFile(std::string filename) {
        std::string message;
        std::ifstream file(filename);
		if(file.is_open()) {
            /* Set the cursor to the end of the file */
            file.seekg(0, std::ios::end);
            /* Measure the length of the file and reserve */
            message.reserve(file.tellg());
            /* Return the cursor to the beggining of the file */
            file.seekg(0, std::ios::beg);


            message.assign((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
			file.close();
        }
        else{
            throw "Unable to open the file\n";
        }
        return message;
    }

	void writeToFile(std::string &info, std::string filename) {
        std::ofstream file(filename);
		if(file.is_open()) {
            file << info;
        }
        else{
            throw "Unable to open the file\n";
        }
        file.close();
    }
}
