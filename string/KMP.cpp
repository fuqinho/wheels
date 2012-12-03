#include <iostream>
#include <string>
#include <vector>
using namespace std;

// the Knuth-Morris-Pratt algorithm
// O(m+n) where m:pattern.size n:text.size

vector<int> compute_prefix_function(string P) {
    int m = P.length();
    // pi[q]: Pのk(<q)文字のprefixが、Pのq文字のprefixのsuffixになるような最大のk
    vector<int> pi(m+1);
    pi[1] = 0;
    // k: number of characters matched
    int k = 0;
    for (int q = 2; q <= m; q++) {
        while (k > 0 && P[k] != P[q-1]) k = pi[k];
        if (P[k] == P[q-1]) k++;
        pi[q] = k;
    }
    return pi;
}

void kmp_mather(string T, string P) {
    int n = T.length();
    int m = P.length();
    vector<int> pi = compute_prefix_function(P);
    // q:number of characters matched
    int q = 0;
    for (int i = 0; i < n; i++) {
        while (q > 0 && P[q] != T[i]) q = pi[q];
        if (P[q] == T[i]) q++;
        if (q == m) {
            cout << "Pattern occurs with shift " << i-m+1 << endl;
            q = pi[q];
        }
    }
}

int main() {
    string T = "acbcabcabcbabacabcabcabacabbabcab";
    string P = "aca";

    vector<int> p = compute_prefix_function(string("ababaca"));
    for (int i=0; i<p.size(); i++) cout << p[i] << " ";
    cout << endl;

    kmp_mather(T, P);
}
