#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> random_vector(int num_elements) {
  std::vector<int> v(num_elements);
  for (int i = 0; i < v.size(); i++) v[i] = i+1;
  random_shuffle(v.begin(), v.end());
  return v;
}

void print_vector(std::vector<int>& v) {
  for (int i = 0; i < v.size(); i++) std::cerr << v[i] << " ";
  std::cerr << std::endl;
}

