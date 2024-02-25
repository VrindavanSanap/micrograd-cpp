#include <iostream>
using namespace std;

float f(float x) { return 3 * x * x - 4 * x + 5; }

int main() {
  float h = 0.0001;
  float x = -2;
  cout << f(x) << endl;
  cout << (f(x + h) - f(x)) / h << endl;
  return 0;
}
