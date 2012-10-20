#include "../common.h"
#include <cassert>
#include <algorithm>
using namespace std;

void max_heapify(vector<int>& A, int i) {
    int l = i * 2 + 1;
    int r = i * 2 + 2;
    int largest = i;
    if (l < A.size() && A[l] > A[largest]) largest = l;
    if (r < A.size() && A[r] > A[largest]) largest = r;
    if (largest != i) {
        swap(A[i], A[largest]);
        max_heapify(A, largest);
    }
}

int heap_maximum(vector<int>& A) {
    return A[0];
}

int heap_extract_max(vector<int>& A) {
    int max = A[0];
    A[0] = A[A.size()-1];
    A.pop_back();
    max_heapify(A, 0);
    return max;
}

void heap_increase_key(vector<int>& A, int i, int key){
    assert(key >= A[i]);

    A[i] = key;
    while (i > 0 && A[(i-1)/2] < A[i]) {
        swap(A[i], A[(i-1)/2]);
        i = (i-1)/2;
    }
}

void max_heap_insert(vector<int>& A, int key) {
    A.push_back(-100000000);
    heap_increase_key(A, A.size()-1, key);
}

int main() {
    vector<int> v;
    max_heap_insert(v, 10);
    max_heap_insert(v, 3);
    max_heap_insert(v, 18);
    max_heap_insert(v, 8);
    max_heap_insert(v, 7);

    for (int i = 0; i < 5; i++) {
        cerr << heap_maximum(v) << endl;
        heap_extract_max(v);
    }
}

