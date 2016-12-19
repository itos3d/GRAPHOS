#ifndef QPARAMS_H
#define QPARAMS_H

#include <QMap>

#include "dsmanager.h"
#include "param.h"
#include "transformation.h"
#include "domain.h"
#include "app.h"

namespace QParams{

/*!
 \brief Library main manager.

*/
class QParamsManager {

public:
/*!
 \brief Constructor

*/
    QParamsManager();

    //static DSManager * getDSManager();
    /*!
     \brief Init the Data Source manager

     \param dsUrl Dasta Source url. i.e.: The path of the database file.
     \return int 0 if can connect, 1 otherwise
    */
    static int initDSManager(QString dsUrl);

    /*!
     \brief Update data base version.
     \param from Current version
     \param to New version
     \return int 0 if ok, 1 otherwise.
    */
    static int updateDBVersion(QString from, QString to);

    /*!
     \brief Get the parameter with the given code.

     \param paramCode The code of the parameter
     \return Param The parameter or NULL if the parameter (or the inverse) does not exist.
    */
    static Param *getParam(QString code);
    /*!
     \brief Get the parameter with the given name.

     \param name The code of the parameter
     \return Param The parameter or NULL if the parameter (or the inverse) does not exist.
    */
    static Param *getParamByName(QString name);
    /*!
     \brief Get the transformation with de given code.

     \param transformationCode The code of the transformation
     \return Trasformation The transformation or NULL if the transformation (or the inverse) does not exist.
    */
    static Transformation * getTransformation(Unit *sourceUnit, Unit *TargetUnit);
    /*!
     \brief Get the unit with de given code.

     \param code The code of the unit
     \return Unit The unit or NULL if the unit does not exist.
    */
    static Unit *getUnit(QString code);

    /*!
     \brief Gets the Category with de given code.

     \param code The code of the Category
     \return Category The Category or NULL if the Category does not exist.
    */
    static Category *getCategory(QString code);    

    /*!
     \brief Gets the Domain with de given code.

     \param code The code of de Domain
     \return Domain * The Domain or NULL if the Category does not exist.
    */
    static Domain *getDomain(QString code);

    /*!
     \brief Gets the App with de given code.

     \param code The code of de App
     \return Domain * The App or NULL if the App does not exist.
    */
    static App * getApp(QString code);

private:

    static DSManager *                       mDSManager;
    static QMap<QString, Param*>   mParamsPool;
    static QMap<QString, Param*>   mParamsPoolByName;
    static QMap<QString, Unit*>              mUnitsPool;
    static QMap<QString, Transformation*>    mTransformationsPool;
    static QMap<QString, Category*>          mCategoriesPool;
    static QMap<QString, Domain*>            mDomainsPool;
    static QMap<QString, App*>               mAppsPool;
};


}

#endif // QPARAMS_H
