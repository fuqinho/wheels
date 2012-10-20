#include <cstdio>
using namespace std;

const int MAX_N = 20;

// part[m][n]: 
//   m個のボールを1袋あたりn個以下で袋に分ける分け方の数
//   n個入りの袋を作るかどうかで、
//    part[m][n] = part[m][n-1] + part[m-n][n]
//   と問題を砕ける。
int part[MAX_N+1][MAX_N+1];

// p[m][n]: mのn分割
//   m個のボールをn個の区別のない袋に入れる入れ方の数
//   ただしすべての袋に1つ以上入れるとする
//   各袋に1つずつボールを入れたあと、残りのm-n個をn個以下の袋に分ける。
//    p[m][n] = p[m-n][1] + p[m-n][2] + ... + p[m-n][n]
//    但し、m<nなら0, m==nなら1, m>=1に関してn=1なら1
int p[MAX_N+1][MAX_N+1];

int main() {
  // calc part[n][a]
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

  // calc p[m][n]
  for (int m = 0; m <= MAX_N; m++) {
    for (int n = 1; n <= MAX_N; n++) {
      if (n > m) {
        p[m][n] = 0;
      } else if (n == m) {
        p[m][n] = 1;
      } else if (m == 1) {
        p[m][n] = 1;
      } else {
        p[m][n] = 0;
        for (int k = 1; k <= n; k++) {
          p[m][n] += p[m-n][k];
        }
      }
    }
  }


  // print result
  for (int n = 1; n <= MAX_N; n++) {
    // partを使った計算
    printf("part[%d][%d] = %d\n", n, n, part[n][n]);

    // mのn分割を使った計算
    int sum = 0;
    for (int k = 1; k <= n; k++) {
      sum += p[n][k];
    }
    printf("p(%d) = %d\n", n, sum);
  }
  printf("8の3分割: %d\n", p[8][3]);
}

