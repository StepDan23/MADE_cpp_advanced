#pragma once
#include <vector>
#include <iostream>
#include <cmath>

namespace task {

const double _EPS_DIV = 1e-7;
const double _EPS_EQU = 1e-2;

std::vector<double> operator+(std::vector<double> vec, std::vector<double> vec_1);
std::vector<double> operator-(std::vector<double> vec, std::vector<double> vec_1);
std::vector<double> operator+(std::vector<double> vec);
std::vector<double> operator-(std::vector<double> vec);
double operator*(std::vector<double> vec, std::vector<double> vec_1);
std::vector<double> operator%(std::vector<double> vec, std::vector<double> vec_1);
bool operator||(std::vector<double> vec, std::vector<double> vec_1);
bool operator&&(std::vector<double> vec, std::vector<double> vec_1);
std::vector<int> operator|(std::vector<int> vec, std::vector<int> vec_1);
std::vector<int> operator&(std::vector<int> vec, std::vector<int> vec_1);

std::ostream &operator<<(std::ostream &out, std::vector<double> &vec);
std::istream &operator>>(std::istream &in, std::vector<double> &vec);
void reverse(std::vector<double> &vec);

std::vector<double> operator+(std::vector<double> vec, std::vector<double> vec_1) {
  std::vector<double> new_vec(vec.size());

  for (size_t i = 0; i < vec.size(); ++i)
    new_vec[i] = vec[i] + vec_1[i];
  return new_vec;
}

std::vector<double> operator-(std::vector<double> vec, std::vector<double> vec_1) {
  std::vector<double> new_vec(vec.size());

  for (size_t i = 0; i < vec.size(); ++i)
    new_vec[i] = vec[i] - vec_1[i];
  return new_vec;
}

std::vector<double> operator+(std::vector<double> vec) {
  std::vector<double> new_vec(vec.size());

  for (size_t i = 0; i < vec.size(); ++i)
    new_vec[i] = vec[i];
  return new_vec;
}

std::vector<double> operator-(std::vector<double> vec) {
  std::vector<double> new_vec(vec.size());

  for (size_t i = 0; i < vec.size(); ++i)
    new_vec[i] = -vec[i];
  return new_vec;
}

double operator*(std::vector<double> vec, std::vector<double> vec_1) {
  double result = 0;

  for (size_t i = 0; i < vec.size(); ++i)
    result += vec[i] * vec_1[i];
  return result;
}

std::vector<double> operator%(std::vector<double> vec, std::vector<double> vec_1) {
  std::vector<double> new_vec(vec.size());

  new_vec[0] = vec[2] * vec_1[1] - vec[1] * vec_1[2];
  new_vec[1] = vec[0] * vec_1[2] - vec[2] * vec_1[0];
  new_vec[2] = vec[1] * vec_1[0] - vec[0] * vec_1[1];

  return new_vec;
}

bool operator||(std::vector<double> vec, std::vector<double> vec_1) {
  double cos_fi = vec * vec_1 / (sqrt((vec * vec) * (vec_1 * vec_1)) + _EPS_DIV);

  if (1.0 - fabs(cos_fi) > _EPS_EQU)
    return false;

  return true;
}

bool operator&&(std::vector<double> vec, std::vector<double> vec_1) {
  double ratio = vec[0] / (vec_1[0] + _EPS_DIV);
  if (ratio < 0)
    return false;

  for (size_t i = 0; i < vec.size(); ++i)
    if (fabs(ratio - vec[i] / (vec_1[i] + _EPS_DIV)) > _EPS_EQU)
      return false;

  return true;
}

std::vector<int> operator|(std::vector<int> vec, std::vector<int> vec_1) {
  std::vector<int> new_vec(vec.size());

  for (size_t i = 0; i < vec.size(); ++i)
    new_vec[i] = vec[i] | vec_1[i];

  return new_vec;
}

std::vector<int> operator&(std::vector<int> vec, std::vector<int> vec_1) {
  std::vector<int> new_vec(vec.size());

  for (size_t i = 0; i < vec.size(); ++i)
    new_vec[i] = vec[i] & vec_1[i];

  return new_vec;
}

std::ostream &operator<<(std::ostream &out, std::vector<double> &vec) {
  for (double val: vec)
    out << val << ' ';
  out << std::endl;

  return out;
}

std::istream &operator>>(std::istream &in, std::vector<double> &vec) {
  int vec_size;

  in >> vec_size;
  vec.resize(vec_size);

  for (size_t i = 0; i < vec_size; ++i)
    in >> vec[i];

  return in;
}

void reverse(std::vector<double> &vec) {
  for (size_t i = 0; i < vec.size() / 2; ++i)
    std::swap(vec[i], vec[vec.size() - 1 - i]);
}

}  //namespace task
