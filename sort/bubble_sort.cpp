#include "../common.h"
using namespace std;

void bubble_sort(vector<int>& A) {
  for (int i = 0; i < A.size() - 1; i++) {
    for (int j = A.size() - 1; j > i; j--) {
      if (A[j] < A[j-1]) swap(A[j], A[j-1]);
    }
  }
}

int main() {
  vector<int> v = random_vector(100);
  bubble_sort(v);
  print_vector(v);
}
