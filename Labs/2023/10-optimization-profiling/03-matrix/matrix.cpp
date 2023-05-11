#include "matrix.hpp"

#include <algorithm>
#include <cassert>
#include <Eigen/Dense>

matrix matrix::transpose() const {
  //constructing a matrix inverting the number of cols and rows
  matrix tr_mat(m_cols,m_rows); 
  //filling the previous matrix
  for(size_t i=0; i < m_cols; i++){
    for(size_t j=0; j < m_rows; j++){
      tr_mat(i,j) = value(j,i);
    }
  }
  return tr_mat;
}
//CACHE-AWERNESS
/* Since we've seen that transposing is not much costly, we transpose the first matrix in order to have row-major matrix  and a better cache-line
*/
matrix operator*(const matrix &A, const matrix &B) {
  //checking if input dimensions are correct
  assert(A.get_cols() == B.get_rows());
  //constructing a matrix of dimension (nrows_A x ncols_B)
  matrix prod_mat(A.get_rows(),B.get_cols());

  //transposing the first matrix
  matrix tmp = A.transpose();
  //filling the previous matrix
  for(size_t i=0; i < prod_mat.get_rows(); i++){
    for(size_t j=0; j < prod_mat.get_cols(); j++){
      prod_mat(i,j) = 0;
      for(size_t k=0; k < A.get_cols();k++){
        prod_mat(i,j) += tmp(k,i)*B(k,j);
      }
    }
  }
  return prod_mat;
}

//EIGEN MULTIPLICATION
matrix matrix::mmult_eigen(const matrix &other){
  //checking if input dimensions are correct
  assert(get_cols() == other.get_rows());
  //constructing a matrix of dimension (nrows_A x ncols_B)
  matrix result(get_rows(),other.get_cols());


  Eigen::Map<const Eigen::MatrixXd> eigen_A(get_data(),get_rows(),get_cols());
  Eigen::Map<const Eigen::MatrixXd> eigen_B(other.get_data(),other.get_rows(),other.get_cols());
  Eigen::Map<Eigen::MatrixXd> eigen_C(result.get_data(),result.get_rows(),result.get_cols());

  eigen_C = eigen_A * eigen_B;
  return result;
}


void matrix::solve(matrix &rhs) {
  size_t ii, jj, kk;
  double f;

  // Factorize
  if (!factorized) {
    factorize();
    std::cout << "factorize !" << std::endl;
  }

  double *b = rhs.get_data();
  // Do Forward Substitution
  std::cout << "fwdsub !" << std::endl;
  for (ii = 0; ii < get_rows(); ++ii) {
    f = b[m_p[ii]];
    for (kk = 0; kk < ii; ++kk) {
      f -= value(m_p[ii], kk) * b[m_p[kk]];
    }
    b[m_p[ii]] = f;
  }

  // Do Backward Substitution
  std::cout << "bwdsub !" << std::endl;
  for (jj = 1; jj <= get_rows(); ++jj) {
    ii = get_rows() - jj;
    f = b[m_p[ii]];
    for (kk = ii + 1; kk < get_cols(); ++kk) {
      f -= value(m_p[ii], kk) * b[m_p[kk]];
    }
    b[m_p[ii]] = f / value(m_p[ii], ii);
  }
}

void matrix::factorize() {
  m_p.resize(m_rows, 0);
  for (size_t ii = 0; ii < m_rows; ++ii) {
    m_p[ii] = ii;
  }

  size_t m = this->get_rows();
  size_t n = this->get_cols();
  size_t ii, jj, kk;

  double pivot = 0., maxpivot = 0.;

  size_t imaxpivot = 0;

  assert(m == n);
  for (ii = 0; ii < m - 1; ++ii) {
    maxpivot = value(m_p[ii], ii);
    imaxpivot = ii;
    for (kk = ii + 1; kk < m; ++kk)
      if (value(m_p[kk], ii) > maxpivot) {
        maxpivot = value(m_p[kk], ii);
        imaxpivot = kk;
      }

    if (imaxpivot != ii) {
      std::swap(m_p[ii], m_p[imaxpivot]);
    }

    pivot = value(m_p[ii], ii);
    for (jj = ii + 1; jj < m; ++jj) {
      value(m_p[jj], ii) = value(m_p[jj], ii) / pivot;

      for (kk = ii + 1; kk < n; ++kk)
        value(m_p[jj], kk) += -value(m_p[ii], kk) * value(m_p[jj], ii);
    }
  }
  factorized = true;
}
