#include "../common.h"
using namespace std;

int partition(vector<int>& A, int p, int r) {
    int x = A[r-1];
    int i = p - 1;
    for (int j = p; j < r-1; j++) {
        if (A[j] <= x) {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i+1], A[r-1]);
    return i+1;
}

void quicksort(vector<int>& A, int p, int r) {
    if (r - p >= 2) {
        int q = partition(A, p, r);
        quicksort(A, p, q);
        quicksort(A, q+1, r);
    }
}

int main() {
    vector<int> v = random_vector(100);
    quicksort(v, 0, 100);
    print_vector(v);
}
