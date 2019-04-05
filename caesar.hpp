#include "util.hpp"

const int ALPHA_NUM = 26;

string caesar_encrypt(const string &text, const string &key){
    string result;
    result.reserve(text.length());
    int int_key = std::stoi(key);
    for(char c : text){
        result.push_back('A' + (c - 'A' + int_key) % ALPHA_NUM);
    }
    return result;
}

string caesar_decrypt(const string &cipher_text, const string &key){
    string result;
    result.reserve(cipher_text.length());
    int int_key = std::stoi(key);
    for(char c : cipher_text){
        result.push_back('A' + (c - 'A' - int_key + ALPHA_NUM) % ALPHA_NUM);
    }
    return result;
}

