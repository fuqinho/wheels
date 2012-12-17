#include <iostream>
using namespace std;

struct mint {
    static const int n = 1000000007;
    int v;
    mint() : v(0) {}
    mint(int v) : v(v) {}
    mint& operator+= (const mint& o) {v = (v+o.v)%n; return *this;}
    mint& operator-= (const mint& o) {v = (v-o.v+n)%n; return *this;}
    mint& operator*= (const mint& o) {v = ((long long)v*o.v)%n; return *this;}
    mint& operator/= (const mint& o) {v = (o.inv()*=v).v; return *this;}
    mint inv() const {return (*this).pow(n-2);}
    mint pow(int e) const {
        mint res=1, x=v;
        while (e) {if (e&1) res*=x; x*=x; e>>=1;}
        return res;
    }
};
mint operator+(const mint& x, const mint& y) {return (x.v+y.v)%mint::n;}
mint operator-(const mint& x, const mint& y) {return (x.v-y.v+mint::n)%mint::n;}
mint operator*(const mint& x, const mint& y) {return ((long long)x.v*y.v)%mint::n;}
mint operator/(const mint& x, const mint& y) {return x*y.inv();}
std::ostream& operator<<(std::ostream& os, const mint& x) {return os<<x.v;}

int main() {
    mint x = 10;
    mint y = 12;
    cout << x-y << endl;
    cout << y.pow(10) << endl;
    x += 100;
    cout << x / y << endl;
    x /= y;
    cout << x << endl;
}
