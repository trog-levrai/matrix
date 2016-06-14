#include <iostream>
#include <chrono>
#include <omp.h>

#include "my_vector.hh"
#include "my_matrix.hh"

#define LEN (1 << 14)
#define LEN_CHECK (1 << 10)

using namespace std::chrono;

unsigned long get_time(high_resolution_clock::time_point t)
{
  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>( t2 - t ).count();
  return duration;
}

std::string check(bool a) {
  if (a)
    return "OK";
  return "KO";
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
  //Used to limit overhead of OpenMP on the first results
  foo + bar;
  foo + bar;
  std::cout << "Test duration with " << omp_get_max_threads() << " thread(s)"
    << std::endl;
  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  foo + bar;
  std::cout << "Test + on vectors took " << get_time(t1) << " us" << std::endl;
  t1 = high_resolution_clock::now();
  foo * bar;
  std::cout << "Test * on vectors took " << get_time(t1) << " us" << std::endl;
  t1 = high_resolution_clock::now();
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
  t1 = high_resolution_clock::now();
  mat * foo;
  std::cout << "Test * on vector and matrix took " << get_time(t1) << " us" << std::endl;
}

void result_test()
{
  auto v1 = std::vector<double>(LEN_CHECK);
  auto v2 = std::vector<double>(LEN_CHECK);
  auto mt = std::vector<double>(LEN_CHECK * LEN_CHECK);
  #pragma omp parallel for
  for (size_t i = 0; i < LEN_CHECK; ++i)
  {
    v1[i] = i;
    v2[i] = i % 5;
  }
  #pragma omp parallel for
  for (size_t i = 0; i < LEN_CHECK * LEN_CHECK; ++i)
    mt[i] = i;
  MyVector<LEN_CHECK> foo = MyVector<LEN_CHECK>(v1);
  MyVector<LEN_CHECK> bar = MyVector<LEN_CHECK>(v2);
  MyMatrix<LEN_CHECK, LEN_CHECK> mat = MyMatrix<LEN_CHECK, LEN_CHECK>(mt);
  //Computes with several threads
  auto mul1 = foo * bar;
  auto mul2 = foo * foo;
  auto add1 = foo + bar;
  auto add2 = bar + foo;
  auto matrix1 = mat * foo;
  auto matrix2 = mat * bar;
  omp_set_num_threads(1);
  //Computes the same with one thread
  std::cout << check((mul1 == (foo * bar))) << std::endl;
  std::cout << check((mul2 == (foo * foo))) << std::endl;
  std::cout << check((add1 == (foo + bar))) << std::endl;
  std::cout << check((add1 == (foo + bar))) << std::endl;
  std::cout << check((matrix1 == (mat * foo))) << std::endl;
  std::cout << check((matrix2 == (mat * bar))) << std::endl;
}

void basic_tests()
{
  //omp_set_num_threads(1);
  std::cout << "Basic tests" << std::endl;
  std::vector<double> v1 { 0.5, 2, 0 };
  std::vector<double> v2 { 2, 0.5, -1 };
  auto m = std::vector<double>(v1);
  for (size_t i = 0; i < 3; ++i)
    m.push_back(v2[i]);
  for (size_t i = 0; i < 3; ++i)
    m.push_back(v2[i]);
  auto m2 = std::vector<double>(v2);
  for (size_t i = 0; i < 3; ++i)
    m2.push_back(v1[i]);
  for (size_t i = 0; i < 3; ++i)
    m2.push_back(v2[i]);
  MyVector<3> foo = MyVector<3>(v1);
  MyVector<3> bar = MyVector<3>(v2);
  (foo + bar).print();
  std::cout << foo * bar << std::endl;
  foo.print();
  bar.print();
  auto matrix = MyMatrix<3, 3>(m);
  auto matrix2 = MyMatrix<3, 3>(m2);
  matrix.print();
  matrix2.print();
  auto tmp = matrix * foo;
  tmp.print();
  //(matrix * foo).print();
  auto aux = matrix * bar;
  aux.print();
  //(matrix * bar).print();
  auto mat = matrix * matrix;
  mat.print();
  auto mat2 = matrix * matrix2;
  mat2.print();
}

int main(int argc, char** argv)
{
  if (argc > 1 && std::string(argv[1]) == "-p")
    perf_tests();
  else if (argc > 1 && std::string(argv[1]) == "-r")
    result_test();
  else
    basic_tests();
}
