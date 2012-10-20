#include "../common.h"
using namespace std;

void max_heapify(vector<int>& A, int heap_size, int i) {
    int l = i * 2 + 1;
    int r = i * 2 + 2;
    int largest = i;
    if (l < heap_size && A[l] > A[largest]) largest = l;
    if (r < heap_size && A[r] > A[largest]) largest = r;
    if (largest != i) {
        swap(A[i], A[largest]);
        max_heapify(A, heap_size, largest);
    }
}

void build_max_heap(vector<int>& A) {
    for (int i = A.size() / 2; i >= 0; i--) {
        max_heapify(A, A.size(), i);
    }
}

void heapsort(vector<int>& A) {
    build_max_heap(A);
    int heap_size = A.size();
    for (int i = A.size() - 1; i > 0; i--) {
        swap(A[0], A[i]);
        heap_size--;
        max_heapify(A, heap_size, 0);
    }
}

int main() {
    vector<int> v = random_vector(100);
    heapsort(v);
    print_vector(v);
}
