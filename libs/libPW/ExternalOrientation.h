/**
*-------------------------------------------------
*  Copyright 2016 by Tidop Research Group <daguilera@usal.se>
*
* This file is part of GRAPHOS - inteGRAted PHOtogrammetric Suite.
*
* GRAPHOS - inteGRAted PHOtogrammetric Suite is free software: you can redistribute
* it and/or modify it under the terms of the GNU General Public
* License as published by the Free Software Foundation, either
* version 3 of the License, or (at your option) any later version.
*
* GRAPHOS - inteGRAted PHOtogrammetric Suite is distributed in the hope that it will
* be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*
* @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>
*-------------------------------------------------
*/
#ifndef EXTERNALORIENTATION_H
#define EXTERNALORIENTATION_H

#include "libPW_global.h"
#include <QVector>

namespace PW{

/*!
 \brief Class representing external orientation of a camera

*/
class LIBPWSHARED_EXPORT ExteriorOrientation
{
public:


/*!
 \brief

*/
    ExteriorOrientation();


/*!
 \brief Constructor

 \param cp center of projection vector
 \param r Rotation matrix
*/
    ExteriorOrientation(QVector<double> cp, QVector< QVector<double> > r);

    /*!
     \brief Sets the center of projection vector.

     \param QVector<double> Center of projection
    */
    void setCP(QVector<double> cp);
    /*!
     \brief Sets the rotation Matrix

     \param QMatrix Rotation matrix
    */
    void setR(QVector< QVector<double> > r);

    /*!
     \brief Gets the center of projection vector.

     \return QVector<double>
    */
    QVector<double> *getCP();
    /*!
     \brief Gets the rotation Matrix

     \return QMatrix
    */
    QVector< QVector<double> > *getR();

private:

    QVector<double> mCP; //Center of rojection
    QVector< QVector<double> > mR;  // Rotation Matrix.
};

}

#endif // EXTERNALORIENTATION_H
