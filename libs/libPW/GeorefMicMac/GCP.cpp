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
#include "GCP.h"
using namespace PW;
GCP::GCP()
{

}
GCP::GCP(int id, double x, double y,double z,QString desc):ID(id),X(x),Y(y),Z(z),mDesc(desc){}

void GCP::setId(int id){
    ID=id;
}
void GCP::setX(double x){
    X=x;
}
void GCP::setY(double y){
    Y=y;
}
void GCP::setZ(double z){
    Z=z;
}
void GCP::setDesc(QString desc){
    mDesc=desc;
}
int GCP::getID(){
    return ID;
}
double GCP::getX(){
    return X;
}
double GCP::getY(){
    return Y;
}
double GCP::getZ(){
    return Z;
}
QString GCP::getDesc(){
    return mDesc;
}
GCP::~GCP()
{

}

