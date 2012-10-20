#include "../common.h"
using namespace std;

void selection_sort(vector<int>& A) {
  for (int i = 0; i < A.size() - 1; i++) {
    int min_val = A[i];
    int min_idx = i;
    for (int j = i  + 1; j < A.size(); j++) {
      if (A[j] < min_val) {
        min_val = A[j];
        min_idx = j;
      }
    }
    if (min_idx != i) {
      swap(A[i], A[min_idx]);
    }
  }
}

int main() {
  vector<int> v = random_vector(100);
  selection_sort(v);
  print_vector(v);
}
