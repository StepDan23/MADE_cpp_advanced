#include <cmath>
#include "matrix.h"

using namespace task;

double **Matrix::init_zero_matrix(size_t rows, size_t cols) {
  double **matrix;

  if (rows == 0 or cols == 0)
    throw OutOfBoundsException();
  else {
    matrix = new double *[rows];

    for (size_t i = 0; i < rows; ++i) {
      matrix[i] = new double[cols];
      for (size_t j = 0; j < cols; ++j)
        matrix[i][j] = 0.;
    }
    return matrix;
  }
}

void Matrix::matrix_copy(double **from, double **to, size_t rows, size_t cols) {
  for (size_t i = 0; i < rows; ++i)
    for (size_t j = 0; j < cols; ++j)
      to[i][j] = from[i][j];
}

void Matrix::free_matrix(double **ptr, size_t size) {
  for (size_t i = 0; i < size; ++i)
    delete[] ptr[i];
  delete[] ptr;
}

Matrix::Matrix() : n_rows(1), n_cols(1), mat_values(init_zero_matrix(1, 1)) { this->mat_values[0][0] = 1.0; }

Matrix::Matrix(size_t rows, size_t cols) : n_rows(rows), n_cols(cols), mat_values(init_zero_matrix(rows, cols)) {
  for (size_t i = 0; i < std::min(this->n_rows, this->n_cols); ++i)
    this->mat_values[i][i] = 1.0;
}

Matrix::Matrix(const Matrix &copy) {
  this->n_rows = copy.n_rows;
  this->n_cols = copy.n_cols;
  this->mat_values = init_zero_matrix(this->n_rows, this->n_cols);
  matrix_copy(copy.mat_values, this->mat_values, this->n_rows, this->n_cols);
}

Matrix::~Matrix() { free_matrix(this->mat_values, this->n_rows); }

Matrix &Matrix::operator=(const Matrix &a) {
  if (this != &a) {
    free_matrix(this->mat_values, this->n_rows);
    this->n_rows = a.n_rows;
    this->n_cols = a.n_cols;
    this->mat_values = init_zero_matrix(a.n_rows, a.n_cols);
    matrix_copy(a.mat_values, this->mat_values, this->n_rows, this->n_cols);
  }
  return *this;
}

double &Matrix::get(size_t row, size_t col) {
  if (row >= this->n_rows or col >= this->n_cols)
    throw OutOfBoundsException();
  else
    return this->mat_values[row][col];
}

const double &Matrix::get(size_t row, size_t col) const {
  if (row >= this->n_rows or col >= this->n_cols)
    throw OutOfBoundsException();
  else
    return this->mat_values[row][col];
}

void Matrix::set(size_t row, size_t col, const double &value) {
  if (row >= this->n_rows or col >= this->n_cols)
    throw OutOfBoundsException();
  else
    this->mat_values[row][col] = value;
}

void Matrix::resize(size_t new_rows, size_t new_cols) {
  double **new_values = init_zero_matrix(new_rows, new_cols);
  size_t rows = std::min(new_rows, this->n_rows);
  size_t cols = std::min(new_cols, this->n_cols);

  matrix_copy(this->mat_values, new_values, rows, cols);
  free_matrix(this->mat_values, this->n_rows);

  this->n_rows = new_rows;
  this->n_cols = new_cols;
  this->mat_values = new_values;
}

double *Matrix::operator[](size_t row) { return this->mat_values[row]; }

double *Matrix::operator[](size_t row) const { return this->mat_values[row]; }

Matrix &Matrix::operator+=(const Matrix &a) {
  if (a.n_rows != this->n_rows or a.n_cols != this->n_cols)
    throw SizeMismatchException();
  else {
    for (size_t i = 0; i < this->n_rows; ++i)
      for (size_t j = 0; j < this->n_cols; ++j)
        this->mat_values[i][j] += a.mat_values[i][j];
    return *this;
  }
}

Matrix &Matrix::operator-=(const Matrix &a) {
  if (a.n_rows != this->n_rows or a.n_cols != this->n_cols)
    throw SizeMismatchException();
  else {
    for (size_t i = 0; i < this->n_rows; ++i)
      for (size_t j = 0; j < this->n_cols; ++j)
        this->mat_values[i][j] -= a.mat_values[i][j];
    return *this;
  }
}

Matrix &Matrix::operator*=(const Matrix &a) {
  if (this->n_cols != a.n_rows)
    throw SizeMismatchException();
  else {
    double **res_values = init_zero_matrix(this->n_rows, a.n_cols);

    for (size_t i = 0; i < this->n_rows; ++i)
      for (size_t j = 0; j < a.n_cols; ++j)
        for (size_t k = 0; k < a.n_rows; ++k)
          res_values[i][j] += this->mat_values[i][k] * a.mat_values[k][j];

    free_matrix(this->mat_values, this->n_rows);
    this->n_cols = a.n_cols;
    this->mat_values = res_values;

    return *this;
  }
}

