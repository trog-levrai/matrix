#include <iostream>
#include <chrono>

#include "my_vector.hh"
#include "my_matrix.hh"

#define LEN (1 << 26)

using namespace std::chrono;

void perf_tests() {
  std::cout << "Performance tests" << std::endl;
  auto v1 = std::vector<double>(LEN);
  auto v2 = std::vector<double>(LEN);
  MyVector<LEN> foo = MyVector<LEN>(v1);
  MyVector<LEN> bar = MyVector<LEN>(v2);
  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  foo + bar;
  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>( t2 - t1 ).count();
  std::cout << "Test duration: " << duration << " microseconds" << std::endl;
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
