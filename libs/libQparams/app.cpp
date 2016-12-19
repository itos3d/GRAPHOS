#include "app.h"

App::App(int id, QString code, QString name, QString description):
    mID(id),
    mCode(code),
    mName(name),
    mDescription(description)
{
}

void App::setDescription(QString description)
{
    mDescription = description;
}

void App::setName(QString name)
{
    mName = name;
}

void App::setCode(QString code)
{
    mCode = code;
}

void App::setID(int id)
{
    mID = id;
}

QString App::getDescription()
{
    return mDescription;
}

QString App::getName()
{
    return mName;
}

QString App::getCode()
{
    return mCode;
}

int App::getID()
{
    return mID;
}
