/**
 * @file orsa_model.hpp
 * @brief Model estimation by ORSA (aka AC-RANSAC) algorithm
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

#ifndef ORSA_MODEL_H
#define ORSA_MODEL_H

#include <vector>
#include "matrix.h"

namespace orsa {

/// Generic class for model estimation with ORSA algorithm.
///
/// Subclasses must follow this interface:
///   1. SizeSample() Number correspondences necessary to compute a model.
///   2. NbModels() Number models from sample of SizeSample() correspondences.
///   3. DistToPoint() Residual is distance to a point or to a line?
///   4. Fit(const vector<size_t> &indices, vector<Model> *models)
///        Compute model(s) compatible with indexed correspondences.
///   5. Error(const Model &model, size_t index)
///        Reprojection square error for indexed correspondence.
///   6. Unnormalize(Model *model)
///        Unnormalize a given model (from normalized to image space).

class OrsaModel {
 public:
  typedef libNumerics::vector<double> Vec;
  typedef libNumerics::matrix<double> Mat;
  typedef Mat Model;

  /// Constructor
  OrsaModel(const Mat &x1, int w1, int h1,
            const Mat &x2, int w2, int h2);
  virtual ~OrsaModel() {}

  /// Minimum number of points required to compute a model.
  /// - homography -> 4
  /// - fundamental 7 pts -> 7
  /// - fundamental 8 pts -> 8
  virtual int SizeSample() const = 0;

  /// Maximum number of models possibly computed from a sample.
  /// - homography -> 1
  /// - fundamental 7 pts -> 3
  /// - fundamental 8 pts -> 1
  virtual int NbModels() const = 0;

  /// Indicate if distance used to distinguish inlier/outlier is to a point
  /// (true) or a line (false).
  /// - homography -> true
  /// - fundamental -> false
  virtual bool DistToPoint() const = 0;

  /// Computes the square error associated to a correspondence with model.
  /// \param model The considered model to evaluate.
  /// \param index The point index stored in the Kernel.
  /// \param side In which image is the error measured?
  virtual double Error(const Model &model, int index, int* side=0) const = 0;

  /// Computes the models associated to indexed sample.
  /// \param indices Indices of points to consider for model estimation.
  /// \param models  Estimated model(s) from sampled point.
  virtual void Fit(const std::vector<int> &indices,
                   std::vector<Model> *models) const = 0;

  /// Unnormalize a given model.
  /// \param model The model to unnormalize.
  virtual void Unnormalize(Model *model) const = 0;

  /// Generic implementation of ORSA (Optimized Random Sampling Algorithm). 
  double orsa(std::vector<int> &vec_inliers,
              size_t nIter = 1000,
              double *precision = NULL,
              Model *model = NULL,
              bool bVerbose = false) const;

  /// Compute model from points.
  bool ComputeModel(const std::vector<int> &indices,
                    Model *model) const;

  /// Enable the model refinement until convergence.
  void setRefineUntilConvergence(bool value);
  
  /// Return if convergence check is on or off.
  bool getRefineUntilConvergence() const;

protected:
  Mat x1_; ///< Points in image 1
  Mat x2_; ///< Points in image 2
  Mat N1_; ///< Normalization for x1_
  Mat N2_; ///< Normalization for x2_ 
  double logalpha0_[2]; ///< Log probability of error<=1, set by subclass
  bool bConvergence;

private:
  /// Distance and associated index
  struct ErrorIndex {
    double error; ///< Square error
    int index; ///< Correspondence index
    int side;     ///< Error in image 1 (side=0) or 2 (side=1)?
    /// Constructor
    ErrorIndex(double e=0, int i=0, int s=0): error(e), index(i), side(s) {}
    bool operator<(const ErrorIndex& e) const { return (error<e.error); }
  };
  ErrorIndex bestNFA(const std::vector<ErrorIndex>& e,
                     double loge0, double maxThreshold,
                     const std::vector<float> & vec_logc_n,
                     const std::vector<float> & vec_logc_k) const;
  double denormalizeError(double squareError, int side) const;

  /// Iterative minimization NFA/RMSE.
  void refineUntilConvergence(const std::vector<float> & vec_logc_n,
                              const std::vector<float> & vec_logc_k,
                              double loge0,
                              double maxThreshold,
                              double minNFA,
                              Model *model,
                              bool bVerbose,
                              std::vector<int> & vec_inliers,
                              double & errorMax,
                              int & side) const;
};

}  // namespace orsa

#endif
