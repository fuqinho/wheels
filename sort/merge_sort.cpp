#include "../common.h"
#include <limits>
using namespace std;

static const int INF = numeric_limits<int>::max();

// merge [l, m) and [m, r) of array A.
void merge(vector<int>& A, int l, int m, int r) {
  int n1 = m - l;
  int n2 = r - m;
  vector<int> L(n1+1), R(n2+1);
  for (int i = 0; i < n1; i++) L[i] = A[l + i];
  for (int j = 0; j < n2; j++) R[j] = A[m + j];
  L[n1] = INF;
  R[n2] = INF;
  int i = 0;
  int j = 0;
  for (int k = l; k < r; k++) {
    if (L[i] <= R[j]) {
      A[k] = L[i];
      i++;
    } else {
      A[k] = R[j];
      j++;
    }
  }
}

void merge_sort(vector<int>& A, int l, int r) {
  if (r - l >= 2) {
    int m = (l + r) / 2;
    merge_sort(A, l, m);
    merge_sort(A, m, r);
    merge(A, l, m, r);
  }
}

int main() {
    vector<int> v = random_vector(100);
    merge_sort(v, 0, 100);
    print_vector(v);
}
