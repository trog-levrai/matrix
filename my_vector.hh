#pragma once

#include <vector>
#include <iostream>
#include <omp.h>

template <unsigned int DIM>
class MyVector
{
  public:
    MyVector(std::vector<double>& values, bool allocated = false)
    : values_(&values)
    , allocated_(allocated)
    { }

    ~MyVector();

    MyVector operator+(MyVector& other);
    double operator*(MyVector& other);
    std::vector<double>& get_values();
    void print() const;

  private:
    MyVector()
    : values_(new std::vector<double>(DIM))
    , allocated_(true)
    { }

    bool allocated_;
    std::vector<double>* values_;
};

#include "my_vector.hxx"
