/**
 * @file homography_model.cpp
 * @brief Homography matrix model
 * @author Pascal Monasse, Pierre Moulon
 * 
 * Copyright (c) 2011 Pascal Monasse, Pierre Moulon
 * All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "homography_model.hpp"
#include "conditioning.hpp"
#include "numerics.h"

#include <iostream>
#include <limits>

#define _USE_MATH_DEFINES // For Windows (M_PI)
#include <math.h>

namespace orsa {

/// Minimal inverse condition value for a valid homography matrix
static const double ICOND_MIN = 0.1;

/// Constructor, initializing \c logalpha0_
HomographyModel::HomographyModel(const Mat &x1, int w1, int h1,
                                 const Mat &x2, int w2, int h2,
                                 bool symError)
: OrsaModel(x1, w1, h1, x2, w2, h2), symError_(symError) {
  logalpha0_[0] = log10(M_PI/(w1*(double)h1) /(N1_(0,0)*N1_(0,0)));
  logalpha0_[1] = log10(M_PI/(w2*(double)h2) /(N2_(0,0)*N2_(0,0)));
}

/// Unnormalize a given model (from normalized to image space).
void HomographyModel::Unnormalize(Model *model) const  {
  UnnormalizerI::Unnormalize(N1_, N2_, model);
}

/// Square of number.
inline double sqr(double x) {
  return (x*x);
}

/// If H is not orientation preserving at the point, the error is infinite.
/// For this test, it is assumed that det(H)>0.
/// \param H The homography matrix.
/// \param index The correspondence index
/// \param side In which image is the error measured?
/// \return The square reprojection error.
double HomographyModel::Error(const Mat &H, int index, int* side) const {
  double err = std::numeric_limits<double>::infinity();
  if(side) *side=1;
  libNumerics::vector<double> x(3);
  // Transfer error in image 2
  x(0) = x1_(0,index); x(1) = x1_(1,index); x(2) = 1.0;
  x = H * x;
  if(x(2)>0) {
    x /= x(2);
    err = sqr(x2_(0,index)-x(0)) + sqr(x2_(1,index)-x(1));
  }
  // Transfer error in image 1
  if(symError_) { // ... but only if requested
    x(0) = x2_(0,index); x(1) = x2_(1,index); x(2) = 1.0;
    x = H.inv() * x;
    if(x(2)>0) {
      x /= x(2);
      double err1 = sqr(x1_(0,index)-x(0)) + sqr(x1_(1,index)-x(1));
      if(err1>err) { // Keep worse error
        err=err1;
        if(side) *side=0;
      }
    }
  }
  return err;
}

/// 2D homography estimation from point correspondences.
void HomographyModel::Fit(const std::vector<int> &indices,
                          std::vector<Model> *H) const {
  if(4 > indices.size())
    return;
  const int n = static_cast<int>( indices.size() );
  libNumerics::matrix<double> A = libNumerics::matrix<double>::zeros(n*2,9);
  for (int i = 0; i < n; ++i) {
    int index = indices[i];
    int j = 2*i;
    A(j,0) = x1_(0, index);
    A(j,1) = x1_(1, index);
    A(j,2) = 1.0;
    A(j,6) = -x2_(0, index) * x1_(0, index);
    A(j,7) = -x2_(0, index) * x1_(1, index);
    A(j,8) = -x2_(0, index);

    ++j;
    A(j,3) = x1_(0, index);
    A(j,4) = x1_(1, index);
    A(j,5) = 1.0;
    A(j,6) = -x2_(1, index) * x1_(0, index);
    A(j,7) = -x2_(1, index) * x1_(1, index);
    A(j,8) = -x2_(1, index);
  }

  libNumerics::vector<double> vecNullspace(9);
  if( libNumerics::SVD::Nullspace(A,&vecNullspace) )
  {
    libNumerics::matrix<double> M(3,3);
    M.read(vecNullspace);
    if(M.det() < 0)
      M = -M;
    M /= M(2,2);

    if(libNumerics::SVD::InvCond(M)>=ICOND_MIN &&
       IsOrientationPreserving(indices,M) )
      H->push_back(M);
  }
}

/// Is \a H orientation preserving near match points of index in \a indices?
/// It is assumed that det(H)>0, otherwise the sign tests should be reversed.
bool HomographyModel::IsOrientationPreserving(const std::vector<int>&indices,
                                              const Mat& H) const {
  libNumerics::matrix<double> h=H.row(2);
  std::vector<int>::const_iterator it=indices.begin(), end=indices.end();
  for(; it != end; ++it)
    if(h(0)*x2_(0,*it)+h(1)*x2_(1,*it)+h(2) <= 0)
      return false;
  return true;
}

}  // namespace orsa
