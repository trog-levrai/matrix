#include "my_vector.hh"

template <unsigned int DIM>
MyVector<DIM>::~MyVector()
{
  if (allocated_)
    delete values_;
}

template <unsigned int DIM>
MyVector<DIM> MyVector<DIM>::operator+(MyVector& other)
{
  MyVector ans = MyVector<DIM>();
  #pragma omp parallel for simd
  for (unsigned int i = 0; i < DIM; ++i)
  {
    (*ans.values_)[i] = (*values_)[i] + (*other.values_)[i];
  }
  return ans;
}

template <unsigned int DIM>
double MyVector<DIM>::operator*(MyVector& other)
{
  double ans = 0;
  #pragma omp parallel for simd reduction(+:ans)
  for (unsigned int i = 0; i < DIM; ++i)
  {
    ans += (*values_)[i] * (*other.values_)[i];
  }
  return ans;
}

template <unsigned int DIM>
bool MyVector<DIM>::operator==(const MyVector& other) const
{
  for (unsigned int i = 0; i < DIM; ++i)
  {
    if ((*values_)[i] != (*other.values_)[i]) {
      return false;
    }
  }
  return true;
}

template <unsigned int DIM>
std::vector<double>& MyVector<DIM>::get_values()
{
  return *values_;
}

template <unsigned int DIM>
void MyVector<DIM>::print() const
{
  std::cout << "{ ";
  for (size_t i = 0; i < DIM; ++i)
    std::cout << values_->at(i) << " ";
  std::cout << "}" << std::endl;
}
