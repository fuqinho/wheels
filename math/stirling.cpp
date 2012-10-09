// スターリング数
// S(n,k): n個の区別あるボールをk個の区別ない箱に空き箱無く入れる時の入れ方の数
//
// 漸化式での求め方
//  S(n,1) = S(n,n) = 1
//  S(n,k) = S(n-1,k-1) + k * S(n-1,k)
//
// 備考
//  k!をかければ、箱に区別がある場合も求まる。
//  包除原理でも求められる。

#include <iostream>
using namespace std;

const int MAX_N = 10;
int S[MAX_N+1][MAX_N+1];

int main() {
  S[1][1] = 1;
  for (int n = 2; n <= MAX_N; n++) {
    S[n][1] = S[n][n] = 1;
    for (int k = 2; k < n; k++) {
      S[n][k] = S[n-1][k-1] + k * S[n-1][k];
    }
  }

  cout << S[4][3] << endl;
}
