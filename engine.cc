#include <iostream>
#include <set>

using namespace std;
class Value {
 public:
  float data;
  float grad;
  vector<Value *> children;
  std::function<void()> _backward;

  Value(float data, vector<Value *> children = vector<Value *>()) {
    this->data = data;
    this->grad = 0;
    this->children = children;
  };
  // __add__ Value + Value
  Value operator+(Value &other) {
    vector<Value *> out_children;
    out_children.push_back(this);
    out_children.push_back(&other);
    return Value(this->data + other.data, out_children);
  }
  // __mul__ Value + Value
  Value operator*(Value &other) {
    vector<Value *> out_children;
    out_children.push_back(this);
    out_children.push_back(&other);
    Value out(this->data + other.data, out_children);

    out._backward = [this, other, out]() mutable {
      this->grad += out.grad;
      other.grad += out.grad;
    };

    return out;
  }
  // __repr__
  friend std::ostream &operator<<(std::ostream &os, const Value &v) {
    os << "Value(data=" << v.data << ")";
    return os;
  }
  void backward() {
    vector<Value *> topo;
    set<Value *> visited;
    }
};

int main() {
  Value a(2.0);
  Value b(3.0);
  Value c = a + b;
  a.data = 10;
  ;
  a.backward();
  cout << (c.children[0]);
}
