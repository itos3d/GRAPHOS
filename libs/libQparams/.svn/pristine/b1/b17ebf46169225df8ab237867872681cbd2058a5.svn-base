#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlResult>
#include <QVariant>
#include <QDebug>
#include <QStringList>
#include <limits>

#include "qparams.h"
#include "sqlitedsmanager.h"
#include "domain.h"


using namespace QParams;

SQLiteDSManager::SQLiteDSManager(QString dsUrl):
    DSManager(dsUrl),
    mDBURL(dsUrl)
{

}

int SQLiteDSManager::openDatasource()
{
    mDB = QSqlDatabase::addDatabase("QSQLITE","QPARAMS_DATA");
    mDB.setDatabaseName(mDBURL);
    if(mDB.open()){

        return 0;
    }qCritical() << mDB.lastError();

    return 1;
}

int SQLiteDSManager::updateDBVersion(QString from, QString to)
{
    if(to == "1.4" && from.toDouble() < 1.4){
        //Add precision field to qparams data base
        QSqlQuery query(mDB);

        QString queryString = "ALTER TABLE qp_params ADD precision INTEGER DEFAULT 0";
        if(query.prepare(queryString)){
            query.exec();
            mDB.commit();
        }
        else{
            qCritical() << mDB.lastError();
            return 1;
        }
    }
}

Param * SQLiteDSManager::getParam(QString code)
{
    QSqlQuery query(mDB);
    QSqlQuery queryAux(mDB);

    Param *param = NULL;
    ContinuousParam *continuousParam = NULL;
    DiscreteParam *discreteParam = NULL;
    if(query.prepare("SELECT * FROM qp_params WHERE name='"+code+"'")){
        query.exec();
        if(query.next()){
            int paramID = query.record().value("id").toInt();
            QString paramCode = query.record().value("code").toString();

            QString paramName = query.record().value("name").toString();
            QString paramDescription= query.record().value("description").toString();
            QString defaultValue = query.record().value("default_value").toString();
            int categoryID = query.record().value("param_category").toInt();
            int domainID = query.record().value("domain_id").toInt();
            int type = query.record().value("param_type").toInt();
            int precision = query.record().value("precision").toInt();

            int paramInternalUnit = query.record().value("internal_unit").toInt();
            query.prepare("SELECT * FROM qp_units WHERE id='"+ QString::number(paramInternalUnit)+"'");
            query.exec();
            query.next();

            QString paramInternalUnitCode = query.record().value("code").toString();
            Unit *internalUnit = QParams::QParamsManager::getUnit(paramInternalUnitCode);

            //Continuous or Discrete:
            if(type==0){
                continuousParam = new ContinuousParam(paramID,paramCode,paramName,paramDescription,internalUnit);
                continuousParam->setDefaultValue(defaultValue.toDouble());

                //Domain:
                if(query.prepare("SELECT * FROM qp_domains WHERE id='"+ QString::number(domainID)+"'")){
                    query.exec();
                    if(query.next()){
                        QString domainCode = query.record().value("code").toString();
                        Domain *domain = QParams::QParamsManager::getDomain(domainCode);
                        continuousParam->setMinValue(domain->getMinValue());
                        continuousParam->setMaxValue(domain->getMaxValue());
                        continuousParam->setValidDomain(true);
                        continuousParam->setPrecision(precision);
                    }
                }
            }
            else{
                discreteParam = new DiscreteParam(paramID,paramCode,paramName,paramDescription,internalUnit);
                discreteParam->setDefaultValue(defaultValue);
                discreteParam->setPrecision(precision);

                //Values:
                if(query.prepare("SELECT * FROM qp_values_params WHERE id_param='"+ QString::number(paramID)+"'")){
                    query.exec();

                    while(query.next()){
                        int valueID = query.record().value("id_value").toInt();
                        if(queryAux.prepare("SELECT * FROM qp_values WHERE id='"+ QString::number(valueID)+"'"));
                        queryAux.exec();
                        if(queryAux.next()){
                            int id = queryAux.record().value("id").toInt();
                            QString code = queryAux.record().value("code").toString();
                            QString value = queryAux.record().value("val").toString();
                            QString description = queryAux.record().value("description").toString();
                            Value newValue(id,code,value,description);
                            discreteParam->addValue(queryAux.record().value("code").toString(),newValue);
                        }
                    }
                }
            }

            switch (type){
            case(0):
                param = continuousParam;
                break;
            case(1):
                param = discreteParam;
                break;
            }
            // Category:
            if(query.prepare("SELECT * FROM qp_categories WHERE id='"+ QString::number(categoryID)+"'")){
                query.exec();
                if(query.next()){

                    QString categoryCode = query.record().value("code").toString();
                    Category *category = QParams::QParamsManager::getCategory(categoryCode);
                    param->setCategory(category);
                }
            }
        }
    }
    return param;
}

