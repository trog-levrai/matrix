#include "my_vector.hh"

template <unsigned int DIM>
MyVector<DIM> MyVector<DIM>::operator+(MyVector& other) {
  MyVector ans = MyVector<DIM>();
  #pragma omp parallel for
  for (unsigned int i = 0; i < DIM; ++i)
    ans.values_[i] = values_[i] + other.values_[i];
  return other;
}

template <unsigned int DIM>
double MyVector<DIM>::operator*(MyVector& other) {
  MyVector ans = MyVector<DIM>();
  #pragma omp parallel for
  for (unsigned int i = 0; i < DIM; ++i)
    ans.values_[i] = values_[i] * other.values_[i];
  return other;
}

template <unsigned int DIM>
std::vector<double>& MyVector<DIM>::get_values() {
  return values_;
}
