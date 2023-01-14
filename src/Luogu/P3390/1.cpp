#include <bits/stdc++.h>
using namespace std;
using int_t = unsigned long long int;
const int_t mod = (int_t)1e9 + 7;
template <typename ValType>
class Matrix;
template <typename T>
ostream &operator<<(ostream &os, const Matrix<T> &mat);
template <typename T>
istream &operator>>(istream &os, const Matrix<T> &mat);
template <typename ValType>
class Matrix {
private:
  ValType *data;
  int_t row;
  int_t col;
  int_t size;
  int_t num;

public:
  ~Matrix() { delete[] data; }
  Matrix(const Matrix<ValType> &other)
    : row(other.row), col(other.col), size(other.size), num(other.num) {
    data = new ValType[other.num];
    memcpy(data, other.data, other.size);
  }
  Matrix(int_t r, int_t c): row(r), col(c) {
    this->row = r;
    this->col = c;
    num = (row + 1) * (col + 1);
    data = new ValType[num];
    size = sizeof(ValType) * num;
    memset(data, 0, size);
  }
  ValType &at(int_t r, int_t c) { return data[c + r * col]; }
  Matrix<ValType> operator*(Matrix<ValType> &mat) throw(const char *) {
    if (this->col != mat.row)
      throw "Column number of matrix1 doesn't equals that in matrix2";
    Matrix<ValType> result(this->row, mat.col);
    for (int_t i = 1; i <= this->row; i++) {
      for (int_t j = 1; j <= mat.col; j++) {
        int_t sum = 0;
        for (int_t x = 1; x <= this->col; x++) {
          sum = (sum % mod + at(i, x) % mod * mat.at(x, j) % mod) % mod;
        }
        result.at(i, j) += sum % mod;
      }
    }
    return result;
  }
  int_t getCol() const { return col; }
  int_t getRow() const { return row; }
  Matrix<ValType> &operator=(const Matrix<ValType> &other) {
    this->col = other.col;
    this->num = other.num;
    this->row = other.row;
    this->size = other.size;
    this->data = new ValType[num];
    memcpy(data, other.data, size);
  }
  friend ostream &operator<< <>(ostream &os, const Matrix<ValType> &mat);
  friend istream &operator>> <>(istream &os, const Matrix<ValType> &mat);
};
template <typename ValType>
ostream &operator<<(ostream &os, Matrix<ValType> &mat) {
  for (int_t i = 1; i <= mat.getRow(); i++) {
    for (int_t j = 1; j <= mat.getCol(); j++) {
      os << mat.at(i, j) % mod << " ";
    }
    os << endl;
  }
  return os;
}
template <typename ValType>
istream &operator>>(istream &is, Matrix<ValType> &mat) {
  for (int_t i = 1; i <= mat.getRow(); i++) {
    for (int_t j = 1; j <= mat.getCol(); j++) {
      is >> mat.at(i, j);
      mat.at(i, j) %= mod;
    }
  }
  return is;
}
using MatType = Matrix<int_t>;
int main() {
  int_t n, index;
  cin >> n >> index;
  MatType mat(n, n);
  cin >> mat;
  MatType result = mat;
  for (index--; index; index >>= 1, mat = mat * mat) {
    if (index & 1) result = result * mat;
  }
  cout << result;
  return 0;
}
