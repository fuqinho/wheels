#include <iostream>
using namespace std;

const int MAX_N = 10;
int comb[MAX_N+1][MAX_N+1];

int main() {

  for (int n = 0; n <= MAX_N; n++) {
    comb[n][0] = 1;
    for (int r = 1; r <= n; r++) {
      comb[n][r] = comb[n-1][r] + comb[n-1][r-1];
    }
  }

  // print result
  for (int n = 0; n <= MAX_N; n++) {
    for (int r = 0; r <= n; r++) cerr << comb[n][r] << "\t";
    cerr << endl;
  }
}
