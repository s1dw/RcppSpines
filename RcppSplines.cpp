#include <Rcpp.h>
using namespace std;
using namespace Rcpp;

/* M-spline */
NumericMatrix interMSpline (int p, NumericVector k, int rowNum, int colNum, NumericVector x, NumericMatrix y) {
  NumericMatrix z(rowNum, colNum - 1);
  double A = 0;
  double B = 0;
  for (int j = 0; j < (colNum - 1); j++) {
    for (int i = 0; i < rowNum; i++) {
      ((p-1) * (k(j+p) - k(j)) > 0) ? A = ((p) * (x(i) - k(j))) / ((p-1) * (k(j+p) - k(j))) * y(i, j): A = 0;
      ((p-1) * (k(j+p) - k(j)) > 0) ? B = ((p) * (k(j+p) - x(i))) / ((p-1) * (k(j+p) - k(j))) * y(i, (j+1)): B = 0;
      z(i, j) = (A + B);
    }
  }
  return z;
}
// [[Rcpp::export]]
NumericMatrix mSpline (int p, NumericVector k, NumericVector x){
  int N = k.length();
  int rowNum = x.length();
  NumericMatrix M(rowNum , N - 1);

  for (int h = 0; h < rowNum; h++) {
    for (int w = 0; w < (N - 1); w++) {
      M(h, w) = x(h);
    }
  }
  for (int j = 0; j < N - 1; j++) {
    for (int i = 0; i < rowNum; i++) {
      ((M(i, j) >= k(j)) && (M(i, j) < k(j+1))) ? M(i, j) = (1 / (k(j+1) - k(j))) : M(i, j) = 0;
    }
  }
  if(p == 1) return M;

  int j = 2;
  for (int i = 0; i < p - 1; i++) {
    M = interMSpline (j, k, rowNum, (N - i - 1), x, M);
    j++;
  }
  return M;
}

/* NB-spline */
NumericMatrix interBSpline (int p, NumericVector k, int rowNum, int colNum, NumericVector x, NumericMatrix y) {
  NumericMatrix z(rowNum, colNum - 1);
  double A = 0;
  double B = 0;
  for (int j = 0; j < (colNum - 1); j++) {
    for (int i = 0; i < rowNum; i++) {
      ((k(j+p-1) - k(j)) > 0) ? A = (x(i) - k(j)) / (k(j+p-1) - k(j)) * y(i, j) : A = 0;
      ((k(j+p) - k(j+1)) > 0) ? B = (k(j+p) - x(i)) / (k(j+p) - k(j+1)) * y(i, (j+1)) : B = 0;
      z(i, j) = (A + B);
    }
  }
  return z;
}
// [[Rcpp::export]]
NumericMatrix bSpline (int p, NumericVector k, NumericVector x){
  int N = k.length();
  int rowNum = x.length();
  NumericMatrix B(rowNum , N - 1);

  for (int h = 0; h < rowNum; h++) {
    for (int w = 0; w < (N - 1); w++) {
      B(h, w) = x(h);
    }
  }
  for (int j = 0; j < N - 1; j++) {
    for (int i = 0; i < rowNum; i++) {
      ((B(i, j) >= k(j)) && (B(i, j) < k(j+1))) ? B(i, j) = 1 : B(i, j) = 0;
    }
  }

  if(p == 1) return B;

  int j = 2;
  for (int i = 0; i < p - 1; i++) {
    B = interBSpline (j, k, rowNum, (N - i - 1), x, B);
    j++;
  }
  return B;
 }

/* I-spline */
// [[Rcpp::export]]
NumericMatrix iSpline (int p, NumericVector k, NumericVector x){
  NumericMatrix NB = bSpline(p, k, x);
  NumericMatrix I(NB.rows(), NB.cols()-1);
  for(int i = 0; i < NB.rows(); i++){
    for(int j = 0; j < NB.cols(); j++){
      for(int k = (j+1); k < NB.cols(); k++){
        I(i, j) = I(i, j) + NB(i, k);
      }
    }
  }
  return I;
}



