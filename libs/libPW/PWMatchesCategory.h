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
#ifndef PWMATCHESCATEGORY_H
#define PWMATCHESCATEGORY_H

#include "libPW.h"
#include "Project.h"

namespace PW{

class LIBPWSHARED_EXPORT PWMatchesCategory
{
public:
    PWMatchesCategory(Project* project,
                      int id,
                      QString description,
                      QString metadata,
                      QString timeCalculation);

    int getId();
    QString getDescription();
    PWGraphImages* getGraphImages();
    void getImagePairs(QMap<QString, QVector<QString> >& imagesPairs);
    int getImagePairsCount();
    QString getMetadata();
    QString getTimeCalculation();
    void getInvalidMatchedCategoryExplanation(QString &title,
                                              QStringList &subgraphs);
    Project * getProject();
    bool isValid();
    void setImagePairs(QMap<QString, QVector<QString> >& imagesPairs);
    void setGraphImages(PWGraphImages* graphImages);
    void removeImagePairs(QString imageName);
private:
    Project* mProject;
    QString mTimeCalculation;
    PWGraphImages* mGraphImages;
    QMap<QString, QVector<QString> >  mImagesPairs;
    QString mDescription;
    QString mMetadata;
    int mId;
};

}

#endif // PWMATCHESCATEGORY_H
