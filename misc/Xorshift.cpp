#include <iostream>
#include <vector>
using namespace std;

unsigned int xor128() {
    static unsigned int x = 123456789;
    static unsigned int y = 362436069;
    static unsigned int z = 521288629;
    static unsigned int w = 88675123;
    
    unsigned int t = x ^ (x << 11);
    x = y; y = z; z = w;
    return w = (w ^ (x >> 19)) ^ (t ^ (t >> 8));
}

int main() {
    vector<int> num(6);
    for (int i = 0; i < 1000000; i++) {
        num[xor128()%6]++;
    }
    for (int i = 0; i < 6; i++) cout << num[i] << endl;
}
