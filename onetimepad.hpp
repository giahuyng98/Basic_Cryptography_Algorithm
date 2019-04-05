#include "util.hpp"

bool is_valid_onetimepad(const string &text, const string &key){
    return (text.length() == key.length());
}

string onetimepad_encrypt(const string &text, const string &key){
    if (!is_valid_onetimepad(text, key)) 
        throw "Invalid key!";
    string result;
    result.reserve(text.length());
    for(size_t i = 0; i < text.length(); ++i){
        result.push_back(to_char(
        (to_int(text[i]) + to_int(key[i])) % ALPHA_NUM));
    }
    return result;
}

string onetimepad_decrypt(const string &cipher_text, const string &key){
    if (!is_valid_onetimepad(cipher_text, key)) 
        throw "Invalid key!";
    string result;
    result.reserve(cipher_text.length());
    for(size_t i = 0; i < cipher_text.length(); ++i){
        result.push_back(to_char(
        (to_int(cipher_text[i]) - to_int(key[i]) + ALPHA_NUM) % ALPHA_NUM));
    }
    return result;
}
