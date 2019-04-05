#include "util.hpp"
#include <cassert>

string vigenere_encrypt(const string &text, const string &key){
    string result;
    result.reserve(text.length());
    for(size_t i = 0; i < text.length(); ++i){
        result.push_back(to_char(
        (to_int(text[i]) + to_int(key[i % key.length()])) % ALPHA_NUM));
    }
    return result;
}

string vigenere_decrypt(const string &cipher_text, const string &key){
    string result;
    result.reserve(cipher_text.length());
    for(size_t i = 0; i < cipher_text.length(); ++i){
        result.push_back(to_char(
        (to_int(cipher_text[i]) - to_int(key[i % key.length()]) + ALPHA_NUM) % ALPHA_NUM));
    }
    return result;
}

