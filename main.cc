#include <iostream>

#include "my_vector.hh"
#include "my_matrix.hh"

int main() {
  std::vector<double> v1 { 0.5, 2, 0 };
  std::vector<double> v2 { 2, 0.5, -1 };
  auto m = std::vector<std::vector<double>>();
  m.push_back(v1);
  m.push_back(v2);
  m.push_back(v2);
  MyVector<3> foo = MyVector<3>(v1);
  MyVector<3> bar = MyVector<3>(v2);
  (foo + bar).print();
  std::cout << foo * bar << std::endl;
  foo.print();
  bar.print();
  auto matrix = MyMatrix<3, 3>(m);
  matrix.print();
  (matrix * foo).print();
  (matrix * bar).print();
}
