#include <vector>
#include <string>
#include <fstream>
#include <stdio.h>
#include <iostream>

#include <QObject>

#include "libMatch/match.h"
#include "orsa.h"

#include "LibOrsaAsift.h"

using namespace std;

libOrsaAsift::libOrsaAsift()
{
}

bool libOrsaAsift::getInliers(int w1,
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
    int Tmin = 8;
    float nfa_max = -2;
    if(x1s.size()!=y1s.size()||x1s.size()!=x2s.size()||x2s.size()!=y2s.size())
    {
        strError+=QObject::tr("Error: dimensions in point vectors are different");
        return false;
    }
    vector<Match> match_coor;
    for(int i=0;i<x1s.size();i++)
    {
        double x1=x1s.at(i);
        double y1=y1s.at(i);
        double x2=x2s.at(i);
        double y2=y2s.at(i);
        Match match1_coor;
        match1_coor.x1 = x1;
        match1_coor.y1 = y1;
        match1_coor.x2 = x2;
        match1_coor.y2 = y2;

        match_coor.push_back(match1_coor);
    }

    const int n = static_cast<int>( match_coor.size() );
    if(n < Tmin)
    {
        strError+=QObject::tr("Error: ORSA-Asift needs %1 matches or more to proceed").arg(QString::number(Tmin));
        return false;
    }
    std::vector<float> index;
    // Guoshen Yu, 2010.09.23
    // index.clear();

    int t_value_orsa=10000;
    int verb_value_orsa=0;
    int n_flag_value_orsa=0;
    int mode_value_orsa=2;
    int stop_value_orsa=0;
    float nfa = orsa((w1+w2)/2, (h1+h2)/2, match_coor, index, t_value_orsa, verb_value_orsa, n_flag_value_orsa, mode_value_orsa, stop_value_orsa);
    if ( nfa < nfa_max )
    {
        // extract meaningful matches
        for ( int cc = 0; cc < (int) index.size(); cc++ )
        {
            vec_inliers.push_back((int)index[cc]);
        }
    }
    return(true);
}