Matrix &Matrix::operator*=(const double &number) {
  for (size_t i = 0; i < this->n_rows; ++i)
    for (size_t j = 0; j < this->n_cols; ++j)
      this->mat_values[i][j] *= number;
  return *this;
}

Matrix Matrix::operator+(const Matrix &a) const {
  Matrix new_mat(*this);
  new_mat += a;

  return new_mat;
}

Matrix Matrix::operator-(const Matrix &a) const {
  Matrix new_mat(*this);
  new_mat -= a;

  return new_mat;
}

Matrix Matrix::operator*(const Matrix &a) const {
  Matrix new_mat(*this);
  new_mat *= a;

  return new_mat;
}

Matrix Matrix::operator*(const double &a) const {
  Matrix new_mat(*this);
  new_mat *= a;

  return new_mat;
}

Matrix Matrix::operator-() const {
  Matrix new_mat(*this);

  new_mat *= -1.;
  return new_mat;
}

Matrix Matrix::operator+() const {
  Matrix new_mat(*this);

  return new_mat;
}

double Matrix::det() const {
  if (this->n_rows != this->n_cols)
    throw SizeMismatchException();
  else {
    if (this->n_rows == 1)
      return this->mat_values[0][0];
    else if (this->n_rows == 2)
      return this->mat_values[0][0] * this->mat_values[1][1] - this->mat_values[0][1] * this->mat_values[1][0];
    else {
      double result = 0.0;

      for (size_t k = 0; k < this->n_rows; ++k) {
        Matrix small_matrix(this->n_rows - 1, this->n_rows - 1);
        for (size_t i = 1; i < this->n_rows; ++i) {
          for (size_t j = 0; j < this->n_rows; ++j) {
            if (j == k)
              continue;
            else if (j < k)
              small_matrix[i - 1][j] = this->mat_values[i][j];
            else
              small_matrix[i - 1][j - 1] = this->mat_values[i][j];
          }
        }
        result += ((k % 2 == 0) ? 1 : -1) * this->mat_values[0][k] * small_matrix.det();
      }
      return result;
    }
  }
}

void Matrix::transpose() {
  double **new_values = init_zero_matrix(this->n_cols, this->n_rows);

  for (size_t i = 0; i < this->n_rows; ++i)
    for (size_t j = 0; j < this->n_cols; ++j)
      new_values[j][i] = this->mat_values[i][j];
  free_matrix(this->mat_values, this->n_rows);
  std::swap(this->n_rows, this->n_cols);
  this->mat_values = new_values;
}

Matrix Matrix::transposed() const {
  Matrix new_mat(*this);
  new_mat.transpose();

  return new_mat;
}

double Matrix::trace() const {
  if (this->n_rows != this->n_cols)
    throw SizeMismatchException();
  else {
    double trace = 0.0;

    for (size_t i = 0; i < this->n_rows; ++i)
      trace += this->mat_values[i][i];

    return trace;
  }
}

std::vector<double> Matrix::getRow(size_t row) {
  if (row >= this->n_rows)
    throw OutOfBoundsException();
  else {
    std::vector<double> row_vec(this->n_cols);

    for (size_t i = 0; i < this->n_cols; ++i)
      row_vec[i] = this->mat_values[row][i];

    return row_vec;
  }
}

std::vector<double> Matrix::getColumn(size_t column) {
  if (column >= this->n_cols)
    throw OutOfBoundsException();
  else {
    std::vector<double> col_vec(this->n_rows);

    for (size_t j = 0; j < this->n_rows; ++j)
      col_vec[j] = this->mat_values[column][j];

    return col_vec;
  }
}

bool Matrix::operator==(const Matrix &a) const {
  if (this->n_cols != a.n_cols or this->n_rows != a.n_rows)
    return false;
  for (size_t i = 0; i < this->n_rows; ++i)
    for (size_t j = 0; j < this->n_cols; ++j)
      if (fabs(this->mat_values[i][j] - a.mat_values[i][j]) > EPS)
        return false;
  return true;
}

bool Matrix::operator!=(const Matrix &a) const { return !(*this == a); }

size_t Matrix::getNumRows() const { return this->n_rows; }

size_t Matrix::getNumCols() const { return this->n_cols; }

Matrix task::operator*(const double &a, const Matrix &b) {
  Matrix new_mat(b);
  new_mat *= a;

  return new_mat;
}

std::ostream &task::operator<<(std::ostream &output, const Matrix &matrix) {
  size_t n_rows = matrix.getNumRows();
  size_t n_cols = matrix.getNumCols();

  for (size_t i = 0; i < n_rows; ++i) {
    for (size_t j = 0; j < n_cols; ++j)
      output << matrix[i][j] << ' ';
    output << std::endl;
  }
  return output;
}

std::istream &task::operator>>(std::istream &input, Matrix &matrix) {
  size_t n_rows, n_cols;
  input >> n_rows >> n_cols;

  matrix.resize(n_rows, n_cols);
  for (size_t i = 0; i < n_rows; ++i)
    for (size_t j = 0; j < n_cols; ++j)
      input >> matrix[i][j];

  return input;
}





