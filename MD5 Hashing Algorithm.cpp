#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
#include <sstream>

using namespace std;

uint32_t leftRotate(uint32_t x, uint32_t c) {
    return (x << c) | (x >> (32 - c));
}

string simpleMD5(const string &input) {
    vector<uint32_t> r = {
        7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
        5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20,
        4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
        6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
    };
    
    vector<uint32_t> k(64);
    for (uint32_t i = 0; i < 64; i++) {
        k[i] = static_cast<uint32_t>(floor(abs(sin(i + 1)) * pow(2, 32)));
    }
    uint32_t messageLength = input.size() * 8;
    string paddedInput = input + char(0x80);
    while ((paddedInput.size() * 8) % 512 != 448) {
        paddedInput += char(0x00);
    }
    
    for (int i = 0; i < 8; i++) {
        paddedInput += char((messageLength >> (i * 8)) & 0xFF);
    }
    uint32_t a0 = 0x67452301;
    uint32_t b0 = 0xEFCDAB89;
    uint32_t c0 = 0x98BADCFE;
    uint32_t d0 = 0x10325476;
    for (size_t chunk = 0; chunk < paddedInput.size(); chunk += 64) {
        uint32_t m[16];
        for (int i = 0; i < 16; i++) {
            m[i] = (uint8_t)paddedInput[chunk + i * 4 + 0] |
                   ((uint8_t)paddedInput[chunk + i * 4 + 1] << 8) |
                   ((uint8_t)paddedInput[chunk + i * 4 + 2] << 16) |
                   ((uint8_t)paddedInput[chunk + i * 4 + 3] << 24);
        }
        uint32_t A = a0;
        uint32_t B = b0;
        uint32_t C = c0;
        uint32_t D = d0;
        
        for (int i = 0; i < 64; i++) {
            uint32_t F, g;
            if (i < 16) {
                F = (B & C) | ((~B) & D);
                g = i;
            } else if (i < 32) {
                F = (D & B) | ((~D) & C);
                g = (5 * i + 1) % 16;
            } else if (i < 48) {
                F = B ^ C ^ D;
                g = (3 * i + 5) % 16;
            } else {
                F = C ^ (B | (~D));
                g = (7 * i) % 16;
            }
            uint32_t temp = D;
            D = C;
            C = B;
            B = B + leftRotate(A + F + k[i] + m[g], r[i]);
            A = temp;
        }
        
        a0 += A;
        b0 += B;
        c0 += C;
        d0 += D;
    }
    stringstream ss;
    ss << hex << setw(8) << setfill('0') << a0
       << setw(8) << setfill('0') << b0
       << setw(8) << setfill('0') << c0
       << setw(8) << setfill('0') << d0;
    return ss.str();
}

int main() {
    string input;
    cout << "Enter the string to hash: ";
    getline(cin, input);
    
    string hash = simpleMD5(input);
    cout << "MD5 Hash: " << hash << endl;
    
    return 0;
}
