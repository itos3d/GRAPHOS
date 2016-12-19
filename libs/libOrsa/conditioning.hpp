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

#ifndef LIBS_MULTIVIEW_CONDITIONNING_H_
#define LIBS_MULTIVIEW_CONDITIONNING_H_

#include "matrix.h"

//-- Implementation of normalized coordinates.
// Normalization improve accuracy of results and provide benefits
//  that make scale and coordinate origin invariant.
// Two normalization algorithm are implemented :
// - Normalization from image dimension to [-.5, .5]
// - Normalization with zero mean and variance to 1.0
//
namespace orsa {
  typedef libNumerics::matrix<double> Mat;

// Point conditioning (compute Transformation matrix) (T must be (3,3)) :
void PreconditionerFromPoints(const Mat &points, Mat *T);

// Apply a given transformation to points (T must be (3,3)) :
void ApplyTransformationToPoints(const Mat &points,
                                 const Mat &T,
                                 Mat *transformed_points);
//
//  Normalize point
// The implementation follows Algorithm 4.2 from Hartley-Zisserman page 109.
void NormalizePoints(const Mat &points,
                     Mat *normalized_points,
                     Mat *T);

// Point conditioning (compute Transformation matrix)
void PreconditionerFromPoints(int width, int height, Mat *T);

//
//  Normalize point
//  From image coordinates to [-.5, .5]
void NormalizePoints(const Mat &points,
                      Mat *normalized_points,
                      Mat *T, int width, int height);

/// Use inverse for unnormalize
struct UnnormalizerI {
  // Denormalize the results. See Hartley-Zisserman page 109.
  // All matrices must be (3,3)
  static void Unnormalize(const Mat &T1, const Mat &T2, Mat *H);
};

/// Use transpose for unnormalize
struct UnnormalizerT {
  // Denormalize the results. See Hartley-Zisserman page 109.
  // All matrices must be (3,3)
  static void Unnormalize(const Mat &T1, const Mat &T2, Mat *H);
};

} //namespace orsa

#endif // LIBS_MULTIVIEW_CONDITIONNING_H_
