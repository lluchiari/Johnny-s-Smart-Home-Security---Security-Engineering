#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <string>
#include <exception>
#include <unistd.h>
#include <include/rsa.hh>
#include <include/InfInt.h>
#include <include/utils.hh>
#include <include/millerRabin.hh>

#define PROGRAM_OPTIONS 4
#define MIN_KEY_LENGTH 1
#define MAX_KEY_LENGTH 1024


static void show_usage(std::string name) {
    std::cerr << "Usage: " << name << " <option(s)> SOURCES\n"
              << "Options:\n"
              << "\t-h,--help\t\t\t\t\tShow this help message\n"
              << "\t-g,--generate-key [KEY_SIZE]\t\t\t\tGenerates the key pair with the [KEY_SIZE] in bits.\n"
              << "\t-e,--encrypt [PUBLIC_KEY] [MESSAGE]\t\tEncrypt a [MESSAGE] file based on the [PUBLIC_KEY] file.\n"
              << "\t-d,--decrypt [PRIVATE_KEY] [CRYPTOGRAM]\t\tDecrypt a [CRYPTOGRAM] file based on the [PRIVATE_KEY] file.\n"
              << std::endl;
}

int main(int argc, char *argv[]) {

#ifndef DEBUG
        /* Checking Command Line Arguments */
        if (argc < 2) {
            std::cout << argv[0] << " invalid option!\nTry '"<< argv[0]
								 << " --help' for more information.\n";
            return -1;
        }

        /* Create the vector of flags. It is usefull for more than one command in the same line*/
        bool flags[PROGRAM_OPTIONS];
        for(int i=0; i< PROGRAM_OPTIONS; i++){flags[i] = false;}

        /* Variable to set the length of the keys */
        int KeyResolution;

        std::vector<std::string> source;
        //std::string destination;

        /* Loop Case to Evaluate all the commands */
        for (int i = 1; i < argc; ++i) {

            /* Auxiliar Variable storing the argument*/
            std::string arg = argv[i];

            /* Command HELP --> Without flags (it's a sovereign command)*/
            if ((arg == "-h") || (arg == "--help")) {
                std::string aux = argv[0];
                std::string filename = aux.substr(0, aux.find("."));
                show_usage(filename);
                return 0;
            }
			/* Command GENERATE KEY --> flags[0] */
			else if((arg == "-g")|| (arg == "--generate-key")) {
                if (i + 1 < argc) {
                    /* Increment 'i' so we don't get the argument as the next argv[i]. */
                    KeyResolution = std::stoi(argv[++i], nullptr, 10);
                    if((KeyResolution < MIN_KEY_LENGTH) && (KeyResolution > MAX_KEY_LENGTH))
                    {
                        std::cerr << "Error: Invalid Key Size!\n";
                        return -1;
                    }
                }
                /* Uh-oh, there was no argument to the destination option. */
                else {
                    std::cerr << "Missing Key Size argument. For more information see --help!" << std::endl;
                    return -1;
                }
                flags[0] = true;
            }
            /* Command ENCRYPT --> flags[1] */
			else if((arg == "-e")|| (arg == "--encrypt")) {
                /* Make sure we aren't at the end of argv! */
                if (i + 2 < argc) {
                    /* Increment 'i' so we don't get the argument as the next argv[i]. */
                    source.push_back(argv[++i]);                    // public key file
                    source.push_back(argv[++i]);                   // message file
                }
                /* Uh-oh, there was no argument to the destination option. */
				else {
                    std::cerr << "--encrypt option requires two argument. See --help for more information" << std::endl;
                    return -1;
                }
                flags[1] = true;
            }
            /* Command DECRYPT --> flags[2] */
			else if((arg == "-d")|| (arg == "--decrypt")) {
                /* Make sure we aren't at the end of argv! */
                if (i + 2 < argc) {
                    /* Increment 'i' so we don't get the argument as the next argv[i]. */
                    source.push_back(argv[++i]);                    // private key file
                    source.push_back(argv[++i]);                   // cryptogram file
                }
                /* Uh-oh, there was no argument to the destination option. */
                else {
                    std::cerr << "--decrypt option requires two argument. See --help for more information" << std::endl;
                    return -1;
                }
                flags[2] = true;
            }
            /* Command ENCRYPT GENERATE KEY --> flags[2] */
			else if((arg == "-eak")|| (arg == "--encrypt-assimetric-key")) {

            }
            /* Command GUI --> flags[2] */
			else if((arg == "-gui")|| (arg == "--graphical")) {

            }
			else {
                show_usage(argv[0]);
                return -1;
            }
        }


        /* Flags Parser */

        /* Generate key pair */
        if(flags[0]) {
            RSA program(KeyResolution);
            program.generateKey();
            if(program.saveKeys() == -1)
            {
                std::cerr << "Error on opening key files\n";
                return -1;
            }
            return 0;
        }
        /* Encrypting */
        else if(flags[1])
        {
            RSA program;
			std::string message;

            /* Load the key */
            if(program.loadPublicKey(source.at(0)) < 0) {
                std::cerr << "Error loading public key" << std::endl;
                return -1;
            }

            /* Loading the message */
			try {
				message = utils::loadFromFile(source.at(1));
            }
			catch(const char *err) {
                std::cerr << err << std::endl;
                return -1;
            }

            /* Verify if the message is not empty */
			if(message.size() <= 0) {
				std::cerr << "Error reading the Message" << std::endl;
                return -1;
            }

            InfInt *cryptogram;

            /* Proccess the encryptation process itself */
            cryptogram = program.encryption(message);
            std::string filename = source.at(1).substr(0, source.at(1).find("."));
			try {
                std::string aux = cryptogram->toString();
                utils::writeToFile(aux, filename.append(".cript"));
            }
			catch(const char *err) {
                std::cerr << err << std::endl;
            }

            delete(cryptogram);
            return 0;
        }
        /* Decrypting */
        else if(flags[2]) {
            RSA program;
            std::string aux;

            /* Load the key */
            if(program.loadPrivateKey(source.at(0)) < 0) {
                std::cerr << "Error loading public key" << std::endl;
                return -1;
            }

            /* Loading the cryptogram */
            try {
                aux = utils::loadFromFile(source.at(1));
            }
            catch(const char *err) {
                std::cerr << err << std::endl;
                return -1;
            }

            InfInt cryptogram = aux;

            /* Verify if the cryptogram is not empty */
            if(cryptogram.size() <= 0) {
                std::cerr << "Error reading the cryptogram" << std::endl;
                return -1;
            }

            std::string message;

            /* Proccess the encryptation process itself */
            program.decryption(message, &cryptogram);
            std::string filename = source.at(1).substr(0, source.at(1).find("."));
            try {
                utils::writeToFile(message, filename.append(".txt"));
            }
            catch(const char *err) {
                std::cerr << err << std::endl;
            }
            return 0;
        }

#else

//    InfInt p = "48851171585780512151872007066472568695045543717924031431249006254046862338909894217562808709546250056289399470894742242014198835030971020078279856090415247";
//    InfInt q = "17156034090577232334004270995267972777289456282615237656675311020498416361101565288066643474796857699447787935485481067506985762542608378284942492718479329";
    //InfInt pq = "30849821653687123463303337813366340344631999834490732265076505139386759060955395380528245195629759344443748279939181018527300477332078364394207345648412271";
//	InfInt p = "18532395500947174450709383384936679868383424444311405679463280782405796233163977";
//	InfInt q = "39688644836832882526173831577536117815818454437810437210221644553381995813014959";

    //InfInt p = "154725368117940698788029053217798887175214759640744378541226187572025414018010181004439221967045836431399408128455038077191873040800659709605935985084899530753233413028684685152782225472103307582636553459294347054889505097412841939917674271786860290832603626651911507603833436210130113055877637427181462712487";
    //InfInt q = "119066337892944497659274447260782976472330933532973728367702305819889080235208144711826032422469638636165988175365563491392888258760951411989700747304780091452449377384804618419099627425891439127996909654253632370887891785795670014023990698293616870256764888928945330566936192067895773774570307726662717965503";

	RSA test(1024);
    test.generateKey();
//	std::string message = "Eu tinha uma galinha que se chamava Mary Lu.";
//	std::string message = "A z";
	std::string message = "Eu estou testando a ?Criptografia!%!@#$%*()RSA! |\\/:;^~[]{}+=";
	InfInt *cryptogram;
	cryptogram = test.encryption(message);

	std::cout << "Message: "<< message << std::endl << "Cryptogram: " << cryptogram->toString() << std::endl;
	std::string nMessage;
	test.decryption(nMessage, cryptogram);
	std::cout << "Message decrypted: " << nMessage << std::endl;
	free (cryptogram);
    return 0;
#endif
}