Param *SQLiteDSManager::getParamByName(QString name)
{
    QSqlQuery query(mDB);
    QSqlQuery queryAux(mDB);

    Param *param = NULL;
    ContinuousParam *continuousParam = NULL;
    DiscreteParam *discreteParam = NULL;
    if(query.prepare("SELECT * FROM qp_params WHERE name='"+name+"'")){
        query.exec();
        if(query.next()){
            int paramID = query.record().value("id").toInt();
            QString paramCode = query.record().value("code").toString();

            QString paramName = query.record().value("name").toString();
            QString paramDescription= query.record().value("description").toString();
            QString defaultValue = query.record().value("default_value").toString();
            int categoryID = query.record().value("param_category").toInt();
            int domainID = query.record().value("domain_id").toInt();
            int type = query.record().value("param_type").toInt();
            int precision = query.record().value("precision").toInt();

            int paramInternalUnit = query.record().value("internal_unit").toInt();
            query.prepare("SELECT * FROM qp_units WHERE id='"+ QString::number(paramInternalUnit)+"'");
            query.exec();
            query.next();

            QString paramInternalUnitCode = query.record().value("code").toString();
            Unit *internalUnit = QParams::QParamsManager::getUnit(paramInternalUnitCode);

            //Continuous or Discrete:            
            if(type==0){
                continuousParam = new ContinuousParam(paramID,paramCode,paramName,paramDescription,internalUnit);
                continuousParam->setDefaultValue(defaultValue.toDouble());

                //Domain:
                if(query.prepare("SELECT * FROM qp_domains WHERE id='"+ QString::number(domainID)+"'")){
                    query.exec();
                    if(query.next()){
                        QString domainCode = query.record().value("code").toString();
                        Domain *domain = QParams::QParamsManager::getDomain(domainCode);
                        continuousParam->setMinValue(domain->getMinValue());
                        continuousParam->setMaxValue(domain->getMaxValue());
                        continuousParam->setValidDomain(true);
                        continuousParam->setPrecision(precision);
                    }
                }
            }
            else{
                discreteParam = new DiscreteParam(paramID,paramCode,paramName,paramDescription,internalUnit);
                discreteParam->setDefaultValue(defaultValue);
                discreteParam->setPrecision(precision);

                //Values:
                if(query.prepare("SELECT * FROM qp_values_params WHERE id_param='"+ QString::number(paramID)+"'")){
                    query.exec();

                    while(query.next()){
                        int valueID = query.record().value("id_value").toInt();
                        if(queryAux.prepare("SELECT * FROM qp_values WHERE id='"+ QString::number(valueID)+"'"));
                        queryAux.exec();
                        if(queryAux.next()){
                            int id = queryAux.record().value("id").toInt();
                            QString code = queryAux.record().value("code").toString();
                            QString value = queryAux.record().value("val").toString();
                            QString description = queryAux.record().value("description").toString();
                            Value newValue(id,code,value,description);
                            discreteParam->addValue(queryAux.record().value("code").toString(),newValue);
                        }
                    }
                }
            }

            switch (type){
            case(0):
                param = continuousParam;
                break;
            case(1):
                param = discreteParam;
                break;
            }
            // Category:
            if(query.prepare("SELECT * FROM qp_categories WHERE id='"+ QString::number(categoryID)+"'")){
                query.exec();
                if(query.next()){

                    QString categoryCode = query.record().value("code").toString();
                    Category *category = QParams::QParamsManager::getCategory(categoryCode);
                    param->setCategory(category);
                }
            }
        }
    }
    return param;
}

