#include <vector>
#include <string>
#include <fstream>
#include <stdio.h>
#include <iostream>

#include <QObject>

#include "match.h"
#include "numerics.h"
#include "orsa_model.hpp"
#include "homography_model.hpp"
#include "libOrsa.h"

using namespace std;

/// Number of random samples in ORSA
static const int ITER_ORSA=10000;

LibOrsa::LibOrsa()
{
}

bool LibOrsa::getInliers(int w1,
                         int h1,
                         int w2,
                         int h2,
                         double precision,
                         std::vector<double>& x1s,
                         std::vector<double>& y1s,
                         std::vector<double>& x2s,
                         std::vector<double>& y2s,
                         std::vector<int>& vec_inliers,
                         QString& strError)
{
    if(x1s.size()!=y1s.size()||x1s.size()!=x2s.size()||x2s.size()!=y2s.size())
    {
        strError+=QObject::tr("Error: dimensions in point vectors are different");
        return false;
    }
    std::vector<Match> vec_matchings;
    for(int i=0;i<x1s.size();i++)
    {
        double x1=x1s.at(i);
        double y1=y1s.at(i);
        double x2=x2s.at(i);
        double y2=y2s.at(i);
        Match match(x1,y1,x2,y2);
        vec_matchings.push_back(match);
    }
    const int n = static_cast<int>( vec_matchings.size() );
    if(n < 5)
    {
        strError+=QObject::tr("Error: ORSA needs 5 matches or more to proceed");
        return false;
    }
    const int ww1=w1;
    const int ww2=w2;
    const int hh1=h1;
    const int hh2=h2;
    libNumerics::matrix<double> H(3,3);
    vec_inliers.clear();
    libNumerics::matrix<double> xA(2,n), xB(2,n);
    for (int i=0; i < n; ++i)
    {
        xA(0,i) = vec_matchings[i].x1;
        xA(1,i) = vec_matchings[i].y1;
        xB(0,i) = vec_matchings[i].x2;
        xB(1,i) = vec_matchings[i].y2;
    }
    orsa::HomographyModel model(xA, w1, h1, xB, w2, h2, true);
    //model.setConvergenceCheck(true);
    bool verbose=false;
    if(model.orsa(vec_inliers, ITER_ORSA, &precision, &H, verbose)>0.0)
    {
        strError+=QObject::tr("Error: ORSA calling model.orsa");
        return false;
    }
    //std::cout << "Before refinement: ";
    //display_stats(vec_matchings, vec_inliers, H);
    if(!model.ComputeModel(vec_inliers,&H) ) // Re-estimate with all inliers
    {
        strError+=QObject::tr("Warning: error in refinement, result is suspect");
        //std::cout << "After  refinement: ";
        //display_stats(vec_matchings, vec_inliers, H);
    }
//    std::vector<Match> good_match;
//    std::vector<int>::const_iterator it = vec_inliers.begin();
//    for(; it != vec_inliers.end(); it++)
//    {
//        Match goodMatch=vec_matchings[*it];
//        good_match.push_back(goodMatch);
//    }
    return(true);
}
