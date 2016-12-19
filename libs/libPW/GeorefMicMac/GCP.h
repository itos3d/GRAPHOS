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
#ifndef GCP_H
#define GCP_H
#include "libPW_global.h"
#include <QtCore>
namespace PW{
class LIBPWSHARED_EXPORT GCP
{
public:
    GCP();
    GCP(int id, double x, double y,double z, QString desc);

    void setId(int id);
    void setX(double x);
    void setY(double y);
    void setZ(double z);
    void setDesc(QString desc);
    int getID();
    double getX();
    double getY();
    double getZ();
    QString getDesc();
    ~GCP();
private:
    int ID;
    double X,Y,Z;
    QString mDesc;
};
}
#endif // GCP_H
