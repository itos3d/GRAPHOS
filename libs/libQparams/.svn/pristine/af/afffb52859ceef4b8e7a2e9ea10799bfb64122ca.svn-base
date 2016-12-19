#ifndef DSMANAGER_H
#define DSMANAGER_H

#include <QString>

#include "param.h"
#include "transformation.h"
#include "domain.h"
#include "app.h"

namespace QParams{

/*!
 \brief Datasource Manager.

*/
class DSManager
{
public:

    /*!
 \brief Constructor.

 \param dsUrl Data Source URL.
*/
    DSManager(QString dsUrl);


    /*!
     \brief Open the Data Source.

     \return int 0 if can open, 1 otherwise.
    */
    virtual int openDatasource() = 0;

    /*!
     \brief Update data base version.
     \param from Current version
     \param to New version
     \return int 0 if ok, 1 otherwise.
    */
    virtual int updateDBVersion(QString from, QString to) = 0;


    /*!
     \brief Get a param from datasource.

     \param code Code of the param
     \return Param *
    */
    virtual Param * getParam(QString code) = 0;

    /*!
     \brief Get a param from datasource.

     \param name Name of the param
     \return Param *
    */
    virtual Param * getParamByName(QString name) = 0;

    /*!
     \brief Get a discrete param from datasource.

     \param code Code of the param
     \return Param *
    */
//    virtual DiscreteParam *getDiscreteParam(QString code) = 0;

    /*!
     \brief Get a unit from datasource.

     \param code Code of the unit.
     \return Unit *
    */
    virtual Unit * getUnit(QString code) = 0;

    /*!
     \brief Get a unit Transformation from datasource.

     \param sourceUnit Source unit.
     \param TargetUnit Target Unit
     \return Transformation * The Transformation.
    */
    virtual Transformation * getTransformation(Unit *sourceUnit, Unit *TargetUnit) = 0;


    /*!
     \brief Get the code for the transformation between two units.

     \param sourceUnit Source unit.
     \param TargetUnit Target Unit.
     \return QString The code (Empty if transformation does not exist).
    */
    virtual QString getTransformationCode(Unit *sourceUnit, Unit *TargetUnit) = 0;

    /*!
     \brief Get a Category from datasource.

     \param code Code of the Category.
     \return Category *
    */
    virtual Category * getCategory(QString code) = 0;

    /*!
     \brief Get a Domain from datasource.

     \param code Code of the Domain.
     \return Domain *
    */
    virtual Domain *getDomain(QString code) = 0;

    /*!
     \brief Get a App from datasource.

     \param code Code of the App.
     \return App *
    */
    virtual App *getApp(QString code) = 0;

};
}

#endif // DSMANAGER_H
