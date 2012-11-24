#include <cstdio>
using namespace std;

// Source: Introduction to Algorithms [p.935-]

// calculate GCD
int euclid(int a, int b) {
    return b == 0 ? a : euclid(b, a % b);
}

struct EuclidData {
    int d, x, y;
    EuclidData(int d, int x, int y) : d(d), x(x), y(y) {}
};

// calculate GCD and find (x,y) such that ax + by = GCD(a,b)
EuclidData extended_euclid(int a, int b) {
    if (b == 0) {
        return EuclidData(a, 1, 0);
    } else {
        EuclidData data = extended_euclid(b, a % b);
        return EuclidData(data.d, data.y, data.x - (a/b)*data.y);
    }
}

int main() {
    int a = 18, b = 12;
    int c = euclid(a, b);
    printf("%d\n", c);

    EuclidData data = extended_euclid(a, b);
    printf("GCD(%d, %d): %d = a(%d) * %d + b(%d) * %d\n",
                 a,  b, data.d,  a, data.x,   b, data.y);
}
