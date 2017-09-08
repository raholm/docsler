#ifndef DOCSLER_UTIL_H_
#define DOCSLER_UTIL_H_

#include <Rcpp.h>
#include <iostream>

#include "def.h"

namespace docsler {

  inline DoubleVector convert_from_R(const Rcpp::NumericVector& v) {
    return Rcpp::as<DoubleVector>(v);
  }

  inline IntVector convert_from_R(const Rcpp::IntegerVector& v) {
    return Rcpp::as<IntVector>(v);
  }

  inline DoubleMatrix convert_from_R(const Rcpp::NumericMatrix& m) {
    auto nrow = m.nrow();
    DoubleMatrix mat(nrow);
    for (unsigned i = 0; i < nrow; ++i) {
      auto row = m(i, Rcpp::_);
      mat.at(i) = DoubleVector{row.begin(), row.end()};
    }
    return mat;
  }

} // namespace docsler

#endif // DOCSLER_UTIL_H_
