#include <iostream>
#include <sstream>

std::string GetLabel(int n) {
  std::ostringstream oss;
  if (n % 3 == 0) oss << "Fizz";
  if (n % 5 == 0) oss << "Buzz";
  if (oss.tellp() == 0) oss << n;
  return oss.str();
}

int main() {
  for (int i = 1; i <= 100; i++) {
    std::cout << GetLabel(i) << " ";
  }
  std::cout << std::endl;
}
