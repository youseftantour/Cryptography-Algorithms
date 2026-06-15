
#include <iostream>
#include <string>

using namespace std;

// Modular exponentiation
long long modExp(long long base, long long exp, long long mod) {
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

// Encrypt message using XOR
string encryptMessage(const string& message, long long key) {
    string encrypted = message;

    for (size_t i = 0; i < message.size(); i++) {
        encrypted[i] = message[i] ^ (key % 256);
    }

    return encrypted;
}

// Decrypt message using XOR
string decryptMessage(const string& encryptedMessage, long long key) {
    string decrypted = encryptedMessage;

    for (size_t i = 0; i < encryptedMessage.size(); i++) {
        decrypted[i] = encryptedMessage[i] ^ (key % 256);
    }

    return decrypted;
}

int main() {

    long long p;
    long long g;

    cout << "====================================" << endl;
    cout << " Diffie-Hellman Key Exchange Demo " << endl;
    cout << "====================================" << endl;

    cout << "\nEnter Prime Number (p): ";
    cin >> p;

    cout << "Enter Primitive Root (g): ";
    cin >> g;

    long long alicePrivate;
    long long bobPrivate;

    cout << "\nEnter Alice's Private Key: ";
    cin >> alicePrivate;

    cout << "Enter Bob's Private Key: ";
    cin >> bobPrivate;

    long long alicePublic = modExp(g, alicePrivate, p);
    long long bobPublic = modExp(g, bobPrivate, p);

    cout << "\nAlice Public Key: " << alicePublic << endl;
    cout << "Bob Public Key: " << bobPublic << endl;

    long long aliceShared =
        modExp(bobPublic, alicePrivate, p);

    long long bobShared =
        modExp(alicePublic, bobPrivate, p);

    cout << "\nAlice Shared Secret: "
         << aliceShared << endl;

    cout << "Bob Shared Secret: "
         << bobShared << endl;

    if (aliceShared == bobShared) {
        cout << "\nKey Exchange Successful!" << endl;
    }
    else {
        cout << "\nKey Exchange Failed!" << endl;
        return 1;
    }

    cin.ignore();

    string message;

    cout << "\nEnter Message: ";
    getline(cin, message);

    string encrypted =
        encryptMessage(message, aliceShared);

    string decrypted =
        decryptMessage(encrypted, aliceShared);

    cout << "\nOriginal Message: "
         << message << endl;

    cout << "Encrypted Message: "
         << encrypted << endl;

    cout << "Decrypted Message: "
         << decrypted << endl;

    if (message == decrypted) {
        cout << "\nEncryption Test Passed!" << endl;
    }
    else {
        cout << "\nEncryption Test Failed!" << endl;
    }

    return 0;
}

