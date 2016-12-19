// Copyright (c) 2007-2011 libmv authors.
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.

#include "conditioning.hpp"
#include <vector>
#include <cmath>
using namespace std;

namespace orsa {

  void PreconditionerFromPoints(int width, int height, Mat *T) {
    // Build the normalization matrix
    double dNorm = 1.0 / sqrt( static_cast<double>(width*height) ); 

    (*T) = Mat::eye(3);
    (*T)(0,0) = (*T)(1,1) = dNorm;
    (*T)(0,2) = -.5f*width*dNorm;
    (*T)(1,2) = -.5*height*dNorm;
  }

  void NormalizePoints(const Mat &points,
    Mat *normalized_points,
    Mat *T,
    int width,
    int height) {
      PreconditionerFromPoints(width, height, T);
      ApplyTransformationToPoints(points, *T, normalized_points);
  }

  // Denormalize the results. See Hartley-Zisserman page 109.
  void UnnormalizerT::Unnormalize(const Mat &T1, const Mat &T2, Mat *H)  {
    *H = T2.t() * (*H) * T1;
  }

  void UnnormalizerI::Unnormalize(const Mat &T1, const Mat &T2, Mat *H)  {
    *H = T2.inv() * (*H) * T1;
  }

  // Return the square of a number.
  template<typename T>
  inline T Square(T x) {
    return x * x;
  }

  void MeanAndVarianceAlongRows(const Mat &A,
    vector<double> *mean_pointer,
    vector<double> *variance_pointer) {
      vector<double> &mean = *mean_pointer;
      vector<double> &variance = *variance_pointer;
      int n = A.nrow();
      int m = A.ncol();
      mean = vector<double>(n, 0.0);
      variance = vector<double>(n, 0.0);

      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
          double x = A(i, j);
          mean[i] += x;
          variance[i] += x * x;
        }
      }

      for (int i = 0; i < n; ++i)
        mean[i] /= m;

      for (int i = 0; i < n; ++i) {
        variance[i] = variance[i] / m - Square(mean[i]);
      }
  }

// Hartley-Zisserman 4.4.4 pag.109
void PreconditionerFromPoints(const Mat &points, Mat *T) {
  vector<double> mean, variance;
  MeanAndVarianceAlongRows(points, &mean, &variance);

  double xfactor = sqrt(2.0 / variance[0]);
  double yfactor = sqrt(2.0 / variance[1]);

  // If variance is equal to 0.0 set scaling factor to identity.
  // -> Else it will provide nan value (because division by 0).
  if (variance[0] < 1e-8)
    xfactor = mean[0] = 1.0;
  if (variance[1] < 1e-8)
    yfactor = mean[1] = 1.0;

  (*T)(0,0) = xfactor; (*T)(0,1) =  0; (*T)(0,2) = -xfactor * mean[0];
  (*T)(1,0) = 0; (*T)(1,1) =  yfactor; (*T)(1,2) = -yfactor * mean[1];
  (*T)(2,0) = 0; (*T)(2,1) =  0; (*T)(2,2) = 1.0;
}

void ApplyTransformationToPoints(const Mat &points,
                                 const Mat &T,
                                 Mat *transformed_points) {
  const int n = points.ncol();
  (*transformed_points) = Mat(2,n);
  for (int i = 0; i < n; ++i) {
    Mat in(3,1), out(3,1);
    in(0,0) = points(0, i); in(1,0) = points(1, i); in(2,0) = 1.0;
    out = T * in;
    (*transformed_points)(0, i) = out(0)/out(2);
    (*transformed_points)(1, i) = out(1)/out(2);
  }
}

void NormalizePoints(const Mat &points,
                     Mat *normalized_points,
                     Mat *T) {
  PreconditionerFromPoints(points, T);
  ApplyTransformationToPoints(points, *T, normalized_points);
}

} // namespace orsa
