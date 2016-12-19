#include "qparams.h"
#include "sqlitedsmanager.h"

using namespace QParams;

DSManager *QParamsManager::mDSManager;
QMap<QString, Param*> QParamsManager::mParamsPool;
QMap<QString, Unit*> QParamsManager::mUnitsPool;
QMap<QString, Transformation*> QParamsManager::mTransformationsPool;
QMap<QString, Category*> QParamsManager::mCategoriesPool;
QMap<QString, Domain*> QParamsManager::mDomainsPool;
QMap<QString, App*> QParamsManager::mAppsPool;
QMap<QString, Param*> QParamsManager::mParamsPoolByName;

QParamsManager::QParamsManager()
{

}

int QParamsManager::initDSManager(QString dsUrl)
{
    //    if (mDSManager == NULL) /*TODO*/
    mDSManager = new SQLiteDSManager(dsUrl);

    return  mDSManager->openDatasource();
}

int QParamsManager::updateDBVersion(QString from, QString to)
{
    if(mDSManager)
        return mDSManager->updateDBVersion(from, to);
    return 1;
}

Param *QParamsManager::getParam(QString code)
{
//    Param * param = NULL;
//    if(mParamsPool.contains(code))
//        param = mParamsPool.value(code);
//    else{
//        param = mDSManager->getParam(code);
//        mParamsPool.insert(code, param);
//    }

    Param *param = mDSManager->getParam(code);
    return param;
}

Param *QParamsManager::getParamByName(QString name)
{
//    Param * param = NULL;
//    if(mParamsPoolByName.contains(name))
//        param = mParamsPoolByName.value(name);
//    else{
//        param = mDSManager->getParamByName(name);
//        mParamsPoolByName.insert(name, param);
//    }

    Param *param = mDSManager->getParamByName(name);
    return param;
}

Unit * QParamsManager::getUnit(QString code)
{
    Unit *unit = NULL;
    if(mUnitsPool.contains(code))
            unit =  mUnitsPool.value(code);
    else {
        unit = mDSManager->getUnit(code);
        mUnitsPool.insert(code, unit);
    }
    return unit;
}

Transformation * QParams::QParamsManager::getTransformation(Unit *sourceUnit, Unit *TargetUnit)
{
    Transformation *transformation = NULL;
    QString code = mDSManager->getTransformationCode(sourceUnit, TargetUnit);
    if (!code.isEmpty()){
        if (mTransformationsPool.contains(code))
            transformation = mTransformationsPool.value(code);
        else{
            transformation = mDSManager->getTransformation(sourceUnit, TargetUnit);
            mTransformationsPool.insert(transformation->getCode(), transformation);
        }
    }else{
        code = mDSManager->getTransformationCode(TargetUnit, sourceUnit);
        if (!code.isEmpty()){
            if (mTransformationsPool.contains(code)){
                transformation = mTransformationsPool.value(code);
                transformation->setInverted(true);
            }else{
                transformation = mDSManager->getTransformation(TargetUnit, sourceUnit);
                mTransformationsPool.insert(transformation->getCode(), transformation);
                transformation->setInverted(true);
            }
        }
    }

    return transformation;
}

Category * QParams::QParamsManager::getCategory(QString code)
{
    Category *category = NULL;
    if(mCategoriesPool.contains(code))
            category =  mCategoriesPool.value(code);
    else {
        category = mDSManager->getCategory(code);
        mCategoriesPool.insert(code, category);
    }
    return category;
}

Domain * QParams::QParamsManager::getDomain(QString code)
{
    Domain *domain = NULL;
    if(mDomainsPool.contains(code))
            domain =  mDomainsPool.value(code);
    else {
        domain = mDSManager->getDomain(code);
        mDomainsPool.insert(code, domain);
    }
    return domain;
}

App * QParams::QParamsManager::getApp(QString code)
{
    App *app = NULL;
    if(mAppsPool.contains(code))
            app =  mAppsPool.value(code);
    else {
        app = mDSManager->getApp(code);
        mAppsPool.insert(code, app);
    }
    return app;
}
