#include "../common.h"
using namespace std;

const int K = 4;

void insertion_sort(vector<int>& A, int l, int r) {
  for (int j = l+1; j < r; j++) {
    int key = A[j];
    int i = j-1;
    while (i >= l && A[i] > key) {
      A[i+1] = A[i];
      i = i-1;
    }
    A[i+1] = key;
  }
}

// merge [l, m) and [m, r) of array A.
void merge(vector<int>& A, int l, int m, int r) {
  int n1 = m - l;
  int n2 = r - m;
  vector<int> L(n1+1), R(n2+1);
  for (int i = 0; i < n1; i++) L[i] = A[l + i];
  for (int j = 0; j < n2; j++) R[j] = A[m + j];
  L[n1] = numeric_limits<int>::max();
  R[n2] = numeric_limits<int>::max();
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

void merge_insertion_sort(vector<int>& A, int l, int r) {
  if (r - l <= K) {
    insertion_sort(A, l, r);
  }
  else if (r - l >= 2) {
    int m = (l + r) / 2;
    merge_insertion_sort(A, l, m);
    merge_insertion_sort(A, m, r);
    merge(A, l, m, r);
  }
}

int main() {
  vector<int> v = random_vector(100);
  merge_insertion_sort(v, 0, 100);
  print_vector(v);
}
