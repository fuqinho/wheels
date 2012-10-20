#include "../common.h"
using namespace std;

void counting_sort(const vector<int>& A, vector<int>& B, int max_val) {
    vector<int> C(max_val + 1);
    for (int i = 0; i < A.size(); i++)
        C[A[i]]++;
    for (int i = 1; i <= max_val; i++)
        C[i] = C[i] + C[i-1];
    // move items from tail to make this sort stable
    for (int i = A.size()-1; i >= 0; i--) {
        B[C[A[i]]-1] = A[i];
        C[A[i]]--;
    }
}

int main() {
    vector<int> vin = random_vector(100);
    vector<int> vout = vector<int>(vin.size());
    counting_sort(vin, vout, 100);
    print_vector(vout);
}
