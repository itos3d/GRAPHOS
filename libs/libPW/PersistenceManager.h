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
#ifndef PERSISTENCEMANAGER_H
#define PERSISTENCEMANAGER_H

#define PERSISTENCEMANAGER_ERROR        1
#define PERSISTENCEMANAGER_NO_ERROR     0

#define PERSISTENCEMANAGER_MAX_INSERTS_IN_UNION 500

#include <QObject>
#include <QtSql>
#include <QMap>

#include "Project.h"
#include "Camera.h"

namespace PW{

class LIBPWSHARED_EXPORT PersistenceManager : public QObject
{
    Q_OBJECT
public:
    explicit PersistenceManager(QString dbURL, QObject *parent = 0);

    bool openDatasource();
    int vacuum();
    int updateDBVersion(QString from, QString to);
    int openAuxDatasource();
    int closeDatasource();
    QSqlDatabase *getDataBase();

    int writeMatches(Project *project,
                     QString& metadata,
                     QString& description,
                     QString& timeCalculation,
                     QString& matchesPath);

    int writeMatches_20140821(Project *project,
                              QString& metadata,
                              QString& description,
                              QString& timeCalculation,
                              QString& matchesPath);
    int writeMatches(Project *project,
                     QString metadata,
                     QString description,
                     QString timeCalculation,
                     QMap<QString, QVector<QString> > imagesIdsTiePoints,
                     QMap<QString, QMap<QString, QVector<double> > > imagesFirstColumnsTiePoints,
                     QMap<QString, QMap<QString, QVector<double> > > imagesFirstRowsTiePoints,
                     QMap<QString, QMap<QString, QVector<double> > > imagesSecondColumnsTiePoints,
                     QMap<QString, QMap<QString, QVector<double> > > imagesSecondRowsTiePoints);

    bool copyMatches(int projectId,
                     QMap<QString, QVector<QString> > imagesIdsTiePoints,
                     QMap<QString, QMap<QString,QVector<float> > > imagesFirstColumnsTiePoints,
                     QMap<QString, QMap<QString,QVector<float> > > imagesFirstRowsTiePoints,
                     QMap<QString, QMap<QString,QVector<float> > > imagesSecondColumnsTiePoints,
                     QMap<QString, QMap<QString,QVector<float> > > imagesSecondRowsTiePoints,
                     Project *destinationProject);
    int writeMatchesCategory(PWMatchesCategory *category, int &categoryId);
    int writeMatchesCategories(Project *project);

    int writeProject(Project * project, bool writeCams=false, bool writeMatchesData=false, int previousProyectID=0);
    int updateProject(Project * project);
    int writeCamera(Camera * camera);

    Project * readProject(QString projectName = "");
    QList<Project> readProjectsDescriptors();
    bool readCategories(Project *project);
    Camera * readCamera(QString cameraName, QString lens);
    Camera * readCamera(QString cameraName);
    Camera * readCameraByLens(QString LensName);
    QList<Camera *> readCameras(QString cameraName, QString lens);

    int deleteProject(QString projectName);

