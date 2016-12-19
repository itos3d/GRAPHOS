#ifndef CATEGORY_H
#define CATEGORY_H

#include <QString>
#include <QStringList>

#include "unit.h"

namespace QParams{

class Category
{
public:

    /*!
     \brief Constructor.

     \param code String code.
    */
    Category(int id,QString code, QString name, QString description, Unit *baseUnit);

    /*!
     \brief

     \return int Numeric ID of the Category (usually the primary key in the database).
    */
    int getID();

    /*!
     \brief

     \return QString Code of the Category.
    */
    QString getCode();

    /*!
     \brief

     \return QString The full name of Category.
    */
    QString getName();

    /*!
     \brief

     \return QString Description text.
    */
    QString getDescription();


    /*!
     \brief

     \return QStringList * The list of units (only de codes) of de category.
    */
    QStringList *getUnitsCodeList();

    /*!
     \brief gets the Category base unit.

     \return Unit * the Category base unit.
    */
    Unit *getBaseUnit();

    /*!
     \brief sets the Category Sistem base unit.

     \param baseUnit The Category base unit.
    */
    void setBaseUnit(Unit * baseUnit);


private:
    int         mID;
    QString     mCode;
    QString     mName;
    QString     mDescription;
    Unit        *mBaseUnit;

    QStringList mUnitsCodeList;
};

}
#endif // CATEGORY_H
