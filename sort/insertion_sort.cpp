#include "../common.h"
using namespace std;

void insertion_sort(vector<int>& A) {
    for (int j = 1; j < A.size(); j++) {
        int key = A[j];
        int i = j-1;
        while (i >= 0 && A[i] > key) {
            A[i+1] = A[i];
            i = i-1;
        }
        A[i+1] = key;
    }
}

int main() {
    vector<int> v = random_vector(100);
    insertion_sort(v);
    print_vector(v);
}
