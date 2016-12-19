#ifndef SQLITEDSMANAGER_H
#define SQLITEDSMANAGER_H

#include <QSqlDatabase>
#include <QMap>

#include "dsmanager.h"

namespace QParams{


/*!
 \brief Datasource Manager using SQLite.

*/
class SQLiteDSManager : public DSManager
{
public:
    SQLiteDSManager(QString dsUrl);

    /*!
     \brief Open the Data Source.

     \return int 0 if can open, 1 otherwise.
    */
    virtual int openDatasource();

    /*!
     \brief Update data base version.
     \param from Current version
     \param to New version
     \return int 0 if ok, 1 otherwise.
    */
    virtual int updateDBVersion(QString from, QString to);

    /*!
     \brief Get a param from datasource.

     \param code Code of the param
     \return Param *
    */
    virtual Param *getParam(QString code);

    /*!
     \brief Get a param from datasource.

     \param name Name of the param
     \return Param *
    */
    virtual Param *getParamByName(QString name);

    /*!
     \brief Get a discrete param from datasource.

     \param code Code of the param
     \return Param *
    */
//    virtual DiscreteParam * getDiscreteParam(QString code);

    /*!
     \brief Get a unit from datasource.

     \param code Code of the unit.
     \return Param *
    */
    virtual Unit * getUnit(QString code);

    /*!
     \brief Get a unit Transformation from datasource.

     \param sourceUnit Source unit.
     \param TargetUnit Target Unit
     \return Transformation * The Transformation.
    */
    virtual Transformation * getTransformation(Unit *sourceUnit, Unit *TargetUnit);


    /*!
     \brief Get the code for the transformation between two units.

     \param sourceUnit Source unit.
     \param TargetUnit Target Unit.
     \return QString The code (Empty if transformation does not exist).
    */
    virtual QString getTransformationCode(Unit *sourceUnit, Unit *TargetUnit);

    /*!
     \brief Get a Category from datasource.

     \param code Code of the Category.
     \return Category *
    */
    virtual Category * getCategory(QString code);

    /*!
     \brief Get a Domain from datasource.

     \param code Code of the Domain.
     \return Domain *
    */
    virtual Domain * getDomain(QString code);

    /*!
     \brief Get a App from datasource.

     \param code Code of the App.
     \return App *
    */
    virtual App *getApp(QString code);

private:
    QString                 mDBURL;
    QSqlDatabase            mDB;
};

}
#endif // SQLITEDSMANAGER_H
