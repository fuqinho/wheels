#include <iostream>
using namespace std;

struct ModVal {
    static const int n = 1000000007;
    int v;
    ModVal() : v(0) {}
    ModVal(int v) : v(v) {}
    ModVal& operator+= (const ModVal& val) { v = (v + val.v) % n; return *this; }
    ModVal& operator-= (const ModVal& val) { v = (v - val.v + n) % n; return *this; }
    ModVal& operator*= (const ModVal& val) { v = ((long long)v * val.v) % n; return *this; }
    ModVal pow(int e) const {
        ModVal res = 1, x = v;
        while (e) {
            if (e & 1) res *= x;
            x *= x; e >>= 1;
        }
        return res;
    }
    ModVal inv() const { return (*this).pow(n-2); }
    ModVal& operator/= (const ModVal& val) {
        ModVal t(v); t *= val.inv(); v = t.v;
        return *this;
    }
    ModVal fact() {
        ModVal res(1);
        for (int i = 1; i <= v; i++) res *= i;
        return res;
    }
};
ModVal operator+(const ModVal& x, const ModVal& y) { return (x.v + y.v) % ModVal::n; }
ModVal operator-(const ModVal& x, const ModVal& y) { return (x.v - y.v + ModVal::n) % ModVal::n; }
ModVal operator*(const ModVal& x, const ModVal& y) { return ((long long)x.v * y.v) % ModVal::n; }
ModVal operator/(const ModVal& x, const ModVal& y) { return x * y.inv(); }
std::ostream& operator<<(std::ostream& ostr, const ModVal& rhs) { return ostr << rhs.v; }

int main() {
    ModVal x = 10;
    ModVal y = 12;
    cout << x-y << endl;
    cout << y.pow(10) << endl;
    x += 100;
    cout << x / y << endl;
}
