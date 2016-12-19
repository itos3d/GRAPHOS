#ifndef TRASFORMATION_H
#define TRASFORMATION_H

#include <QString>
#include <muParser.h>

#include "unit.h"


namespace QParams{

//! Conversion between units.
/*!
  Class to convert between units.
*/
class Transformation
{
public:

    Transformation(QString code);
    Transformation(int id, QString code, QString name, QString description,
                   Unit *soruceUnit, Unit *targetUnit,QString experession, QString expressionInverse);

    /*!
     \brief

     \param value in pirnt units.
     \return Value in internal units.
    */
    double transform(double value);
    /*!
     \brief

     \param Value in internal units.
     \return Value in pirnt units.
    */
    double transformInverse(double value);


    /*!
     \brief Get Transformation full name.

     \return QString The name.
    */
    QString getName();

    /*!
     \brief Get Transformation code.

     \return QString The code.
    */
    QString getCode();

    /*!
     \brief Get Transformation description text.

     \return QString The desciption.
    */
    QString getDescription();

    /*!
     \brief Get direct transformation expression.

     \return QString The direct expressión.
    */
    QString getExpression();

    /*!
     \brief Get inverse transformation expression.

     \return QString The inverse expressión.
    */
    QString getExpressionInverse();

    /*!
     \brief Get Source Unit.

     \return Unit * Source Unit.
    */
    Unit * getSourceUnit();

    /*!
     \brief Get Target Unit.

     \return Unit * Target Unit.
    */
    Unit * getTargetUnit();

    /*!
     \brief If true trasnform(double) performs inverse trasformation and trasnformInverse performs direct transformation.

     \return bool
    */
    bool isInverted();


    /*!
     \brief Reverses the use of transform(double) and transformInverse(double)

     \param inverted true if trasnform(double) performs inverse trasformation and trasnformInverse performs direct transformation.
    */
    void setInverted(bool inverted);


    /*!
     \brief Set the Transformation code.

     \param code
    */
    void setCode(QString code);

    /*!
     \brief Set the Transformation name.

     \param name
    */
    void setName(QString name);

    /*!
     \brief Set the description text.

     \param description
    */
    void setDescription(QString description);

    /*!
     \brief Set the direct transformation expression.

     \param expression
    */
    void setExression(QString expression);

    /*!
     \brief Set the inverse transformation expression.

     \param expression
    */
    void setExressionInverse(QString expression);

    /*!
     \brief Set source unit.

     \param sourceUnit
    */
    void setSourceUnit(Unit *sourceUnit);

    /*!
     \brief Set target unit.

     \param targerUnit
    */
    void setTargetUnit(Unit *targerUnit);

private:
    int         mID;
    QString     mCode;
    QString     mName;
    QString     mDescription;
    Unit *      mSourceUnit;
    Unit *      mTargetUnit;
    QString     mExpression;
    QString     mExpressionInverse;
    bool        mInverted;

    mu::Parser mParser;

};

}
#endif // TRASFORMATION_H
