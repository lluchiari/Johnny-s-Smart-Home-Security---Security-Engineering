#include <iostream>
#include <include/rsa.hh>
#include <include/InfInt.h>
#include <include/utils.hh>

int main(int argc, char *argv[]) {
//    InfInt p = "154725368117940698788029053217798887175214759640744378541226187572025414018010181004439221967045836431399408128455038077191873040800659709605935985084899530753233413028684685152782225472103307582636553459294347054889505097412841939917674271786860290832603626651911507603833436210130113055877637427181462712487";
//    InfInt q = "119066337892944497659274447260782976472330933532973728367702305819889080235208144711826032422469638636165988175365563491392888258760951411989700747304780091452449377384804618419099627425891439127996909654253632370887891785795670014023990698293616870256764888928945330566936192067895773774570307726662717965503";
//	std::cout << "gcd(" << p.toString() << ", " << q.toString() << "): ";
//	std::cout << utils::gcd(p, q) << std::endl;
//	std::cout << "p * q = " << (p * q).toString() << std::endl;
    RSA test;
    std::cout << test.giveMeARandonPrime(15) << std::endl;
    return 0;
}
