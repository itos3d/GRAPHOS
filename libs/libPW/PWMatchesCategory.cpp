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
#include "PWMatchesCategory.h"

using namespace PW;


PWMatchesCategory::PWMatchesCategory(Project *project,
                                     int id,
                                     QString description,
                                     QString metadata,
                                     QString timeCalculation):
    mProject(project),
    mId(id),
    mDescription(description),
    mMetadata(metadata),
    mTimeCalculation(timeCalculation)
{
    mGraphImages=NULL;
}

int PWMatchesCategory::getId()
{
    return mId;
}

QString PWMatchesCategory::getDescription()
{
    return(mDescription);
}

PWGraphImages *PWMatchesCategory::getGraphImages()
{
    return(mGraphImages);
}

void PWMatchesCategory::getImagePairs(QMap<QString, QVector<QString> > &imagesPairs)
{
    imagesPairs.clear();
    imagesPairs=mImagesPairs;
}

int PWMatchesCategory::getImagePairsCount(){
    return mImagesPairs.count();
}

QString PWMatchesCategory::getMetadata()
{
    return(mMetadata);
}

QString PWMatchesCategory::getTimeCalculation()
{
    return(mTimeCalculation);
}

void PWMatchesCategory::getInvalidMatchedCategoryExplanation(QString &title, QStringList &subgraphs)
{
    if(mGraphImages!=NULL)
        mGraphImages->getInvalidMatchedCategoryExplanation(title,subgraphs);
}

Project *PWMatchesCategory::getProject()
{
    return mProject;
}

bool PWMatchesCategory::isValid()
{
    bool isValid=false;
    if(mGraphImages!=NULL)
        isValid=mGraphImages->isValid();
    return(isValid);
}

void PWMatchesCategory::setImagePairs(QMap<QString, QVector<QString> > &imagesPairs)
{
    mImagesPairs=imagesPairs;
}

void PWMatchesCategory::setGraphImages(PWGraphImages *graphImages)
{
    mGraphImages=graphImages;
}

void PWMatchesCategory::removeImagePairs(QString imageName)
{
    foreach(QString key, mImagesPairs.keys()){
        if (key == imageName)
            mImagesPairs.remove(key);
        else{
            QVector<QString> imageNames = mImagesPairs.value(key);
            QVector<QString> newImagesNames;
            newImagesNames.clear();
            for (int i=0; i< imageNames.count();i++)
                if(imageNames[i] != imageName)
                    newImagesNames.append(imageNames[i]);
            if (newImagesNames.count() == 0)
                mImagesPairs.remove(key);
            else
                mImagesPairs.insert(key, newImagesNames);
        }
    }
}