    // DHL_20140405
    int enableSpatialite();
    int getMatchesCategories(int projectId,
                             QVector<int>& idMatchesCategories,
                             QStringList& metadataMatchesCategories,
                             QStringList& descriptionMatchesCategories,
                             QStringList& timeCalculationCategories);
    QMap<QString,QVector<QString> > imagesIdsTiePoints;
    QMap<QString,QVector<QVector<double> > > imagesColumnsTiePoints;
    QMap<QString,QVector<QVector<double> > > imagesRowsTiePoints;
    bool getMatchesOLD(int projectId,
                    QStringList descriptionMatchesCategories,
                    QMap<QString,int>& imagesIds,
                    QMap<QString,QVector<QString> >& imagesIdsTiePoints,
                    QMap<QString,QMap<QString,QVector<float> > >& imagesFirstColumnsTiePoints,
                    QMap<QString,QMap<QString,QVector<float> > >& imagesFirstRowsTiePoints,
                    QMap<QString,QMap<QString,QVector<float> > >& imagesSecondColumnsTiePoints,
                    QMap<QString,QMap<QString,QVector<float> > >& imagesSecondRowsTiePoints,
                    QMap<QString,QMap<QString,QVector<int> > >& matchesIds);
    bool getMatchesNEW(int projectId,
                    QStringList descriptionMatchesCategories,
                    QMap<QString,int>& imagesIds,
                    QMap<QString,QVector<QString> >& imagesIdsTiePoints,
                    QMap<QString,QMap<QString,QVector<float> > >& imagesFirstColumnsTiePoints,
                    QMap<QString,QMap<QString,QVector<float> > >& imagesFirstRowsTiePoints,
                    QMap<QString,QMap<QString,QVector<float> > >& imagesSecondColumnsTiePoints,
                    QMap<QString,QMap<QString,QVector<float> > >& imagesSecondRowsTiePoints,
                    QMap<QString,QMap<QString,QVector<int> > >& matchesIds);
    bool getMatches(int projectId,
                    QStringList descriptionMatchesCategories,
                    QMap<QString,int>& imagesIds,
                    QMap<QString,QVector<QString> >& imagesIdsTiePoints,
                    QMap<QString, QMap<QString, QVector<double> > > &imagesFirstColumnsTiePoints,
                    QMap<QString, QMap<QString, QVector<double> > > &imagesFirstRowsTiePoints,
                    QMap<QString, QMap<QString, QVector<double> > > &imagesSecondColumnsTiePoints,
                    QMap<QString, QMap<QString, QVector<double> > > &imagesSecondRowsTiePoints,
                    QMap<QString,QMap<QString,QVector<int> > >& matchesIds);
    bool getMatches_20140821(int projectId,
                    QStringList descriptionMatchesCategories,
                    QMap<QString,int>& activeImagesIds,
                    QMap<QString,QVector<QString> >& imagesIdsTiePoints,
                    QMap<QString,QMap<QString,QVector<float> > >& imagesFirstColumnsTiePoints,
                    QMap<QString,QMap<QString,QVector<float> > >& imagesFirstRowsTiePoints,
                    QMap<QString,QMap<QString,QVector<float> > >& imagesSecondColumnsTiePoints,
                    QMap<QString,QMap<QString,QVector<float> > >& imagesSecondRowsTiePoints,
                    QMap<QString,QMap<QString,QVector<int> > >& matchesIds);
    bool getMatches(int projectId,
                    QStringList descriptionMatchesCategories,
                    QMap<QString,QVector<QString> >& imagesIdsTiePoints,
                    QMap<QString, QMap<QString, QVector<double> > > &imagesFirstColumnsTiePoints,
                    QMap<QString, QMap<QString, QVector<double> > > &imagesFirstRowsTiePoints,
                    QMap<QString, QMap<QString, QVector<double> > > &imagesSecondColumnsTiePoints,
                    QMap<QString, QMap<QString, QVector<double> > > &imagesSecondRowsTiePoints);
    // DHL_20140405
    bool getMatchingPoints(int projectId,
                           QStringList descriptionMatchesCategories,
                           int imageFirstID,
                           int imageSecondID,
                           QList<QVector<float>>& matching_coords);
    bool getMatchingPoints_20140821(int projectId,
                                    QStringList descriptionMatchesCategories,
                                    int imageFirstID,
                                    int imageSecondID,
                                    QList<QVector<float>>& matching_coords);

    bool getMatchesCategoriesImagePairs(int idProject,
                                        QVector<int> idMatchesCategories,
                                        bool twoWay,
                                        QMap<QString,QVector<QString> >& imagesIdsPairs);
    bool getMatches_20140821(int projectId,
                    QStringList descriptionMatchesCategories,
                    QMap<QString,QVector<QString> >& imagesIdsPairs);

    bool setMatchesCategories(Project* project);

    bool deleteMatches(QList<int> imagesIdList);

    bool writeMatchesAccuracies(QMap<QString, QMap<QString, QVector<double> > > &orientationImagesFirstColumnsTiePoints,
                                QMap<QString, QMap<QString, QVector<double> > > &orientationImagesFirstRowsTiePoints,
                                QMap<QString, QMap<QString, QVector<double> > > &orientationImagesSecondColumnsTiePoints,
                                QMap<QString, QMap<QString, QVector<double> > > &orientationImagesSecondRowsTiePoints,
                                QMap<QString, QMap<QString, QVector<int> > > &orientationMatchesIds,
                                QMap<QString, QMap<QString, QVector<double> > >& orientationMatchesAccuracies);

private:
    QList<PW::PWImage *> * getImages(Project *project, int dbProjectID, QString basePath);
    QList<PW2dPoint *> *getImagePoints(int dbImageID);
    ExteriorOrientation * getExternalOrientation(int imageID);
    PhotogrammetricModel * getCameraModel(int activeCameraModelID);
    QPolygon getMask(int imageID);
    QList<PW3dPoint *> *getTerrainPoints(int projectID);


signals:
    void operationFinished();

public slots:

private:
    QString                 mDBURL;
    QSqlDatabase            mDB;

};
}
#endif // PERSISTENCEMANAGER_H
