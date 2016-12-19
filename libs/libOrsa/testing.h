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

#ifndef TESTING_TESTING_H_
#define TESTING_TESTING_H_

#include "matrix.h"
#include "TestHarness.h"

#define EXPECT_MATRIX_NEAR(a, b, tolerance) \
do { \
  bool dims_match = (a.nrow() == b.nrow()) && (a.ncol() == b.ncol()); \
  CHECK_EQUAL(a.nrow(),b.nrow()); \
  CHECK_EQUAL(a.ncol(),b.ncol()); \
  if (dims_match) { \
    for (int r = 0; r < a.nrow(); ++r) { \
      for (int c = 0; c < a.ncol(); ++c) { \
        DOUBLES_EQUAL(a(r, c), b(r, c), tolerance); \
      } \
    } \
  } \
} while(false);

#define EXPECT_MATRIX_NEAR_ZERO(a, tolerance) \
do { \
  for (int r = 0; r < a.nrow(); ++r) { \
    for (int c = 0; c < a.ncol(); ++c) { \
      DOUBLES_EQUAL(0.0, a(r, c), tolerance) \
    } \
  } \
} while(false);

#define EXPECT_MATRIX_EQ(a, b) \
do { \
  bool dims_match = (a.nrow() == b.nrow()) && (a.ncol() == b.ncol()); \
  CHECK_EQUAL(a.nrow(),b.nrow()); \
  CHECK_EQUAL(a.ncol(),b.ncol()); \
  if (dims_match) { \
    for (int r = 0; r < a.nrow(); ++r) { \
      for (int c = 0; c < a.ncol(); ++c) { \
        CHECK_EQUAL(a(r, c), b(r, c)) \
      } \
    } \
  } \
} while(false);

#define EXPECT_NEAR(expected,actual,threshold) \
  DOUBLES_EQUAL(expected,actual,threshold);

#define EXPECT_TRUE(condition) \
  CHECK(condition);

#define EXPECT_FALSE(condition) \
  CHECK(!condition);

#define EXPECT_EQ(a, b) CHECK_EQUAL(a,b);

#endif  // TESTING_TESTING_H_
