
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

// AES S-Box
// TODO: Insert complete AES S-Box values
static const unsigned char sBox[256] = {
    0x00
};

// AES Inverse S-Box
// TODO: Insert complete AES Inverse S-Box values
static const unsigned char invSBox[256] = {
    0x00
};

// AES Rcon
static const unsigned char Rcon[10] = {
    0x01, 0x02, 0x04, 0x08, 0x10,
    0x20, 0x40, 0x80, 0x1B, 0x36
};

string stringToHex(const string& input) {
    stringstream hexStream;
    hexStream << hex << setfill('0');

    for (char c : input) {
        hexStream << setw(2)
                  << static_cast<int>(static_cast<unsigned char>(c));
    }

    return hexStream.str();
}

void printState(const vector<vector<unsigned char>>& state) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << hex << setw(2)
                 << setfill('0')
                 << (int)state[j][i];
        }
        cout << endl;
    }
    cout << endl;
}

void rotWord(vector<unsigned char>& word) {
    unsigned char temp = word[0];

    for (int i = 0; i < 3; ++i) {
        word[i] = word[i + 1];
    }

    word[3] = temp;
}

void subWord(vector<unsigned char>& word) {
    for (int i = 0; i < 4; ++i) {
        word[i] = sBox[word[i]];
    }
}

void keyExpansion(
    const vector<unsigned char>& key,
    vector<vector<unsigned char>>& expandedKey
) {
    int keySize = key.size() / 4;
    int expandedKeySize = expandedKey.size();

    for (int i = 0; i < keySize; ++i) {
        for (int j = 0; j < 4; ++j) {
            expandedKey[i][j] = key[i * 4 + j];
        }
    }

    vector<unsigned char> temp(4);

    for (int i = keySize; i < expandedKeySize; ++i) {

        for (int j = 0; j < 4; ++j) {
            temp[j] = expandedKey[i - 1][j];
        }

        if (i % keySize == 0) {
            rotWord(temp);
            subWord(temp);
            temp[0] ^= Rcon[i / keySize - 1];
        }

        for (int j = 0; j < 4; ++j) {
            expandedKey[i][j] =
                expandedKey[i - keySize][j] ^ temp[j];
        }
    }
}

void addRoundKey(
    vector<vector<unsigned char>>& state,
    const vector<vector<unsigned char>>& roundKey
) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            state[j][i] ^= roundKey[j][i];
        }
    }
}

void subBytes(vector<vector<unsigned char>>& state) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            state[i][j] = sBox[state[i][j]];
        }
    }
}

void invSubBytes(vector<vector<unsigned char>>& state) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            state[i][j] = invSBox[state[i][j]];
        }
    }
}

void shiftRows(vector<vector<unsigned char>>& state) {
    vector<unsigned char> temp(4);

    for (int i = 1; i < 4; ++i) {

        for (int j = 0; j < 4; ++j) {
            temp[j] = state[i][(j + i) % 4];
        }

        for (int j = 0; j < 4; ++j) {
            state[i][j] = temp[j];
        }
    }
}

void invShiftRows(vector<vector<unsigned char>>& state) {
    vector<unsigned char> temp(4);

    for (int i = 1; i < 4; ++i) {

        for (int j = 0; j < 4; ++j) {
            temp[j] = state[i][(j - i + 4) % 4];
        }

        for (int j = 0; j < 4; ++j) {
            state[i][j] = temp[j];
        }
    }
}

unsigned char gfMul(unsigned char a, unsigned char b) {
    unsigned char p = 0;

    for (int i = 0; i < 8; ++i) {

        if (b & 1)
            p ^= a;

        bool hiBitSet = a & 0x80;

        a <<= 1;

        if (hiBitSet)
            a ^= 0x1b;

        b >>= 1;
    }

    return p;
}

void mixColumns(vector<vector<unsigned char>>& state) {
    unsigned char temp[4];

    for (int i = 0; i < 4; ++i) {

        temp[0] =
            gfMul(0x02, state[0][i]) ^
            gfMul(0x03, state[1][i]) ^
            state[2][i] ^
            state[3][i];

        temp[1] =
            state[0][i] ^
            gfMul(0x02, state[1][i]) ^
            gfMul(0x03, state[2][i]) ^
            state[3][i];

        temp[2] =
            state[0][i] ^
            state[1][i] ^
            gfMul(0x02, state[2][i]) ^
            gfMul(0x03, state[3][i]);

        temp[3] =
            gfMul(0x03, state[0][i]) ^
            state[1][i] ^
            state[2][i] ^
            gfMul(0x02, state[3][i]);

        for (int j = 0; j < 4; ++j) {
            state[j][i] = temp[j];
        }
    }
}

vector<unsigned char> parseHex(const string& hexStr) {
    vector<unsigned char> result;

    for (size_t i = 0; i < hexStr.length(); i += 2) {
        string byteStr = hexStr.substr(i, 2);

        unsigned char byte =
            (unsigned char)strtol(
                byteStr.c_str(),
                nullptr,
                16
            );

        result.push_back(byte);
    }

    return result;
}

int main() {
    cout << "AES implementation loaded." << endl;
    cout << "S-Box tables are required for full encryption testing." << endl;

    return 0;
}

