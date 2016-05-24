#include <iostream>

#include "my_vector.hh"

int main() {
  std::vector<double> v1 { 0.5, 2, 0 };
  std::vector<double> v2 { 2, 0.5, -1 };
  MyVector<3> foo = MyVector<3>(v1);
  MyVector<3> bar = MyVector<3>(v2);
  (foo + bar).print();
  std::cout << foo * bar << std::endl;
}
