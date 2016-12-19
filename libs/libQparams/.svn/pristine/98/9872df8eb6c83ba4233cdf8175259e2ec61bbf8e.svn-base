#include "transformation.h"


using namespace QParams;

Transformation::Transformation(QString code)
{
}

Transformation::Transformation(int id, QString code, QString name, QString description,
                               Unit *soruceUnit, Unit *targetUnit,QString experession, QString expressionInverse):
    mID(id),
    mCode(code),
    mName(name),
    mDescription(description),
    mSourceUnit(soruceUnit),
    mTargetUnit(targetUnit),
    mExpression(experession),
    mExpressionInverse(expressionInverse),
    mInverted(false)
{
}

double QParams::Transformation::transform(double value)
{
    if(!isInverted())
        mParser.SetExpr(mExpression.toStdString());
    else
        mParser.SetExpr(mExpressionInverse.toStdString());
    mParser.DefineVar("x", &value);
    return mParser.Eval();
}

double QParams::Transformation::transformInverse(double value)
{
    if(!isInverted())
        mParser.SetExpr(mExpressionInverse.toStdString());
    else
        mParser.SetExpr(mExpression.toStdString());
    mParser.DefineVar("x", &value);
    return mParser.Eval();
}

QString QParams::Transformation::getName()
{
    return mName;
}

bool QParams::Transformation::isInverted()
{
    return mInverted;
}

void QParams::Transformation::setInverted(bool inverted)
{
    mInverted = inverted;
}

QString QParams::Transformation::getCode()
{
    return mCode;
}

QString QParams::Transformation::getDescription()
{
    return mDescription;
}

QString QParams::Transformation::getExpression()
{
    return mExpression;
}

QString QParams::Transformation::getExpressionInverse()
{
    return mExpressionInverse;
}

QParams::Unit * QParams::Transformation::getSourceUnit()
{
    return mSourceUnit;
}

QParams::Unit * QParams::Transformation::getTargetUnit()
{
    return mTargetUnit;
}

void QParams::Transformation::setTargetUnit(QParams::Unit *targerUnit)
{
    mTargetUnit = targerUnit;
}

void QParams::Transformation::setSourceUnit(QParams::Unit *sourceUnit)
{
    mSourceUnit = sourceUnit;
}

void QParams::Transformation::setExressionInverse(QString expression)
{
    mExpressionInverse = expression;
}

void QParams::Transformation::setExression(QString expression)
{
    mExpression = expression;
}

void QParams::Transformation::setDescription(QString description)
{
    mDescription = description;
}

void QParams::Transformation::setName(QString name)
{
    mName = name;
}

void QParams::Transformation::setCode(QString code)
{
    mCode = code;
}

