#include "util.hpp"

using Mat3x3 = std::array<std::array<int, 3>, 3>;
using Mat3x1 = std::array<std::array<int, 1>, 3>;

Mat3x3 parseMat3x3(string key){
    std::replace(key.begin(), key.end(), ',', ' ');
    std::stringstream ss(key);
    Mat3x3 result;
    for(auto &row : result) 
        for(auto &elem : row) 
            ss >> elem;
    return result;
}

int extended_gcd(int a, int b, int &x, int &y){
    if (a == 0){
        x = 0;
        y = 1;
        return b;
    }
    int x1, y1;
    int g = extended_gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return g;
}

int mod_inverse(int num, int mod){
    num %= mod;
    if (num < 0) num += mod;
    int x, y;
    int g = extended_gcd(num, mod, x, y);
    if (g != 1) return 0;
    return (x % mod + mod) % mod;
}

Mat3x1 operator*(const Mat3x3 &mat1, const Mat3x1 &mat2){
    Mat3x1 result;
    for(int row = 0; row < 3; ++row){
        result[row][0] = 0;
        for(int k = 0; k < 3; ++k){
            result[row][0] = (result[row][0] + mat1[row][k] * mat2[k][0]) % ALPHA_NUM;
            while (result[row][0] < 0) result[row][0] += ALPHA_NUM;
        }
    }
    return result;
}

Mat3x3 get_transpose(const Mat3x3 &mat){
    Mat3x3 result;
    for(int row = 0; row < 3; ++row){
        for(int col = 0; col < 3; ++col){
            result[row][col] = mat[col][row];
        }
    }
    return result;
}

Mat3x3 get_minor_cofactor(const Mat3x3 &mat){
    return Mat3x3{{
    {   mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1],
      -(mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0]),
        mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]
     },
    { -(mat[0][1] * mat[2][2] - mat[0][2] * mat[2][1]),
        mat[0][0] * mat[2][2] - mat[0][2] * mat[2][0],
      -(mat[0][0] * mat[2][1] - mat[0][1] * mat[2][0])
     },
    {   mat[0][1] * mat[1][2] - mat[0][2] * mat[1][1],
      -(mat[0][0] * mat[1][2] - mat[0][2] * mat[1][0]),
        mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0]
     }
    }};
}

int determinant(const Mat3x3 &mat){
    return mat[0][0] * (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1])
         - mat[0][1] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0])
         + mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]);
}

Mat3x3 inverse_mod(const Mat3x3 &mat, int inv_det){
    Mat3x3 tmc = get_minor_cofactor(get_transpose(mat));
    Mat3x3 result;
    for(int row = 0; row < 3; ++row){
        for(int col = 0; col < 3; ++col){
            result[row][col] = (inv_det * tmc[row][col]) % ALPHA_NUM;
        }
    }
    return result;
}

Mat3x3 inverse(const Mat3x3 &mat){
    return inverse_mod(mat, mod_inverse(determinant(mat), 26));
}

string hillcipher_util(const string &str, const Mat3x3 &mat){
    int det = determinant(mat);
    if (det == 0 || mod_inverse(det, ALPHA_NUM) == 0) throw "Not exist reverse matrix or key having common factors with 26\n";
    const string fix_text(str + string(str.length() % 3, 'X'));
    string result;
    result.reserve(fix_text.length());
    for(size_t i = 0; i < fix_text.length(); i += 3){
        Mat3x1 tmp = mat * Mat3x1{{{to_int(fix_text[i])}, {to_int(fix_text[i+1])}, {to_int(fix_text[i+2])}}};
        result.push_back(to_char(tmp[0][0]));
        result.push_back(to_char(tmp[1][0]));
        result.push_back(to_char(tmp[2][0]));
    }
    return result;
}

string hillcipher_encrypt(const string &text, const string &key){
    return hillcipher_util(text, parseMat3x3(key));
}

string hillcipher_decrypt(const string &cipher_text, const string &key){
    return hillcipher_util(cipher_text, inverse(parseMat3x3(key)));
}
