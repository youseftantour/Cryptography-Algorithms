
#include <iostream>
#include <cmath>

using namespace std;

// Function to check if a number is prime
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;

    if (n % 2 == 0 || n % 3 == 0)
        return false;

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }

    return true;
}

// Function to find greatest common divisor
int gcd(int a, int b) {
    if (b == 0)
        return a;

    return gcd(b, a % b);
}

// Function to find modular inverse
int modInverse(int a, int m) {
    int m0 = m;
    int y = 0;
    int x = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        int q = a / m;
        int t = m;

        m = a % m;
        a = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    if (x < 0)
        x += m0;

    return x;
}

// Function to generate RSA keys
void generateKeys(int p, int q, int& e, int& d, int& n) {

    if (!isPrime(p) || !isPrime(q)) {
        cout << "Error: Both numbers must be prime." << endl;
        return;
    }

    n = p * q;

    int phi = (p - 1) * (q - 1);

    for (e = 2; e < phi; e++) {
        if (gcd(e, phi) == 1)
            break;
    }

    d = modInverse(e, phi);
}

// Function to encrypt a message
int encrypt(int msg, int e, int n) {
    return (int)pow(msg, e) % n;
}

// Function to decrypt a message
int decrypt(int encryptedMsg, int d, int n) {
    return (int)pow(encryptedMsg, d) % n;
}

int main() {

    int p, q;

    cout << "RSA Encryption and Decryption" << endl;
    cout << "-----------------------------" << endl;

    cout << "Enter first prime number (p): ";
    cin >> p;

    cout << "Enter second prime number (q): ";
    cin >> q;

    if (!isPrime(p) || !isPrime(q)) {
        cout << "Error: Both numbers must be prime." << endl;
        return 1;
    }

    int e, d, n;

    generateKeys(p, q, e, d, n);

    cout << "\nGenerated Keys" << endl;
    cout << "--------------" << endl;
    cout << "Public Key (e, n): (" << e << ", " << n << ")" << endl;
    cout << "Private Key (d, n): (" << d << ", " << n << ")" << endl;

    int message;

    cout << "\nEnter a numeric message to encrypt: ";
    cin >> message;

    if (message >= n) {
        cout << "Error: Message must be smaller than n (" << n << ")." << endl;
        return 1;
    }

    int encryptedMessage = encrypt(message, e, n);

    cout << "\nEncrypted Message: "
         << encryptedMessage << endl;

    int decryptedMessage =
        decrypt(encryptedMessage, d, n);

    cout << "Decrypted Message: "
         << decryptedMessage << endl;

    if (decryptedMessage == message) {
        cout << "\nRSA Test Passed Successfully!" << endl;
    } else {
        cout << "\nRSA Test Failed!" << endl;
    }

    return 0;
}
