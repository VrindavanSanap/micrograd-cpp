
#include <functional>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;
class Value {
 public:
  float data;
  float grad;
  vector<Value *> children;
  std::function<void()> _backward;
  vector<Value *> topo;
  bool has__backward = false;
  Value(float data, vector<Value *> children = vector<Value *>()) {
    this->data = data;
    this->grad = 0;
    this->children = children;
    this->has__backward = false;
  };
  // __add__ Value + Value
  Value operator+(Value &other) {
    vector<Value *> out_children;
    out_children.push_back(this);
    out_children.push_back(&other);
    Value out(this->data + other.data, out_children);

    out._backward = [this, other, &out]() mutable {
      this->grad += out.grad;
      other.grad += out.grad;
    };
    out.has__backward = true;

    return out;
    cout << "plus classed" << endl;
  }
  Value operator-(Value &other) {
    vector<Value *> out_children;
    out_children.push_back(this);
    out_children.push_back(&other);
    Value out(this->data - other.data, out_children);

    out._backward = [this, other, &out]() mutable {
      this->grad -= out.grad;
      other.grad -= out.grad;
    };
    out.has__backward = true;

    return out;
    cout << "plus classed" << endl;
  }

  Value operator+(float other) {
    Value v(other);
    return this->operator+(v);
  }
  Value operator-() { return this->operator*(-1); };
  // Value operator+=(float other) {
  //   Value v(other);
  //   this->operator+(v);
  // }

  // Value operator+=(Value &other) {
  //   return this->operator+(other);
  //   }
  // __mul__ Value + Value
  Value operator*(Value &other) {
    vector<Value *> out_children;
    out_children.push_back(this);
    out_children.push_back(&other);
    Value out(this->data * other.data, out_children);

    out._backward = [this, other, &out]() mutable {
      this->grad += other.data * out.grad;
      other.grad += this->data * out.grad;
      // cout << other.data * out.grad << ' ' << this->data * out.grad << endl;
    };
    out.has__backward = true;
    return out;
  }
  Value operator*(float other) {
    Value v(other);
    return this->operator*(v);
  }

  Value operator/(float other) {
    Value v(other);
    Value v_inv = v.power(-1);
    return this->operator*(v_inv);
  }

  Value power(float other) {
    vector<Value *> out_children;
    out_children.push_back(this);

    Value out(std::pow(this->data, other), out_children);

    out._backward = [this, other, &out]() mutable {
      this->grad += other * std::pow(this->data, other - 1);

      // cout << other.data * out.grad << ' ' << this->data * out.grad << endl;
    };
    out.has__backward = true;
    return out;
  }
  Value relu() {
    vector<Value *> out_children;
    out_children.push_back(this);
    float res = 0;
    if (this->data > 0) {
      res = this->data;
    }
    Value out(res, out_children);

    out._backward = [this, &out]() mutable {
      this->grad += out.data * (out.grad > 0);
      // cout << other.data * out.grad << ' ' << this->data * out.grad << endl;
    };
    out.has__backward = true;
    return out;
  }
  // __repr__
  friend std::ostream &operator<<(std::ostream &os, const Value &v) {
    os << "Value(data=" << v.data << ", grad=" << v.grad << ")";

    return os;
  }
  void build_topo(Value &v) {
    set<Value *> visited;
    if (visited.find(&v) == visited.end()) {
      visited.insert(&v);
    }
    for (Value *child : v.children) {
      build_topo(*child);
    }
    topo.push_back(&v);
  }
  void backward() {
    build_topo(*this);
    this->grad = 1;
    for (Value *valPtr : topo) {
      if (valPtr != nullptr) {
        Value val = *valPtr;
        // cout << val.data;
        if (val.has__backward) {
          val._backward();
        }

      } else {
        // Handle the case when valPtr is nullptr
      }
    }
  }
};
Value operator/(float other, Value &v) {
  Value other_value(other);
  Value v_inv = v.power(-1);
  return other_value * v_inv;
}
int main() {
  Value a(-4.0);
  Value b(2.0);
  Value d(3);
  Value c = a + b;
  c = a;
  c.backward();
  // Value a(-4.0);
  // Value b(2.0);
  // Value c = a + b;
  // // a.backward();
  // cout << c << " " << 1 << endl;

  // Value b_p_3 = b.power(3);
  // Value t5 = a * b;
  // Value d = t5+b_p_3;
  
  // cout << d << " " << 2 << endl;

  // c = c + c + 1;
  // cout << c << " " << 3 << endl;

  // c = c + c + 1 - a;
  // cout << c << " " << 4 << endl;
  // c.backward();
  // Value t1 = (b + a).relu();
  // d = d * 2 + t1 + d;

  // cout << d << " " << 5 << endl;
  // Value t2 = (b - a).relu();
  // d = d * 3 + t2 + d;
  // cout << d << " " << 6 << endl;
  // Value e = c - d;

  // cout << e << " " << 7 << endl;
  // Value f = e.power(2);
  // cout << f << " " << 8 << endl;
  // Value g = f / 2.0;
  // cout << g << " " << 9 << endl;
  // Value t3 = 10.0 / f;
  // g = g + t3;
  // cout << g << " " << 10 << endl;
  // f print(f '{g.data:.4f}') #prints 24.7041, the outcome of this forward pass

  // cout << a.grad << endl;
  //     print(f '{a.grad:.4f}') #prints 138.8338, i.e.the numerical value of dg
  //     / da
  // print(f '{b.grad:.4f}') #prints 645.5773, i.e.the numerical value of dg /
  // db
}
