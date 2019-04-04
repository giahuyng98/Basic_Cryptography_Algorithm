#include "caesar.hpp"
#include "monoalphabetic.hpp"
#include "playfair.hpp"
#include "parse_args.hpp"

int main(int argc, char *argv[]){
    ParseArgs arg(argc, argv);

    auto show_usage = [&](){
        std::cerr <<
                  "Usage: " + std::string(argv[0]) + " " + "[Options]...\n"
                  "Options:\n"
                  "-h:              show this help.\n"
                  "-a <algorithm>:  en/de code algorithm.\n"
                  "    c:           caesar.\n"
                  "    m:           monoalphabetic.\n"
                  "    p:           playfair.\n"
                  "    h:           hill cipher.\n"
                  "    v:           vigenere.\n"
                  "    o:           one time pad.\n"
                  "-e <text>:       encode <text>.\n"
                  "-d <text>:       decode <text>.\n"
                  "-k <key>:        key be used to en/de code algorithm.\n"
                  "\nExample: encrypt string \"ptithcm\" with key 5 using caesar algorithm\n"
                  "         " + std::string(argv[0]) + " -a c -e ptithcm -k 5\n"
                  "\nNotes: \n"
                  "<text> contain ALPHABET CHARACTER ONLY.\n"
                  "<key> should depend on cipher algorithm, follow below:\n"
                  "  -a c: <key>=int.\n"
                  "  -a m: <key>=26 distinct alphabet character.\n"
                  "  -a p: <key>=string.\n"
                  "  -a h: <key>=3x3 matrix e.g 17,17,5,21,18,21,2,2,19 .\n"
                  "  -a v: <key>=string.\n"
                  "  -a o: <key>=string with length = <text>.\n"
                  "\nFor bug report, please see:\n"
                  "<https://github.com/giahuyng98/Basic_Cryptography_Algorithm>\n"
                  ;
    };


    using Str = std::string;
    using Func = std::function<Str(const Str &, const Str &)>;
    
    std::map<char, std::pair<Func, Func>> lookup = {
        {'c', {caesar_encrypt, caesar_decrypt}},
        {'m', {monoalphabetic_encrypt, monoalphabetic_decrypt}},
        {'p', {playfair_encrypt, playfair_decrypt}}
    };

    auto err = [&](int code = 1){
        show_usage();
        exit(code);
    };
    if (argc <= 1) err();
    if (arg.exist("-h")) err(0);

    Str algo = arg.get("-a") + " ";
    Str plain_text = remove_not_alpha(to_upper(arg.get("-e")));
    Str cipher_text = remove_not_alpha(to_upper(arg.get("-d")));
    Str key = to_upper(arg.get("-k"));

    try{
        auto itr = lookup.find(algo[0]);
        if (itr == lookup.end()) 
            throw "Invalid algorithm!\n";
        if (!plain_text.empty()) {
            std::cout << itr->second.first(plain_text, key) << "\n";
        } else if (!cipher_text.empty()){
            std::cout << itr->second.second(cipher_text, key) << "\n";
        } else throw "Invalid agruments!\n";

    } catch (const char *e){
        std::cerr << e << "\n";
        err();
    }
}
