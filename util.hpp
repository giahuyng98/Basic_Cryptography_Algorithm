#pragma once
#include <cctype>
#include <vector>
#include <bitset>
#include <functional>
#include <algorithm>
#include <string>
#include <map>
#include <unordered_map>
using std::vector;
using std::bitset;
using std::pair;
using std::string;

int to_int(char c){
    return c - 'A';
}

string to_upper(const string &str){
    string result(str);
    for(char &c : result)
        c = toupper(c);
    return result;
}

string remove_not_alpha(const string &text){
    string result;
    result.reserve(text.length());
    for(char c : text){
        if (isalpha(c)) result.push_back(c);
    }
    return result;
}
