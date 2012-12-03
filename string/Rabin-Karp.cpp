#include <iostream>
#include <vector>
#include <string>
using namespace std;

string T = "1023764102834612734172331084712";
string P = "23";

const int MOD = 1000000007;

int mod_normalize(int n) {
    if (n < 0)
        n += ((abs(n)/MOD) + 1) * MOD;
    return  n % MOD;
}

int mod_mul(int n, int m) {
    return ((long long)mod_normalize(n) * mod_normalize(m)) % MOD;
}

int mod_pow(int n, int p) {
    int res = 1;
    int a = n;
    while (p) {
        if (p & 1) res = mod_mul(res, a);
        a = mod_mul(a, a);
        p = p >> 1;
    }
    return res;
}

bool validate(int shift) {
    for (int i = 0; i < P.size(); i++) {
        if (P[i] != T[i+shift]) return false;
    }
    return true;
}

void rabin_karp_matcher(string T, string P, int d) {
    int n = T.size();
    int m = P.size();
    int h = mod_pow(d, m-1);
    int p = 0;
    int t = 0;
    for (int i = 0; i < m; i++) {
        p = (d*p + (P[i]-'0')) % MOD;
        t = (d*t + (T[i]-'0')) % MOD;
    }
    for (int s = 0; s <= n - m; s++) {
        if (p == t) {
            if (validate(s))
                cout << "Pattern occcurs with shift " << s << endl;
        }
        if (s < n - m) {
            t = (mod_mul(d, t - mod_mul(T[s]-'0', h)) + T[s+m]-'0') % MOD;
        }
    }
}

int main() {
    rabin_karp_matcher(T, P, 10);
}
