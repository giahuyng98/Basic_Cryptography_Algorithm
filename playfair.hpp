#include "util.hpp"

vector<vector<char>> create_playfair_matrix(string key){
    vector<vector<char>> matrix(5, vector<char>(5, '#'));
    bitset<26> used;
    for(char &c : key){
        if (c == 'J') c = 'I';
    }

    char current_char = 'A';
    size_t pos = 0;
    used[to_int('J')] = 1;

    for(auto &m : matrix){
        for(char &c : m){
            for(; pos < key.size() && c == '#'; ++pos){
                if (!used[to_int(key[pos])]) 
                    c = key[pos];
            }
            for(; c == '#'; ++current_char){
                if (!used[to_int(current_char)])
                    c = current_char;
            }
            used[to_int(c)] = 1;
        }
    }
    return matrix;
}
vector<pair<int,int>> create_pos_matrix(vector<vector<char>> const &matrix){
    vector<pair<int,int>> pos(26);
    for(int i = 0; i < 5; ++i){
        for(int j = 0; j < 5; ++j){
            pos[to_int(matrix[i][j])] = {i, j};
        }
    }
    pos[to_int('J')] = pos[to_int('I')];
    return pos;
}

string playfair_util(const string &text, const string &key, const std::function<int(int)> &func){
    auto mat = create_playfair_matrix(key);
    auto pos = create_pos_matrix(mat);
    string result;
    result.reserve(text.length() + 1);

    auto add = [&](const pair<int,int> &pos1, const pair<int,int> &pos2){
        if (pos1.first == pos2.first){
            //same row
            result.push_back(mat[pos1.first][func(pos1.second)]);
            result.push_back(mat[pos2.first][func(pos2.second)]);
        } else if (pos1.second == pos2.second){
            //same col
            result.push_back(mat[func(pos1.first)][pos1.second]);
            result.push_back(mat[func(pos2.first)][pos2.second]);
        } else {
            //diff row && diff col
            result.push_back(mat[pos1.first][pos2.second]);
            result.push_back(mat[pos2.first][pos1.second]);
        }
    };

    size_t i = 0;
    for(;;){
        if (i + 1 >= text.length()) break;
        char ch1 = toupper(text[i]);
        char ch2 = toupper(text[i + 1]);
        if (ch1 == ch2){
            ch2 = 'X';
            ++i;
        } else i += 2;
        add(pos[to_int(ch1)], pos[to_int(ch2)]);
    }
    // remain 1 character
    if (i < text.length()){
        add(pos[to_int(text[i])], pos[to_int('X')]);
    }
    
    return result;
}

string playfair_encrypt(const string &text, const string &key){
    return playfair_util(text, key, [](int pos){return (pos + 1) % 5;});
}

string playfair_decrypt(const string &text, const string &key){
    return playfair_util(text, key, [](int pos){return (pos + 4) % 5;});
}
