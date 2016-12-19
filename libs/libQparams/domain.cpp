#include "domain.h"

using namespace QParams;

Domain::Domain(int id, QString code, double minValue, double maxValue):
    mID(id),
    mCode(code),
    mMinValue(minValue),
    mMaxValue(maxValue)
{
}

int Domain::getID()
{
    return mID;
}

QString Domain::getCode()
{
    return mCode;
}

double Domain::getMinValue()
{
    return mMinValue;
}

double Domain::getMaxValue()
{
    return mMaxValue;
}

void Domain::setID(int id)
{
    mID = id;
}

void Domain::setCode(QString code)
{
    mCode = code;
}

void Domain::setMinValue(double value)
{
    mMinValue = value;
}

void Domain::setMaxValue(double value)
{
    mMaxValue = value;
}
