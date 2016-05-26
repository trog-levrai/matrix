#include <iostream>

#include "my_vector.hh"
#include "my_matrix.hh"

#define LEN 100000000

void perf_tests() {
  std::cout << "Performance tests" << std::endl;
  auto v1 = std::vector<double>();
  auto v2 = std::vector<double>();
  for (size_t i = 0; i < LEN; ++i) {
    v1.push_back(i);
    v2.push_back(i);
  }
  MyVector<LEN> foo = MyVector<LEN>(v1);
  MyVector<LEN> bar = MyVector<LEN>(v2);
  //(foo + bar).print();
  foo + bar;
}

void basic_tests() {
  std::cout << "Basic tests" << std::endl;
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

int main(int argc, char** argv) {
  if (argc > 1 && std::string(argv[1]) == "-p")
    perf_tests();
  else
    basic_tests();
}
