#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

bool is_suffix(string a, string b) {
    if (a.size() > b.size()) return false;
    for (int i = 0; i < a.size(); i++) {
        if (a[a.size()-1-i] != b[b.size()-1-i]) return false;
    }
    return true;
}

vector<map<char,int> > compute_transition_function(string P, vector<char> S) {
    int m = P.size();
    vector<map<char, int> > res(m+1);
    for (int q = 0; q <= m; q++) {
        for (int i = 0; i < S.size(); i++) {
            char a = S[i];
            int k = min(m + 1, q + 2);
            do {
                k--;
            } while (!is_suffix(P.substr(0, k), P.substr(0, q) + a));
            res[q][a] = k;
        }
    }
    return res;
}

void finite_automaton_matcher(string T, vector<map<char, int> > transition, int m) {
    int q = 0;
    for (int i = 0; i < T.size(); i++) {
        q = transition[q][T[i]];
        if (q == m)
            cout << "Pattern occurs with shift " << i-m+1 << endl;
    }
}

int main() {
    char CHARS[] = {'a', 'b', 'c'};
    vector<char> S(CHARS, CHARS + (sizeof(CHARS) / sizeof(CHARS[0])));
    string P = "ababaca";
    string T = "abababacaba";

    vector<map<char,int> > transition = compute_transition_function(P, S);
    finite_automaton_matcher(T, transition, P.size());
}

