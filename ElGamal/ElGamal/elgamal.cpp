
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Modular exponentiation
long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;

    base %= mod;

    while (exp > 0) {

        if (exp % 2 == 1)
            result = (result * base) % mod;

        exp >>= 1;
        base = (base * base) % mod;
    }

    return result;
}

// Random number generation
long long random_number(long long min, long long max) {
    return min + rand() % (max - min + 1);
}

// Key generation
void key_generation(
    long long& p,
    long long& g,
    long long& x,
    long long& y
) {
    cout << "Enter a prime number (p): ";
    cin >> p;

    cout << "Enter a primitive root (g): ";
    cin >> g;

    x = random_number(1, p - 2);

    y = mod_exp(g, x, p);
}

// Encryption
pair<long long, long long> encrypt(
    long long p,
    long long g,
    long long y,
    long long m
) {
    long long k = random_number(1, p - 2);

    long long c1 = mod_exp(g, k, p);

    long long c2 =
        (mod_exp(y, k, p) * m) % p;

    return make_pair(c1, c2);
}

// Decryption
long long decrypt(
    long long p,
    long long x,
    pair<long long, long long> ciphertext
) {
    long long c1 = ciphertext.first;
    long long c2 = ciphertext.second;

    long long s =
        mod_exp(c1, x, p);

    long long m =
        (c2 * mod_exp(s, p - 2, p)) % p;

    return m;
}

int main() {

    srand(time(0));

    long long p, g, x, y;

    cout << "==========================" << endl;
    cout << " ElGamal Encryption Demo " << endl;
    cout << "==========================" << endl;

    key_generation(p, g, x, y);

    cout << "\nPrivate Key (x): "
         << x << endl;

    cout << "Public Key (y): "
         << y << endl;

    long long message;

    cout << "\nEnter a message (number less than p): ";
    cin >> message;

    if (message >= p) {
        cout << "Message must be smaller than p."
             << endl;
        return 1;
    }

    pair<long long, long long> ciphertext =
        encrypt(p, g, y, message);

    cout << "\nCiphertext:" << endl;
    cout << "c1 = " << ciphertext.first << endl;
    cout << "c2 = " << ciphertext.second << endl;

    long long decrypted =
        decrypt(p, x, ciphertext);

    cout << "\nDecrypted Message: "
         << decrypted << endl;

    if (decrypted == message) {
        cout << "\nElGamal Test Passed!" << endl;
    }
    else {
        cout << "\nElGamal Test Failed!" << endl;
    }

    return 0;
}