//DiscreteParam * SQLiteDSManager::getDiscreteParam(QString code)
//{
//    QSqlQuery query(mDB);
//    DiscreteParam *param = NULL;
//    //if(query.prepare("SELECT * FROM qp_params WHERE code='"+code+"'")){
//    if(true){
//        query.exec("SELECT * FROM qp_params WHERE code='"+code+"'");
//        if(query.next()){
//            int paramID = query.record().value("code").toInt();
//            QString paramCode = query.record().value("code").toString();

//            QString paramName = query.record().value("name").toString();
//            QString paramDescription= query.record().value("description").toString();
//            double defaultValue = query.record().value("default_value").toDouble();
//            int categoryID = query.record().value("param_category").toInt();

//            int paramInternalUnit = query.record().value("internal_unit").toInt();
//            query.prepare("SELECT * FROM qp_units WHERE id='"+ QString::number(paramInternalUnit)+"'");
//            query.exec();
//            query.next();

//            QString paramInternalUnitCode = query.record().value("code").toString();
//            Unit *internalUnit = QParams::QParamsManager::getUnit(paramInternalUnitCode);

//            //Continuous or Discrete:
//            int type = query.record().value("param_type").toInt();
//            if(type==1){
//                param = new DiscreteParam(paramID,paramCode,paramName,paramDescription,internalUnit);
//                param->setDefaultValue(defaultValue);
//                if(query.prepare("SELECT * FROM qp_values_params WHERE id_param='"+QString::number(paramID)+"'")){
//                    query.exec();
//                    if(query.next()){
//                        int valueID = query.record().value("id_value").toInt();
//                        if(query.prepare("SELECT * FROM qp_values WHERE id='"+QString::number(valueID)+"'")){
//                            query.exec();
//                            while (query.next()) {
//                                Value value(query.record().value("id").toInt(),
//                                            query.record().value("code").toString(),
//                                            query.record().value("val").toString(),
//                                            query.record().value("description").toString());
//                                ((DiscreteParam *)param)->getValues().insert(query.record().value("code").toString(),value);
//                            }
//                        }
//                    }
//                }
//            }

//            // Category:
//            if(query.prepare("SELECT * FROM qp_categories WHERE id='"+ QString::number(categoryID)+"'")){
//                query.exec();
//                if(query.next()){

//                    QString categoryCode = query.record().value("code").toString();
//                    Category *category = QParams::QParamsManager::getCategory(categoryCode);
//                    param->setCategory(category);
//                }
//            }
//        }
//    }
//    return param;
//}

Unit * SQLiteDSManager::getUnit(QString code){
    QSqlQuery query(mDB);
    Unit *unit = NULL;
    if(query.prepare("SELECT * FROM qp_units WHERE code='"+code+"'")){
        query.exec();
        if(query.next()){
            int unitID = query.record().value("id").toInt();
            QString unitCode = query.record().value("code").toString();
            QString unitName = query.record().value("name").toString();
            QString unitDescription= query.record().value("description").toString();

//            int baseUnitId = query.record().value("is_base_unit").toInt();
//            Unit *baseUnit = NULL;
//            if (baseUnitId != 0)
//                if(query.prepare("SELECT * FROM qp_units WHERE id='"+ QString::number(baseUnitId) + "'")){
//                    query.exec();
//                    query.next();
//                    baseUnit = QParams::QParamsManager::getUnit(query.record().value("code").toString());
//                }

//            unit = new Unit(unitID,unitCode,unitName,unitDescription,baseUnit);
            unit = new Unit(unitID,unitCode,unitName,unitDescription);
        }
    }
    return unit;
}

