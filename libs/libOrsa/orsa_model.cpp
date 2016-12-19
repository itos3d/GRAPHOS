/**
 * @file orsa_model.cpp
 * @brief Model estimation by ORSA (aka AC-RANSAC) algorithm
 * @author Lionel Moisan, Pascal Monasse, Pierre Moulon
 * 
 * Copyright (c) 2007,2010-2011 Lionel Moisan, Pascal Monasse, Pierre Moulon
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

#include "orsa_model.hpp"
#include "conditioning.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>

namespace orsa {

/// Points are normalized according to image dimensions. Subclass must
/// initialize logalpha0_ and take account of normalization in doing that.
/// Matrices \a x1 and \a x2 are 2xn, representing Cartesian coordinates.
OrsaModel::OrsaModel(const Mat &x1, int w1, int h1,
                     const Mat &x2, int w2, int h2)
: x1_(x1.nrow(), x1.ncol()), x2_(x2.nrow(), x2.ncol()),
  N1_(3,3), N2_(3,3), bConvergence(false) {
  assert(2 == x1_.nrow());
  assert(x1_.nrow() == x2_.nrow());
  assert(x1_.ncol() == x2_.ncol());

  // Normalize both images by same factor, as our thresholds for SVD are based
  // on zoom around 1
  int w=std::max(w1,w2), h=std::max(h1,h2);
  NormalizePoints(x1, &x1_, &N1_, w, h);
  NormalizePoints(x2, &x2_, &N2_, w, h);
  logalpha0_[0] = logalpha0_[1] = 0;
}

/// If multiple solutions are possible, return false.
bool OrsaModel::ComputeModel(const std::vector<int> &indices,
                             Model *model) const {
    std::vector<Model> models;
    Fit(indices, &models);
    if(models.size() != 1)
      return false;
    *model = models.front();
    Unnormalize(model);
    return true;
}

/// logarithm (base 10) of binomial coefficient
static float logcombi(int k, int n)
{
  if (k>=n || k<=0) return(0.0);
  if (n-k<k) k=n-k;
  double r = 0.0;
  for (int i = 1; i <= k; i++)
    r += log10((double)(n-i+1))-log10((double)i);

  return static_cast<float>(r);
}

/// tabulate logcombi(.,n)
static void makelogcombi_n(int n, std::vector<float> & l)
{
  l.resize(n+1);
  for (int k = 0; k <= n; k++)
    l[k] = logcombi(k,n);
}

/// tabulate logcombi(k,.)
static void makelogcombi_k(int k,int nmax, std::vector<float> & l)
{
  l.resize(nmax+1);
  for (int n = 0; n <= nmax; n++)
    l[n] = logcombi(k,n);
}

/// Find best NFA and number of inliers wrt square error threshold in e.
OrsaModel::ErrorIndex OrsaModel::bestNFA(const std::vector<ErrorIndex>& e,
                                         double loge0,
                                         double maxThreshold,
                                         const std::vector<float> &logc_n,
                                         const std::vector<float> &logc_k) const
{
  const int startIndex = SizeSample();
  const double multError = (DistToPoint()? 1.0: 0.5);

  ErrorIndex bestIndex(std::numeric_limits<double>::infinity(),
                       startIndex,
                       0);
  const int n = static_cast<int>( e.size() );
  for(int k=startIndex+1; k<=n && e[k-1].error<=maxThreshold; ++k) {
    double logalpha = logalpha0_[e[k-1].side] + multError*log10(e[k-1].error);
    ErrorIndex index(loge0+logalpha*(double)(k-startIndex)+logc_n[k]+logc_k[k],
                     k, e[k-1].side);
    if(index.error < bestIndex.error)
      bestIndex = index;
  }
  return bestIndex;
}

/// Denormalize error, recover real error in pixels.
double OrsaModel::denormalizeError(double squareError, int side) const {
  return sqrt(squareError)/(side==0? N1_(0,0): N2_(0,0));
}

/// Get a (sorted) random sample of size X in [0:n-1]
static void random_sample(std::vector<int> &k, int X, int n)
{
  for(int i=0; i<X; i++) {
    int r = (rand()>>3)%(n-i), j;
    for(j=0; j<i && r>=k[j]; j++)
      r++;
    int j0 = j;
    for(j=i; j > j0; j--)
      k[j]=k[j-1];
    k[j0] = r;
  }
}

/// Pick a random sample
/// \param sizeSample The size of the sample.
/// \param vec_index  The possible data indices.
/// \param sample The random sample of sizeSample indices (output).
static void UniformSample(int sizeSample,
                          const std::vector<int> &vec_index,
                          std::vector<int> *sample) {
  sample->resize(sizeSample);
  random_sample(*sample, sizeSample, static_cast<int>(vec_index.size()));
  for(int i = 0; i < sizeSample; ++i)
    (*sample)[i] = vec_index[ (*sample)[i] ];
}

/// Generic implementation of 'ORSA':
/// A Probabilistic Criterion to Detect Rigid Point Matches
///    Between Two Images and Estimate the Fundamental Matrix.
/// Bibtex :
/// @article{DBLP:journals/ijcv/MoisanS04,
///  author    = {Lionel Moisan and B{\'e}renger Stival},
///  title     = {A Probabilistic Criterion to Detect Rigid Point Matches
///    Between Two Images and Estimate the Fundamental Matrix},
///  journal   = {International Journal of Computer Vision},
///  volume    = {57},
///  number    = {3},
///  year      = {2004},
///  pages     = {201-218},
///  ee        = {http://dx.doi.org/10.1023/B:VISI.0000013094.38752.54},
///  bibsource = {DBLP, http://dblp.uni-trier.de}
///}
/// 
/// ORSA is based on an a contrario criterion of
/// inlier/outlier discrimination, is parameter free and relies on an optimized
/// random sampling procedure. It returns the log of NFA and optionally
/// the best estimated model.
///
/// \param vec_inliers Output vector of inlier indices.
/// \param nIter The number of iterations.
/// \param precision (input/output) threshold for inlier discrimination.
/// \param model The best computed model.
/// \param bVerbose Display optimization statistics.
double OrsaModel::orsa(std::vector<int> & vec_inliers,
                       size_t nIter,
                       double *precision,
                       Model *model,
                       bool bVerbose) const {
  vec_inliers.clear();

  const int sizeSample = SizeSample();
  const int nData = x1_.ncol();
  if(nData <= sizeSample)
    return std::numeric_limits<double>::infinity();

  const double maxThreshold = (precision && *precision>0)?
    *precision * *precision *N2_(0,0)*N2_(0,0): // Square max error
    std::numeric_limits<double>::infinity();

  std::vector<ErrorIndex> vec_residuals(nData); // [residual,index]
  std::vector<int> vec_sample(sizeSample); // Sample indices

  // Possible sampling indices (could change in the optimization phase)
  std::vector<int> vec_index(nData);
  for (int i = 0; i < nData; ++i)
    vec_index[i] = i;

  // Precompute log combi
  double loge0 = log10((double)NbModels() * (nData-sizeSample));
  std::vector<float> vec_logc_n, vec_logc_k;
  makelogcombi_n(nData, vec_logc_n);
  makelogcombi_k(sizeSample,nData, vec_logc_k);

  // Reserve 10% of iterations for focused sampling
  size_t nIterReserve=nIter/10;
  nIter -= nIterReserve;

  // Output parameters
  double minNFA = std::numeric_limits<double>::infinity();
  double errorMax = 0;
  int side=0;

  // Main estimation loop.
  for (size_t iter=0; iter < nIter; iter++) {
    UniformSample(sizeSample, vec_index, &vec_sample); // Get random sample

    std::vector<Model> vec_models; // Up to max_models solutions
    Fit(vec_sample, &vec_models);

    // Evaluate models
    bool better=false;
    for (size_t k = 0; k < vec_models.size(); ++k)
    {
      // Residuals computation and ordering
      for (int i = 0; i < nData; ++i)
      {
        int s;
        double error = Error(vec_models[k], i, &s);
        vec_residuals[i] = ErrorIndex(error, i, s);
      }
      std::sort(vec_residuals.begin(), vec_residuals.end());

      // Most meaningful discrimination inliers/outliers
      ErrorIndex best = bestNFA(vec_residuals, loge0, maxThreshold,
                                vec_logc_n, vec_logc_k);
      if(best.error < minNFA) // A better model was found
      {
        better = true;
        minNFA = best.error;
        side = best.side;
        vec_inliers.resize(best.index);
        for (int i=0; i<best.index; ++i)
          vec_inliers[i] = vec_residuals[i].index;
        errorMax = vec_residuals[best.index-1].error; // Error threshold
        if(best.error<0 && model) *model = vec_models[k];
        if(bVerbose)
        {
          std::cout << "  nfa=" << minNFA
                    << " inliers=" << vec_inliers.size()
                    << " precision=" << denormalizeError(errorMax, side)
                    << " im" << side+1
                    << " (iter=" << iter;
          if(best.error<0) {
            std::cout << ",sample=" << vec_sample.front();
            std::vector<int>::const_iterator it=vec_sample.begin();
            for(++it; it != vec_sample.end(); ++it)
              std::cout << ',' << *it;
          }
          std::cout << ")" <<std::endl;
        }
      }
    }
    // ORSA optimization: draw samples among best set of inliers so far
    if((better && minNFA<0) || (iter+1==nIter && nIterReserve)) {
        if(vec_inliers.empty()) { // No model found at all so far
            nIter++; // Continue to look for any model, even not meaningful
            nIterReserve--;
        } else {
            vec_index = vec_inliers;
            if(nIterReserve) {
                nIter = iter+1+nIterReserve;
                nIterReserve=0;
            }
        }
    }
  }

  if(minNFA >= 0)
    vec_inliers.clear();

  if(bConvergence)
    refineUntilConvergence(vec_logc_n, vec_logc_k, loge0,
                           maxThreshold, minNFA, model, bVerbose, vec_inliers,
                           errorMax, side);

  if(precision)
    *precision = denormalizeError(errorMax, side);
  if(model && !vec_inliers.empty())
    Unnormalize(model);
  return minNFA;
}

/// Refine the model on all the inliers with the "a contrario" model
/// The model is refined while the NFA threshold is not stable.
void OrsaModel::refineUntilConvergence(const std::vector<float> & vec_logc_n,
                                       const std::vector<float> & vec_logc_k,
                                       double loge0,
                                       double maxThreshold,
                                       double minNFA,
                                       Model *model,
                                       bool bVerbose,
                                       std::vector<int> & vec_inliers,
                                       double & errorMax,
                                       int & side) const
{
  std::cout << "\n\n OrsaModel::refineUntilConvergence(...)\n" << std::endl;
  const int nData = x1_.ncol();
  std::vector<ErrorIndex> vec_residuals(nData); // [residual,index]

  bool bContinue = true;
  int iter = 0;
  do{
    std::vector<Model> vec_models; // Up to max_models solutions
    Fit(vec_inliers, &vec_models);

    // Evaluate models
    for (size_t k = 0; k < vec_models.size(); ++k)
    {
      // Residuals computation and ordering
      for (int i = 0; i < nData; ++i)
      {
        double error = Error(vec_models[k], i);
        vec_residuals[i] = ErrorIndex(error, i);
      }
      std::sort(vec_residuals.begin(), vec_residuals.end());

      // Most meaningful discrimination inliers/outliers
      ErrorIndex best = bestNFA(vec_residuals, loge0, maxThreshold,
                                vec_logc_n, vec_logc_k);

      if(best.error < 0 && best.error < minNFA) // A better model was found
      {
        minNFA = best.error;
        side = best.side;
        vec_inliers.resize(best.index);
        for (int i=0; i<best.index; ++i)
          vec_inliers[i] = vec_residuals[i].index;
        errorMax = vec_residuals[best.index-1].error; // Error threshold
        if(model) *model = vec_models[k];

        if(bVerbose)
        {
          std::cout << "  nfa=" << minNFA
            << " inliers=" << vec_inliers.size()
            << " precision=" << denormalizeError(errorMax, side)
            << " (iter=" << iter << ")\n";
        }
      }
      else
        bContinue = false;
    }
    if (vec_models.empty())
    {
      bContinue = false;
    }
    ++iter;
  }
  while( bContinue );
}

/// Toggle iterative refinement NFA/RMSE.
void OrsaModel::setRefineUntilConvergence(bool value)
{
  bConvergence = value;
}

/// Iterative refinement NFA/RMSE.
bool OrsaModel::getRefineUntilConvergence() const
{
  return bConvergence;
}

} // namespace orsa
