#include <iostream>
using namespace std;

float f(float x) { return 3 * x * x - 4 * x + 5; }

int main() {
  float h = 0.0001;

  float a = 2.0;
  float b = -3.0;
  float c = 10.0;

  float d1 = a * b + c;
  c += h;
  float d2 = a * b + c;
  cout << "d1: " << d1 << endl;
  cout << "d2: " << d2 << endl;
  cout << "slope: " << (d2 - d1)/h << endl;

  return 0;
}
