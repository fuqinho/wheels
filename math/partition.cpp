#include <cstdio>
using namespace std;

const int MAX_N = 20;
int part[MAX_N+1][MAX_N+1];

int main() {
  for (int a = 0; a <= MAX_N; a++) {
    part[0][a] = 1;
  }
  part[0][0] = 1;
  for (int n = 1; n <= MAX_N; n++) {
    part[n][1] = 1;
    for (int a = 1; a <= MAX_N; a++) {
      part[n][a] = part[n][a-1] + (n-a >= 0 ? part[n-a][a] : 0);
    }
  }

  // print result
  for (int n = 1; n <= MAX_N; n++) {
    printf("p(%d) = %d\n", n, part[n][n]);
  }
}

