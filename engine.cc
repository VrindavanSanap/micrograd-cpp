#include <iostream>

using namespace std;
class Value {
 public:
  float data;
  float grad;
  vector<Value*> children;
  Value(float data, vector<Value*> children = vector<Value*>()) {
    this->data = data;
    this->children = children;
  };
  // __add__ Value + Value
  Value operator+( Value &other) {
    vector<Value*> out_children;
    out_children.push_back(this);
    out_children.push_back(&other);
    return Value(this->data + other.data, out_children);
  }
  // __mul__ Value + Value
  Value operator*(Value &other) {
    vector<Value *> out_children;
    out_children.push_back(this);
    out_children.push_back(&other);
    return Value(this->data + other.data, out_children);
  }
  // __repr__
  friend std::ostream &operator<<(std::ostream &os, const Value &v) {
    os << "Value(data=" << v.data << ")";
    return os;
  }
};

int main() {
  Value a(2.0);
  Value b(3.0);
  Value c = a + b;
  a.data = 10;
  cout <<* (c.children[0]);
}
