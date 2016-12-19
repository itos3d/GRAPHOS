#ifndef QPARAM_H
#define QPARAM_H

#include <QString>
#include <QVariant>
#include <QMap>

#include "unit.h"
#include "value.h"
#include "category.h"


//!  ContinuousParam class.
/*!
  Base class representing parameter.
*/
namespace QParams{

class Param : public QObject
{
public:
    Param(QString code);
    Param(QString code, QString name, QString description, Unit *internalUnit);
    Param(int id, QString code, QString name, QString description, Unit *internalUnit);

    /*!
     \brief

     \return int Numeric ID of the param (usually the primary key in the database).
    */
    virtual int getID();

    /*!
     \brief

     \return QString Code of the param.
    */
    virtual QString getCode();

    /*!
     \brief

     \return QString Full name.
    */
    virtual QString getName();

    /*!
     \brief

     \return QString Description text.
    */
    virtual QString getDescription();

    /*!
     \brief

     \return QString Code of the asociated internal unit.
    */
    virtual Unit *getInternalUnit();


    /*!
     \brief

     \return Category * The param category.
    */
    virtual Category *getCategory();

    /*!
     \brief

     \return int Precission (number of decimals to use).
    */
    virtual int getPrecision();

    /*!
     \brief Set the numeric ID of the param (usually the primary key in the database).

     \param unitCode Numeric ID of the param.
    */
    virtual void setID(int id);

    /*!
     \brief Set the text code.

     \param code The text code
    */
    virtual void setCode(QString code);

    /*!
     \brief Set the full name of the param.

     \param name The name.
    */
    virtual void setName(QString name);

    /*!
     \brief set the description text.

     \param description Description text.
    */
    virtual void setDescription(QString description);

    /*!
     \brief Set the code of the asociated internal unit.
     \param unitCode Code of the asociated internal unit.
    */
    virtual void setInternalUnit(Unit *unit);

    /*!
     \brief Set the param categroy.

     \param category The category.
    */
    virtual void setCategory(Category *category);

    /*!
     \brief Set the param categroy.

     \param int precission (number of decimals to use).
    */
    virtual void setPrecision(int precission);


protected:
    int         mID;
    QString     mCode;
    QString     mName;
    QString     mDescription;
    Unit        *mInternalUnit;
    Category    *mCategory;
    int         mPrecision;
};

//!  ContinuousParam class.
/*!
  Class representing a continuous parameter and implement conversions between internal and printing units.
*/
class ContinuousParam: public Param
{
public:

    /*!
 \brief Constructor

 \param Param code in database.
*/
    ContinuousParam(QString code);

    ContinuousParam(QString code, QString name, QString description, Unit *internalUnit);
    ContinuousParam(int id, QString code, QString name, QString description, Unit *internalUnit);


    //! Set the param value in internal unit.
    /*!
     \param vaule The value in internal unit.
     \return The value with internal unit.
   */
    virtual double setValue(double vaule);

    //! Set the param value.
    /*!
     \param vaule The value.
     \param unit The value input unit.
     \return The value with internal unit.
   */
    virtual double setValue(double vaule, Unit *unit);

    //! Get the value of the param with internal param unit.
    /*!
     \return The value of the param.
   */
    virtual double getValue();

    //! Get the value of the param with sepecified unit.
    /*!
     \param unit The unit
     \return The value.
   */
    virtual double getValue(Unit *unit);

    /*!
     \brief

     \return double Min value.
    */
    virtual double getMinValue();

    /*!
     \brief

     \return double Max value.
    */
    virtual double getMaxValue();

    /*!
     \brief

     \return double Default value.
    */
    virtual double getDefaultValue();


    /*!
     \brief

     \return bool if domain (máx and min values) is valid.
    */
    virtual double isValidDomain();

    /*!
     \brief Set the Min allowed value.

     \param Min value.
    */
    virtual void setMinValue(double value);

    /*!
     \brief Set the Max allowed value.

     \param Max value.
    */
    virtual void setMaxValue(double value);

    /*!
     \brief Set the "isValidDomian" value.

     \param isValidDomian value.
    */
    virtual void setValidDomain(bool isValidDomain);

    /*!
     \brief Set the default value.

     \param value default value.
    */
    virtual void setDefaultValue(double value);


private:

    double      mMinValue;
    double      mMaxVaule;
    double      mInternalVal;
    bool        mValidDomain;
    double      mDefaultValue;

};

//!  DiscreteParam class.
/*!
  Class representing a continuous parameter and implement conversions between internal and printing units.
*/
class DiscreteParam: public Param
{
public:
    DiscreteParam(QString code);

    DiscreteParam(QString code, QString name, QString description, Unit *internalUnit);
    DiscreteParam(int id, QString code, QString name, QString description, Unit *internalUnit);


    QMap<QString,Value> getValues();

    /*!
     \brief

     \return double value from list.
    */
    Value getValue(QString code);

    /*!
     \brief

     \return double current value.
    */
    virtual QString getValue();

    /*!
     \brief

     \return double Default value.
    */
    virtual QString getDefaultValue();

    /*!
     \brief Add value to the list.

     \param value.
    */
    void addValue(QString code, Value value);

    /*!
     \brief Set the default value.

     \param value current value.
    */
    virtual void setValue(QString value);

    /*!
     \brief Set the default value.

     \param value default value.
    */
    virtual void setDefaultValue(QString value);


private:
    QMap<QString,Value>     mValues;
    QString                 mDefaultValue;
    QString                 mInternalValue;
};

}
#endif // QPARAM_H
