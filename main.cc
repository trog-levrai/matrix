#include <iostream>
#include <chrono>
#include <omp.h>

#include "my_vector.hh"
#include "my_matrix.hh"

#define LEN (1 << 14)

using namespace std::chrono;

unsigned long get_time(high_resolution_clock::time_point t)
{
  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>( t2 - t ).count();
  return duration;
}

void perf_tests()
{
  std::cout << "Performance tests" << std::endl;
  auto v1 = std::vector<double>(LEN);
  auto v2 = std::vector<double>(LEN);
  auto mt = std::vector<double>(LEN * LEN);
  MyVector<LEN> foo = MyVector<LEN>(v1);
  MyVector<LEN> bar = MyVector<LEN>(v2);
  MyMatrix<LEN, LEN> mat = MyMatrix<LEN, LEN>(mt);
  std::cout << "Test duration with " << omp_get_max_threads() << " thread(s)"
    << std::endl;
  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  foo + bar;
  std::cout << "Test + on vectors took " << get_time(t1) << " us" << std::endl;
  t1 = high_resolution_clock::now();
  foo * bar;
  std::cout << "Test * on vectors took " << get_time(t1) << " us" << std::endl;
  mat * foo;
  std::cout << "Test * on vector and matrix took " << get_time(t1) << " us" << std::endl;
  omp_set_num_threads(1);
  std::cout << "Test duration with " << omp_get_max_threads() << " thread(s)"
    << std::endl;
  t1 = high_resolution_clock::now();
  foo + bar;
  std::cout << "Test + on vectors took " << get_time(t1) << " us" << std::endl;
  t1 = high_resolution_clock::now();
  foo * bar;
  std::cout << "Test * on vectors took " << get_time(t1) << " us" << std::endl;
  mat * foo;
  std::cout << "Test * on vector and matrix took " << get_time(t1) << " us" << std::endl;
}

void basic_tests() {
  std::cout << "Basic tests" << std::endl;
  std::vector<double> v1 { 0.5, 2, 0 };
  std::vector<double> v2 { 2, 0.5, -1 };
  auto m = std::vector<double>(v1);
  for (size_t i = 0; i < 3; ++i)
    m.push_back(v2[i]);
  for (size_t i = 0; i < 3; ++i)
    m.push_back(v2[i]);
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
