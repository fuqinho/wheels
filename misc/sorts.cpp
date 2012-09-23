#include <iostream>
#include <vector>
using namespace std;

int A[] = {15,9,8,1,4,11,7,12,13,6,5,3,16,2,10,14};
static const int N = sizeof(A) / sizeof(A[0]);

void print(int A[]);
void insertion_sort(int A[]);
void median_sort(int A[], int left, int right);
void insertion_sort(int A[], int left, int right);
void heap_sort(int A[]);
void counting_sort(int A[]);
void bucket_sort(int A[]);

int main() {
  //insertion_sort(A);
  //median_sort(A, 0, N-1);
  //insertion_sort(A, 0, N-1);
  //heap_sort(A);
  //counting_sort(A);
  bucket_sort(A);
  print(A);
}

////// Insertion Sort ////////
void insert(int A[], int pos, int value) {
  int i = pos - 1;
  while (i >= 0 && A[i] > value) {
    A[i+1] = A[i];
    i--;
  }
  A[i+1] = value;
}

void insertion_sort(int A[]) {
  for (int i = 1; i < N; i++) {
    insert(A, i, A[i]);
  }
}


void insertion_sort(vector<int>::iterator begin, vector<int>::iterator end) {
  for (vector<int>::iterator i = begin; i != end; i++) {


    
  }
}

////// Median Sort ////////

int partition(int A[], int left, int right, int pivotIndex)
{
  int pivot = A[pivotIndex];

  // 軸を配列の終端に移す
  swap(A[right], A[pivotIndex]);

  // すべてのpivot以下の値を配列の前方に移し、軸をその直後に置く
  int store = left;
  for (int i = left; i < right; i++) {
    if (A[i] <= pivot) {
      swap(A[i], A[store]);
      store++;
    }
  }

  swap(A[right], A[store]);
  return store;
}

int selectKth(int A[], int k, int left, int right)
{
  // 軸位置を適当に選ぶ(今回は単に左端)
  int idx = left;

  // 軸位置に合った要素が何番目に大きい数字か調べる
  int pivotIndex = partition(A, left, right, idx);
  if (left+k-1 == pivotIndex) return pivotIndex;

  // 軸位置がk番目じゃなければ、再帰的に分割後の区間からk番目要素を探す
  if (left+k-1 < pivotIndex) {
    return selectKth(A, k, left, pivotIndex-1);
  } else {
    return selectKth(A, k - (pivotIndex-left+1), pivotIndex+1, right);
  }
}

void median_sort(int A[], int left, int right) {
  if (left < right) {
    int mid = (right - left + 1) / 2;
    int me = selectKth(A, mid+1, left, right);

    median_sort(A, left, left+mid-1);
    median_sort(A, left+mid+1, right);
  }
}

////// Quick Sort ////////
/// 省略


///// Selection Sort /////
int selectMax(int A[], int left, int right) {
  int maxPos = left;
  for (int i = left + 1; i <= right; i++) {
    if (A[i] > A[maxPos]) maxPos = i;
  }
  return maxPos;
}

void insertion_sort(int A[], int left, int right) {
  for (int i = right - left + 1; i >= 1; i--) {
    int maxPos = selectMax(A, 0, i);
    if (maxPos != i) {
      swap(A[maxPos], A[i]);
    }
  }
}

///// Heap Sort /////
void heapify(int A[], int idx, int max) {
  int largest = idx;

  int left = idx * 2 + 1;
  if (left < max && A[left] > A[largest]) {
    largest = left;
  } 

  int right = idx * 2 + 2;
  if (right < max && A[right] > A[largest]) {
    largest = right;
  }

  if (largest != idx) {
    swap(A[idx], A[largest]);
    heapify(A, largest, max);
  }
}

void build_heap(int A[]) {
  for (int i = N/2 - 1; i >= 0; i--) {
    heapify(A, i, N);
  }
}

void heap_sort(int A[]) {
  build_heap(A);
  for (int i = N-1; i >= 1; i--) {
    swap(A[0], A[i]);
    heapify(A, 0, i);
  }
}

///// Counting Sort /////

void counting_sort(int A[]) {
  vector<int> B(20, 0);
  for (int i = 0; i < N; i++) {
    B[A[i]] ++;
  }

  int idx = 0;
  for (int i = 0; i < B.size(); i++) {
    while (B[i] > 0) {
      A[idx++] = i;
      B[i]--;
    }
  }
}

///// Bucket Sort /////
int hash(int n) {
  return n / 3;
}

void bucket_sort(int A[]) {
  vector<vector<int> > B(7);
  for (int i = 0; i < N; i++) {
    int k = hash(A[i]);
    B[k].push_back(A[i]);
  }

  int idx = 0;
  for (int i = 0; i < B.size(); i++) {
    insertion_sort(B[i].begin(), B[i].end());
    for (int j = 0; j < B[i].size(); j++) {
      A[idx++] = B[i][j];
    }
  }
}

////// Utility Functions ///////
void print(int A[]) {
  cout << "A = [";
  for (int i = 0; i < N; i++) {
    cout << A[i];
    if (i != N-1) cout << ", ";
  }
  cout << "]" << endl;
}

