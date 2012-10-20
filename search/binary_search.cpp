#include "../common.h"
using namespace std;

int binary_search(vector<int>& A, int v) {
    sort(A.begin(), A.end());

    int lb = -1, ub = A.size()-1;
    while (ub - lb >= 2) {
        int mid = (lb + ub) / 2;
        if (A[mid] >= v) {
            ub = mid;
        } else {
            lb = mid;
        }
    }
    return ub;
}

int main() {
    vector<int> v = random_vector(100);
    int idx = binary_search(v, 50);
    cout << v[idx] << endl;
}
