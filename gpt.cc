#include <iostream>

// Define a function that takes an integer and returns an integer
int square(int x) { return x * x; }

// Define a function that takes a function pointer as argument
int apply_function(int (*func)(int), int x) {
  // Call the function pointer with the argument x
  return func(x);
}

int main() {
  // Example usage:
  int result = apply_function(square, 5);
  std::cout << result << std::endl;  // Output: 25
  return 0;
}
