#include "category.h"

using namespace QParams;

Category::Category(int id,QString code, QString name, QString description, Unit *baseUnit):
    mID(id),
    mCode(code),
    mName(name),
    mDescription(description),
    mBaseUnit(baseUnit)
{
}

int Category::getID()
{
    return mID;
}

QString Category::getCode()
{
    return mCode;
}

QString Category::getName()
{
    return mName;
}

QString Category::getDescription()
{
    return mDescription;
}

QStringList * Category::getUnitsCodeList()
{
    return &mUnitsCodeList;
}

QParams::Unit * QParams::Category::getBaseUnit()
{
    return mBaseUnit;
}

void QParams::Category::setBaseUnit(QParams::Unit *baseUnit)
{
    mBaseUnit = baseUnit;
}
