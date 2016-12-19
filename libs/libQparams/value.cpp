#include "value.h"

using namespace QParams;

Value::Value()
{
}

Value::Value(QString code)
{
}

Value::Value(QString code, QString value, QString description):
    mCode(code),
    mValue(value),
    mDescription(description)
{
}

Value::Value(int id, QString code, QString value, QString description):
    mID(id),
    mCode(code),
    mValue(value),
    mDescription(description)
{
}

int QParams::Value::getID()
{
    return mID;
}

QString QParams::Value::getCode()
{
    return mCode;
}

QString QParams::Value::getValue()
{
    return mValue;
}

QString QParams::Value::getDescription()
{
    return mDescription;
}

void QParams::Value::setID(int id)
{
    mID = id;
}

void QParams::Value::setCode(QString code)
{
    mCode = code;
}

void QParams::Value::setValue(QString value)
{
    mValue = value;
}

void QParams::Value::setDescription(QString description)
{
    mDescription = description;
}
