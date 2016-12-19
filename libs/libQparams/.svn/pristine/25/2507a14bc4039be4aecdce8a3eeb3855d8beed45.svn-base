#ifndef DOMAIN_H
#define DOMAIN_H

#include <QString>

namespace QParams{

/*!
 \brief Domain of a param.

*/
class Domain
{
public:

    Domain(int id, QString code, double minValue, double maxValue);


    /*!
     \brief

     \return int Numeric ID of the domain
    */
    int getID();

    /*!
     \brief

     \return int Text code of the domain
    */
    QString getCode();

    /*!
     \brief

     \return int Min value allowed
    */
    double getMinValue();

    /*!
     \brief

     \return int Max value allowed
    */
    double getMaxValue();

    /*!
     \brief Sets the numeric ID of the domain

     \param id The ID
    */
    void setID(int id);

    /*!
     \brief Sets text code of the domain

     \param code The code
    */
    void setCode(QString code);

    /*!
     \brief Sets the min value

     \param value Min value
    */
    void setMinValue(double value);

    /*!
     \brief Sets the max value

     \param value max value
    */
    void setMaxValue(double value);

private:
    int mID;
    QString mCode;
    double mMinValue;
    double mMaxValue;
};

}

#endif // DOMAIN_H
