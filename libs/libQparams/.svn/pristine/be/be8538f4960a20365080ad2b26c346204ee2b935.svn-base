#ifndef UNIT_H
#define UNIT_H

#include <QString>

namespace QParams{


/*!
 \brief Class representing measure unit.

*/
class Unit
{
public:

/*!
 \brief Constructor.

 \param code String code.
*/
    Unit(QString code);

/*!
 \brief Contructor.

 \param code String code.
 \param name Full name.
 \param description Description text.
*/
    Unit(QString code, QString name, QString description);

    /*!
     \brief Contructor.

     \param id Numeric ID.
     \param code String code.
     \param name Full name.
     \param description Description text.
    */
    Unit(int id,QString code, QString name, QString description);

    /*!
     \brief

     \return int Numeric ID of the unit (usually the primary key in the database).
    */
    int getID();

    /*!
     \brief

     \return QString Code of the unit.
    */
    QString getCode();

    /*!
     \brief

     \return QString The full name of unit.
    */
    QString getName();

    /*!
     \brief

     \return QString Description text.
    */
    QString getDescription();

    /*!
     \brief gets the Insternational Sistem base unit.

     \return Unit * the IS base unit.
    */
//    Unit *getISBaseUnit();

    /*!
     \brief Sets the numeric ID of the unit (usually the primary key in the database).

     \param unitCode Numeric ID of the unit.
    */
    void setID(int id);

    /*!
     \brief Sets the text code.

     \param code The text code
    */
    void setCode(QString code);

    /*!
     \brief Sets the unit name.

     \param name The unit name.
    */
    void setName(QString name);

    /*!
     \brief sets the description text.

     \param description Description text.
    */
    void setDescription(QString description);

    /*!
     \brief sets the International Sistem base unit.

     \param baseUnit The IS base unit.
    */
//    void setISBaseUnit(Unit * baseUnit);


private:
    int mID;
    QString mCode;
    QString mName;
    QString mDescription;
//    Unit *mISBaseUnit;
};

}
#endif // UNIT_H
