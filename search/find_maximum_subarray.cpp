#include <iostream>
#include <vector>
#include <algorithm>
#include "../common.h"
using namespace std;

const int INF = 100000000;

struct Subarray {
    int low;
    int high;
    int sum;
    Subarray(int l, int h, int s) : low(l), high(h), sum(s) {}
};

// Divide-and-conquer algorithm
Subarray find_max_crossing_subarray(vector<int>& A, int l, int m, int r) {
    int left_sum = -INF;
    int sum = 0;
    int max_left = -1;
    for (int i = m-1; i >= l; i--) {
        sum += A[i];
        if (sum > left_sum) {
            left_sum = sum;
            max_left = i;
        }
    }
    int right_sum = -INF;
    sum = 0;
    int max_right = -1;
    for (int i = m; i < r; i++) {
        sum += A[i];
        if (sum > right_sum) {
            right_sum = sum;
            max_right = i+1;
        }
    }
    return Subarray(max_left, max_right, left_sum + right_sum);
}

Subarray find_maximum_subarray(vector<int>& A, int l, int r) {
    if (r - l == 1) {
        return Subarray(l, r, A[l]); // base case: only one element
    } else {
        int mid = (l + r) / 2;
        Subarray cand_left     = find_maximum_subarray(A, l, mid);
        Subarray cand_right    = find_maximum_subarray(A, mid, r);
        Subarray cand_cross    = find_max_crossing_subarray(A, l, mid, r);
        if (cand_left.sum >= cand_right.sum && cand_left.sum >= cand_cross.sum)
            return cand_left;
        else if (cand_right.sum >= cand_cross.sum)
            return cand_right;
        else
            return cand_cross;
    }
}

// Linear-time algorithm
Subarray find_maximum_subarray2(vector<int>& A) {
    Subarray best(0, 1, A[0]);
    int suffix_array_start, suffix_array_sum;
    if (A[0] > 0) {
        suffix_array_start = 0;
        suffix_array_sum = A[0];
    } else {
        suffix_array_start = 1;
        suffix_array_sum = 0;
    }
    for (int i = 1; i < A.size(); i++) {
        // best v.s. {best_array_which_ends_at_(i-1)} + A[i]
        suffix_array_sum += A[i];
        if (suffix_array_sum > best.sum) {
            best.sum = suffix_array_sum;
            best.low = suffix_array_start;
            best.high = i+1;
        }
        if (suffix_array_sum <= 0) {
            suffix_array_sum = 0;
            suffix_array_start = i+1;
        }
    }
    return best;
}

int main() {
    vector<int> v = random_vector(100);
    for (int i = 0; i < v.size(); i++) v[i] -= 50;
    print_vector(v);
    Subarray sa = find_maximum_subarray(v, 0, 100);
    Subarray sa3 = find_maximum_subarray2(v);
    cerr << "[" << sa.low << "," << sa.high << "): " << sa.sum << endl;
    cerr << "[" << sa3.low << "," << sa3.high << "): " << sa3.sum << endl;

    cerr << "---------------------------" << endl;
    int A2[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    //int A2[] = {-13, -3, -25, -20, -3, -16, -23, -18, -20, -7, -12, -5, -22, -15, -4, -7};
    vector<int> v2(sizeof(A2) / sizeof(A2[0]));
    for (int i = 0; i < v2.size(); i++) v2[i] = A2[i];
    print_vector(v2);
    Subarray sa2 = find_maximum_subarray(v2, 0, v2.size());
    Subarray sa4 = find_maximum_subarray2(v2);
    cerr << "[" << sa2.low << "," << sa2.high << "): " << sa2.sum << endl;
    cerr << "[" << sa4.low << "," << sa4.high << "): " << sa4.sum << endl;
}
