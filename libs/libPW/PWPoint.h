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
#ifndef PWPOINT_H
#define PWPOINT_H

#include "libPW_global.h"
#include <QObject>
#include <QList>

namespace PW{


/*!
 \brief Base Class representing a generic point.

*/
class LIBPWSHARED_EXPORT PWPoint
{

public:

    /*!
     \brief

    */
    enum PointType {
        Control = 0x0000,
        Check = 0x0001
    };

    /*!
     \brief

    */
    PWPoint(PointType type, QString name = "");
    /*!
     \brief Gets the type of point

     \return PointType
    */
    virtual PointType getType();
    /*!
     \brief Gets de number of components or dimensions of the point

     \return int
    */
    virtual int getCoordsCount() = 0;
    /*!
     \brief Gets the value of a component or coordinate.

     \param index
     \return double
    */
    virtual double getCoord(int index) = 0;

    /*!
     \brief Gets a list of associated points (i.e.: Image points associated with a ground control point)

     \return QList<PWPoint *>
    */
    virtual QList<PWPoint *> getAssociatedPoints();

    /*!
     \brief Gets the name of the point.

     \return QString
    */
    virtual QString getName();

    /*!
     \brief Sets the name of the point

     \param name
    */
    virtual void setName(QString name);

    /*!
     \brief Sets the value of a component or coordinate.

     \param index
    */
    virtual void setCoord(int index, double value) = 0;

protected:
    QList<PWPoint *> mAssociatedPoints; /*!< list of associated points, i.e.: Image points associated with a ground control point*/
    PointType mType;
    QString mName;
};

}
#endif // PWPOINT_H
