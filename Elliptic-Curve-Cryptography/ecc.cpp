
#include <iostream>
#include <stdexcept>

using namespace std;

class Point {
public:
    long long x;
    long long y;
    bool is_infinity;

    Point()
        : x(0), y(0), is_infinity(true) {}

    Point(long long x, long long y)
        : x(x), y(y), is_infinity(false) {}

    bool operator==(const Point& other) const {

        if (is_infinity && other.is_infinity)
            return true;

        if (is_infinity || other.is_infinity)
            return false;

        return x == other.x &&
               y == other.y;
    }
};

class EllipticCurve {
public:
    long long a;
    long long b;
    long long p;

    EllipticCurve(
        long long a,
        long long b,
        long long p
    )
        : a(a), b(b), p(p) {}

    Point add(
        const Point& P,
        const Point& Q
    ) {

        if (P.is_infinity)
            return Q;

        if (Q.is_infinity)
            return P;

        if (P.x == Q.x &&
            P.y != Q.y)
            return Point();

        long long m;

        if (P == Q) {

            m =
                (3 * P.x * P.x + a)
                * inverse_mod(2 * P.y, p)
                % p;
        }
        else {

            m =
                (Q.y - P.y)
                * inverse_mod(Q.x - P.x, p)
                % p;
        }

        long long x_r =
            (m * m - P.x - Q.x) % p;

        long long y_r =
            (m * (P.x - x_r) - P.y) % p;

        x_r = (x_r + p) % p;
        y_r = (y_r + p) % p;

        return Point(x_r, y_r);
    }

    Point negate(const Point& P) {
        return Point(
            P.x,
            (p - P.y) % p
        );
    }

private:

    long long inverse_mod(
        long long k,
        long long p
    ) {

        if (k == 0)
            throw invalid_argument(
                "Inverse does not exist"
            );

        if (k < 0)
            return p -
                   inverse_mod(-k, p);

        long long s = 0;
        long long old_s = 1;

        long long t = 1;
        long long old_t = 0;

        long long r = p;
        long long old_r = k;

        while (r != 0) {

            long long quotient =
                old_r / r;

            long long temp;

            temp = r;
            r = old_r - quotient * r;
            old_r = temp;

            temp = s;
            s = old_s - quotient * s;
            old_s = temp;

            temp = t;
            t = old_t - quotient * t;
            old_t = temp;
        }

        return (old_s + p) % p;
    }
};

int main() {

    cout << "================================="
         << endl;

    cout << " Elliptic Curve Cryptography "
         << endl;

    cout << "================================="
         << endl;

    long long a, b, p;

    cout << "\nEnter curve parameter a: ";
    cin >> a;

    cout << "Enter curve parameter b: ";
    cin >> b;

    cout << "Enter prime modulus p: ";
    cin >> p;

    EllipticCurve curve(a, b, p);

    long long x1, y1;
    long long x2, y2;

    cout << "\nEnter Point P (x y): ";
    cin >> x1 >> y1;

    cout << "Enter Point Q (x y): ";
    cin >> x2 >> y2;

    Point P(x1, y1);
    Point Q(x2, y2);

    Point result =
        curve.add(P, Q);

    cout << "\nP + Q = ("
         << result.x
         << ", "
         << result.y
         << ")"
         << endl;

    Point negP =
        curve.negate(P);

    cout << "Negation of P = ("
         << negP.x
         << ", "
         << negP.y
         << ")"
         << endl;

    cout << "\nECC Operations Completed Successfully!"
         << endl;

    return 0;
}

