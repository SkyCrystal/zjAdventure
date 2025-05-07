#include <iostream>

__declspec(dllexport) void test() {
  std::cout << "Test function called!" << std::endl;
}