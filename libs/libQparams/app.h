#ifndef APP_H
#define APP_H

#include <QString>

class App
{
public:
    App(int id, QString code, QString name, QString description);

    /*!
     \brief

     \return int Numeric ID of the Application (usually the primary key in the database).
    */
    int getID();

    /*!
     \brief

     \return QString Code of the Application.
    */
    QString getCode();

    /*!
     \brief

     \return QString The full name of Application.
    */
    QString getName();

    /*!
     \brief

     \return QString Description text.
    */
    QString getDescription();

    /*!
     \brief Sets the numeric ID of the Application (usually the primary key in the database).

     \param unitCode Numeric ID of the Application.
    */
    void setID(int id);

    /*!
     \brief Sets the text code.

     \param code The text code
    */
    void setCode(QString code);

    /*!
     \brief Sets the Application name.

     \param name The Application name.
    */
    void setName(QString name);

    /*!
     \brief sets the description text.

     \param description Description text.
    */
    void setDescription(QString description);

private:
    int mID;
    QString mCode;
    QString mName;
    QString mDescription;
};

#endif // APP_H
