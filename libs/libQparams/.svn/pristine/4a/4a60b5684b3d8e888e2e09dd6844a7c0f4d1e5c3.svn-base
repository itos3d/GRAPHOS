#include <QDebug>

#include "param.h"
#include "qparams.h"

using namespace QParams;

ContinuousParam::ContinuousParam(QString code):
    Param(code),
    mInternalVal(0),
    mValidDomain(false)
{
}

ContinuousParam::ContinuousParam(QString code, QString name, QString description, Unit *internalUnit):
    Param(code,name,description,internalUnit),
    mInternalVal(0),
    mValidDomain(false)
{

}

ContinuousParam::ContinuousParam(int id, QString code, QString name, QString description, Unit *internalUnit):
    Param(id,code,name,description,internalUnit),
    mInternalVal(0),
    mValidDomain(false)
{

}

Param::Param(QString code):
    mCode(code)
{
    /*TODO*/
}


Param::Param(QString code, QString name, QString description, Unit *internalUnit):
    mCode(code),
    mName(name),
    mDescription(description),
    mInternalUnit(internalUnit)
{

}

Param::Param(int id, QString code, QString name, QString description, Unit *internalUnit):
    mID(id),
    mCode(code),
    mName(name),
    mDescription(description),
    mInternalUnit(internalUnit)
{

}

void Param::setCode(QString code)
{
    mCode = code;
}

void Param::setName(QString name)
{
    mName = name;
}

void Param::setDescription(QString description)
{
    mDescription = description;
}

void Param::setInternalUnit(Unit *unit)
{
    mInternalUnit = unit;
}

QString Param::getName()
{
    return mName;
}

QString Param::getCode()
{
    return mCode;
}

QString Param::getDescription()
{
    return mDescription;
}

Unit *Param::getInternalUnit()
{
    return mInternalUnit;
}

void Param::setID(int id)
{
    mID = id;
}

int Param::getID()
{
    return mID;
}

Category * QParams::Param::getCategory()
{
    return mCategory;
}

int Param::getPrecision()
{
    return mPrecision;
}

double ContinuousParam::getDefaultValue()
{
    return mDefaultValue;
}


double ContinuousParam::getMinValue()
{
    return mMinValue;
}

double ContinuousParam::getMaxValue()
{
    return mMaxVaule;
}

double ContinuousParam::isValidDomain()
{
    return mValidDomain;
}

void ContinuousParam::setDefaultValue(double value)
{
    mDefaultValue = value;
}

void ContinuousParam::setMinValue(double value)
{
    mMinValue = value;
}

void ContinuousParam::setMaxValue(double value)
{
    mMaxVaule = value;
}

void ContinuousParam::setValidDomain(bool isValidDomain)
{
    mValidDomain = isValidDomain;
}

void Param::setCategory(Category *category)
{
    mCategory = category;
}

void Param::setPrecision(int precission)
{
    mPrecision = precission;
}


double ContinuousParam::getValue()
{
    return mInternalVal;
}

double ContinuousParam::getValue(Unit *unit)
{
    return 0; //TODO.
}

double ContinuousParam::setValue(double value)
{
    mInternalVal = value;
    return mInternalVal;
}

double ContinuousParam::setValue(double value, Unit *unit)
{
    if (unit->getCode() == mInternalUnit->getCode())
    {
        mInternalVal = value;
        return mInternalVal;
    }

    Transformation *transformation = QParamsManager::getTransformation(unit, mInternalUnit);
    if(transformation == NULL){
        QString message = "Transformation not found: " + unit->getName() + " -> " + mInternalUnit->getName();
        qCritical() << tr(message.toAscii());
        return mInternalVal;
    }

    mInternalVal = transformation->transform(value);
    return mInternalVal;
}

DiscreteParam::DiscreteParam(QString code):
    Param(code)
{
}

DiscreteParam::DiscreteParam(QString code, QString name, QString description, Unit *internalUnit):
    Param(code,name,description,internalUnit)
{

}

DiscreteParam::DiscreteParam(int id, QString code, QString name, QString description, Unit *internalUnit):
    Param(id,code,name,description,internalUnit)
{

}

QMap<QString,Value> DiscreteParam::getValues(){
    return mValues;
}

Value DiscreteParam::getValue(QString code)
{
    return mValues.value(code);
}

QString DiscreteParam::getValue()
{
    return mInternalValue;
}

QString DiscreteParam::getDefaultValue()
{
    return mDefaultValue;
}

void DiscreteParam::addValue(QString code, QParams::Value value)
{
    mValues.insert(code, value);
}

void DiscreteParam::setValue(QString value)
{
    mInternalValue = value;
}


void DiscreteParam::setDefaultValue(QString value)
{
    mDefaultValue = value;
}
