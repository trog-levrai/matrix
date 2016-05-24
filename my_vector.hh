#pragma once

#include <vector>
#include <iostream>

template <unsigned int DIM>
class MyVector
{
  public:
    MyVector(std::vector<double>& values)
    : values_(std::vector<double>(values))
    { }

    ~MyVector() = default;

    MyVector operator+(MyVector& other);
    double operator*(MyVector& other);
    std::vector<double>& get_values();
    void print() const;

  private:
    MyVector()
    : values_(std::vector<double>(DIM))
    { }

    std::vector<double> values_;
};

#include "my_vector.hxx"
