
#include <iostream>
#include <cmath>

using namespace std;

// Compute GCD
unsigned long long gcd(
    unsigned long long a,
    unsigned long long b
) {
    while (b != 0) {
        unsigned long long temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}

// Modular exponentiation
unsigned long long modExp(
    unsigned long long base,
    unsigned long long exp,
    unsigned long long mod
) {
    unsigned long long result = 1;

    base %= mod;

    while (exp > 0) {

        if (exp % 2 == 1)
            result = (result * base) % mod;

        exp >>= 1;
        base = (base * base) % mod;
    }

    return result;
}

// Modular inverse
unsigned long long modInverse(
    unsigned long long e,
    unsigned long long phi
) {
    long long t = 0;
    long long newT = 1;

    long long r = phi;
    long long newR = e;

    while (newR != 0) {

        long long quotient = r / newR;

        long long tempT = t;
        t = newT;
        newT = tempT - quotient * newT;

        long long tempR = r;
        r = newR;
        newR = tempR - quotient * newR;
    }

    if (r > 1)
        return -1;

    if (t < 0)
        t += phi;

    return t;
}

// Prime check
bool isPrime(unsigned long long num) {

    if (num <= 1)
        return false;

    for (unsigned long long i = 2;
         i <= sqrt(num);
         i++) {

        if (num % i == 0)
            return false;
    }

    return true;
}

// RSA key generation
void generateRSAKeys(
    unsigned long long& n,
    unsigned long long& e,
    unsigned long long& d,
    unsigned long long p,
    unsigned long long q
) {

    n = p * q;

    unsigned long long phi =
        (p - 1) * (q - 1);

    for (e = 2; e < phi; e++) {
        if (gcd(e, phi) == 1)
            break;
    }

    d = modInverse(e, phi);
}

// Sign message
unsigned long long signMessage(
    unsigned long long message,
    unsigned long long d,
    unsigned long long n
) {
    return modExp(message, d, n);
}

// Verify signature
bool verifySignature(
    unsigned long long message,
    unsigned long long signature,
    unsigned long long e,
    unsigned long long n
) {
    unsigned long long verification =
        modExp(signature, e, n);

    return verification == message;
}

int main() {

    unsigned long long p, q;

    cout << "==========================" << endl;
    cout << " Digital Signature Demo " << endl;
    cout << "==========================" << endl;

    cout << "\nEnter Prime Number p: ";
    cin >> p;

    cout << "Enter Prime Number q: ";
    cin >> q;

    if (!isPrime(p) || !isPrime(q)) {
        cout << "Both values must be prime."
             << endl;
        return 1;
    }

    unsigned long long n, e, d;

    generateRSAKeys(
        n,
        e,
        d,
        p,
        q
    );

    cout << "\nPublic Key (e,n): ("
         << e << ", "
         << n << ")" << endl;

    cout << "Private Key (d,n): ("
         << d << ", "
         << n << ")" << endl;

    unsigned long long message;

    cout << "\nEnter numeric message: ";
    cin >> message;

    if (message >= n) {
        cout << "Message must be smaller than n."
             << endl;
        return 1;
    }

    unsigned long long signature =
        signMessage(
            message,
            d,
            n
        );

    cout << "\nGenerated Signature: "
         << signature << endl;

    bool verified =
        verifySignature(
            message,
            signature,
            e,
            n
        );

    if (verified) {
        cout << "\nSignature Verified Successfully!"
             << endl;
        cout << "Authentication Passed!"
             << endl;
    }
    else {
        cout << "\nSignature Verification Failed!"
             << endl;
    }

    return 0;
}

