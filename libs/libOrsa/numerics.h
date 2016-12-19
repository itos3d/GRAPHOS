/**
 * @file numerics.h
 * @brief Linear algebra: system solving by LU decomposition and SVD
 * @author Pascal Monasse
 * 
 * Copyright (c) 2010-2012 Pascal Monasse
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

#ifndef NUMERICS_H
#define NUMERICS_H

#include "matrix.h"

namespace libNumerics {
    typedef double flnum;

    /// Solve system AX = B.
    bool solveLU(const matrix<flnum>& A, const vector<flnum>& B,
                 vector<flnum>& X);
    bool solveLU(matrix<flnum> A, vector<flnum>& B);

    /// Singular Value Decomposition: U diag(D) V, U in O(m), V in O(n), D>=0.
    class SVD {
    public:
        SVD(const matrix<flnum>& A);
        matrix<flnum> compose() const;
        flnum sv(int i) const;

        matrix<flnum> U, V;
        vector<flnum> D;

        typedef matrix<flnum> Mat;
        typedef vector<flnum> Vec;
        // Static functions related to SVD
        static bool Nullspace(const Mat& A, Vec* nullspace,
                              double ratioExtremes=1e-2, double ratio2Min=.5);
        static flnum InvCond(const Mat& A);
        static void EnforceRank2_3x3(const Mat& A, Mat* ARank);
        static void Nullspace2_Remap33(const Mat& A, Mat& f1, Mat& f2);
    private:
        void sort();
    };

} // namespace libNumerics

#endif
