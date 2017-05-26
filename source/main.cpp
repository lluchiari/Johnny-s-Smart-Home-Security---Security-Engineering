#include <iostream>
#include <include/rsa.hh>
#include <include/InfInt.h>
#include <include/utils.hh>

int main(int argc, char *argv[]) {
	RSA a;
	std::cout << "GCD(32847383182641798246782164327, 29837435283176407123461320987): " << utils::gcd("32847383182641798246782164327", "29837435283176407123461320987") << std::endl;
    return 0;
}
