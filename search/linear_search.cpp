#include "../common.h"
using namespace std;

int linear_search(vector<int>& A, int v) {
  for (int i = 0; i < A.size(); i++) {
    if (A[i] == v) return i;
  }
  return A.size();
}

int main() {
  vector<int> v = random_vector(100);
  int idx = linear_search(v, 50);
  cout << v[idx] << endl;
}
