#include <iostream>
#include <type_traits>
#include <typeinfo>

template <typename T>
using MaybeRef = typename std::conditional<std::is_integral<T>::value, const T,
                                           const T &>::type;

template <typename T> void func(MaybeRef<T> i) {
  std::cout << typeid(i).name() << std::endl;
}

template <typename T> class Foo {
public:
  virtual void validate(MaybeRef<T> i) = 0;
  virtual void check(T &i) = 0;
};

class FooChild : public Foo<int> {
public:
  void validate(int i) override {
    std::cout << "type: " << typeid(i).name() << " value: " << i << std::endl;
  }
};

class FooChild2 : public Foo<std::string> {
public:
  void validate(const std::string &i) override {
    std::cout << "type: " << typeid(i).name() << " value: " << i << std::endl;
  }
};

int main() {
  MaybeRef<int> a = 1;

  float f = 3.0f;
  MaybeRef<float> b = f;

  FooChild foo_child;
  foo_child.validate(1);

  FooChild2 foo_child2;
  foo_child2.validate("h");
}