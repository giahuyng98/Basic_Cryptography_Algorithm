#include "util.hpp"
#include <iostream>

bool is_monoalphabetic_key(string key){
    sort(key.begin(), key.end());
    key.resize(std::unique(key.begin(), key.end()) - key.begin());
    return key.size() == ALPHA_NUM;
}
string monoalphabetic_encrypt(const string &text, const string &key){
    string fix_key = remove_not_alpha(key);
    if (!is_monoalphabetic_key(fix_key))
        throw "Error: Key is not valid!\n";
    string result;
    result.reserve(text.length());
    for(char c : text){
        result.push_back(fix_key[c - 'A']);
    }
    return result;
}
string monoalphabetic_decrypt(const string &cipher_text, const string &key){
    string fix_key = remove_not_alpha(key);
    if (!is_monoalphabetic_key(fix_key))
        throw "Error: Key is not valid!\n";
    string result;
    result.reserve(cipher_text.length());
    string look_back(26, ' ');
    char first = 'A';
    for(char c : fix_key){
    	look_back[c - 'A'] = first++;
    }
    for(char c : cipher_text){
        result.push_back(look_back[c - 'A']);
    }
    return result;
}

