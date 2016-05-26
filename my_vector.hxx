#include "my_vector.hh"

template <unsigned int DIM>
MyVector<DIM> MyVector<DIM>::operator+(MyVector& other) {
  MyVector ans = MyVector<DIM>();
  double* aux = ans.values_.data();
  double* v1 = values_.data();
  double* v2 = other.values_.data();
  #pragma omp parallel for
  for (unsigned int i = 0; i < DIM; ++i)
  {
//   std::cout << omp_get_thread_num() << std::endl;
    aux[i] = v1[i] + v2[i];
  }
  return ans;
}

template <unsigned int DIM>
double MyVector<DIM>::operator*(MyVector& other) {
  double ans = 0;
  #pragma omp parallel for reduction(+:ans)
  for (unsigned int i = 0; i < DIM; ++i)
  {
    ans += values_[i] * other.values_[i];
  }
  return ans;
}

template <unsigned int DIM>
std::vector<double>& MyVector<DIM>::get_values() {
  return values_;
}

template <unsigned int DIM>
void MyVector<DIM>::print() const {
  std::cout << "{ ";
  for (size_t i = 0; i < DIM; ++i)
    std::cout << values_[i] << " ";
  std::cout << "}" << std::endl;
}
