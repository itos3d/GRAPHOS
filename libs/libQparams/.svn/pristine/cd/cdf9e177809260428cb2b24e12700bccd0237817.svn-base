#ifndef VALUE_H
#define VALUE_H

#include <QString>

namespace QParams{


/*!
 \brief Class representing value (usually for use with discrete params).

*/
class Value
{
public:

    /*!
     \brief Constructor.

     \param code String code.
    */
        Value();

    /*!
     \brief Constructor.

     \param code String code.
    */
        Value(QString code);

    /*!
     \brief Contructor.

     \param code String code.
     \param value The value.
     \param description Description text.
    */
        Value(QString code, QString value, QString description);

        /*!
         \brief Contructor.

         \param id Numeric ID.
         \param code String code.
         \param value The value.
         \param description Description text.
        */
        Value(int id,QString code, QString value, QString description);

        /*!
         \brief

         \return int Numeric ID of the value (usually the primary key in the database).
        */
        int getID();

        /*!
         \brief

         \return QString Code of the value.
        */
        QString getCode();

        /*!
         \brief

         \return QString Value.
        */
        QString getValue();

        /*!
         \brief

         \return QString Description text.
        */
        QString getDescription();

        /*!
         \brief Set the numeric ID of the value (usually the primary key in the database).

         \param unitCode Numeric ID of the value.
        */
        void setID(int id);

        /*!
         \brief Set the text code.

         \param code The text code
        */
        void setCode(QString code);

        /*!
         \brief Set the value.

         \param name The value.
        */
        void setValue(QString value);

        /*!
         \brief set the description text.

         \param description Description text.
        */
        void setDescription(QString description);

private:
        int mID;
        QString mCode;
        QString mValue;
        QString mDescription;
};

}
#endif // VALUE_H