Transformation * SQLiteDSManager::getTransformation(Unit *sourceUnit, Unit *targetUnit){
    QSqlQuery query(mDB);
    Transformation *transformation = NULL;
    int sourceUnitID = sourceUnit->getID();
    int targetUnitID = targetUnit->getID();
    if(query.prepare("SELECT * FROM qp_transformations WHERE source_unit='" + QString::number(sourceUnitID)+
                     "' AND target_unit ='"+
                     QString::number(targetUnitID)+"'")){
        query.exec();
        if(query.next()){
            int id = query.record().value("code").toInt();
            QString code = query.record().value("code").toString();
            QString name = query.record().value("name").toString();
            QString description= query.record().value("description").toString();
            QString expression = query.record().value("expression").toString();
            QString expressionInverse = query.record().value("expression_inverse").toString();

            Unit *sourceUnitX = QParams::QParamsManager::getUnit(sourceUnit->getCode());
            Unit *targetUnitX = QParams::QParamsManager::getUnit(targetUnit->getCode());

            transformation = new Transformation(id,code,
                                                name,description,
                                                sourceUnitX,targetUnitX,expression, expressionInverse);
        }
    }
    return transformation;
}

QString SQLiteDSManager::getTransformationCode(QParams::Unit *sourceUnit, QParams::Unit *targetUnit)
{
    QSqlQuery query(mDB);
    int sourceUnitID = sourceUnit->getID();
    int targetUnitID = targetUnit->getID();
    QString code = "";
    if(query.prepare("SELECT * FROM qp_transformations WHERE source_unit='" + QString::number(sourceUnitID)+
                     "' AND target_unit ='"+
                     QString::number(targetUnitID)+"'")){
        query.exec();
        query.next();
        code = query.record().value("code").toString();
        return code;
    }

    return code;
}

Category * SQLiteDSManager::getCategory(QString code)
{
    QSqlQuery query(mDB);
    QSqlQuery query2(mDB);
    Category *category = NULL;
    if(query.prepare("SELECT * FROM qp_categories WHERE code='"+code+"'")){
        query.exec();
        if(query.next()){
            int categorytID = query.record().value("id").toInt();
            QString categoryCode = query.record().value("code").toString();
            QString categoryName = query.record().value("name").toString();
            QString categoryDescription= query.record().value("description").toString();

            int baseUnitId = query.record().value("is_base_unit").toInt();
            Unit *baseUnit = NULL;
            if (baseUnitId != 0)
                if(query.prepare("SELECT * FROM qp_units WHERE id='"+ QString::number(baseUnitId) + "'")){
                    query.exec();
                    query.next();
                    baseUnit = QParamsManager::getUnit(query.record().value("code").toString());
                }

            category = new Category(categorytID,categoryCode,categoryName,categoryDescription, baseUnit);

            if(query.prepare("SELECT * FROM qp_categories_units WHERE id_category='"+QString::number(categorytID)+"'")){
                query.exec();
                while (query.next()) {
                    int unitID = query.record().value("id_unit").toInt();
                    if(query2.prepare("SELECT * FROM qp_units WHERE id='"+QString::number(unitID)+"'")){
                        query2.exec();
                        query2.next();
                        category->getUnitsCodeList()->append(query2.record().value("code").toString());
                    }
                }
            }
        }
    }
    return category;
}

Domain * SQLiteDSManager::getDomain(QString code)
{
    QSqlQuery query(mDB);
    Domain *domain = NULL;
    if(query.prepare("SELECT * FROM qp_domains WHERE code='"+code+"'")){
        query.exec();
        if(query.next()){
            int domainID = query.record().value("id").toInt();
            QString domainCode = query.record().value("code").toString();
            double minValue =  query.record().value("min_value").toDouble();
            double maxValue = query.record().value("max_value").toDouble();

            domain = new Domain(domainID, domainCode, minValue, maxValue);
        }
    }
    return domain;
}

App * SQLiteDSManager::getApp(QString code)
{
    QSqlQuery query(mDB);
    App *app = NULL;
    if(query.prepare("SELECT * FROM qp_apps WHERE code='"+code+"'")){
        query.exec();
        if(query.next()){
            int appID = query.record().value("id").toInt();
            QString appCode = query.record().value("code").toString();
            QString appName = query.record().value("name").toString();
            QString appDescription = query.record().value("description").toString();

            app = new App(appID, appCode, appName, appDescription);
        }
    }
    return app;
}
