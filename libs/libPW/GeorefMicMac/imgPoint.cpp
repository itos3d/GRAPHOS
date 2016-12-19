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
#include "imgPoint.h"
using namespace PW;
imgPoint::imgPoint()
{

}
imgPoint::imgPoint(int id, double x, double y,QString desc):ID(id),X(x),Y(y),mDesc(desc){}

void imgPoint::setId(int id){
    ID=id;
}
void imgPoint::setX(double x){
    X=x;
}
void imgPoint::setY(double y){
    Y=y;
}
void imgPoint::setDesc(QString desc){
    mDesc=desc;
}
int imgPoint::getID(){
    return ID;
}
double imgPoint::getX(){
    return X;
}
double imgPoint::getY(){
    return Y;
}
QString imgPoint::getDesc(){
    return mDesc;
}
imgPoint::~imgPoint()
{

}

