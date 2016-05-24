#include <iostream>

#include "my_vector.hh"

int main() {
  std::vector<double> v1 {2.5, 3.3, 43 };
  std::vector<double> v2 {-1.5, -2.3, -42 };
  MyVector<3> foo = MyVector<3>(v1);
  MyVector<3> bar = MyVector<3>(v2);
  MyVector<3> baz = foo + bar;
  std::cout << "{ ";
  for (auto i : baz.get_values())
    std::cout << baz.get_values()[i] << " ";
  std::cout << " }" << std::endl;
}
