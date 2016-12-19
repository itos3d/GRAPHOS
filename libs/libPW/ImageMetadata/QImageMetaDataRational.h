//--------------------------------------------------------------------------------
//    Copyright (c) Kate Labs Ltd 2010
//
//    This file is part of QImageMetaData.
//
//    QImageMetaData is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    QImageMetaData is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//    GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public License
//    along with QImageMetaData. If not, see <http://www.gnu.org/licenses/>.
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
// Note! Natural Docs is used to generate documentation from this file.
//
//       Please use appropriate comments.
//
//       For further details, please see http://www.naturaldocs.org.
//--------------------------------------------------------------------------------

#ifndef RATIONAL_H
#define RATIONAL_H

//--------------------------------------------------------------------------------
// Headers
//--------------------------------------------------------------------------------
#include <QtCore/QtGlobal>

//--------------------------------------------------------------------------------
// Class: QImageMetaDataRational
//
// The class implements a rational which nominator and denominator
// consist of 32-bits unsigned or signed integers.
//--------------------------------------------------------------------------------
/*!
 * The class implements a rational number which nominator and denominator
 * consist of 32-bit unsigned or signed integers.
 */
template <typename T>
class QImageMetaDataRational
{
public:
  //------------------------------------------------------------------------------
  // Method: Constructor
  //
  // The default constructor.
  //------------------------------------------------------------------------------
  /*!
   * The default constructor, which sets the nominator and the denominator to zero.
   */
  QImageMetaDataRational();

  //------------------------------------------------------------------------------
  // Method: Destructor
  //
  // The default destructor.
  //------------------------------------------------------------------------------
  /*!
   * The default destructor.
   */
  ~QImageMetaDataRational();

  //------------------------------------------------------------------------------
  // Method: init
  //
  // Initialises the rational.
  //------------------------------------------------------------------------------
  /*!
   * The method initialises the rational and sets the nominator and the denominator to zero.
   */
  void init();

  //------------------------------------------------------------------------------
  // Method: init
  //
  // Initialises the rational.
  //------------------------------------------------------------------------------
  /*!
   * The method initialises the rational and sets the nominator and the denominator.
   *
   * \param nominator   The nominator of the rational.
   * \param denominator The denominator of the rational.
   */
  void init(T nominator,T denominator);

  //------------------------------------------------------------------------------
  // Method: setNominator
  //
  // Sets the nominator of the variable.
  //------------------------------------------------------------------------------
  /*!
   * The method sets the nominator of the rational.
   *
   * \param nominator The nominator of the rational.
   */
  void setNominator(T nominator);

  //------------------------------------------------------------------------------
  // Method: setDenominator
  //
  // Sets the denominator of the variable.
  //------------------------------------------------------------------------------
  /*!
   * The method sets the denominator of the rational.
   *
   * \param denominator The denominator of the rational.
   */
  void setDenominator(T denominator);

  //------------------------------------------------------------------------------
  // Method: nominator
  //
  // Returns the nominator of the variable.
  //------------------------------------------------------------------------------
  /*!
   * The method returns the nominator of the rational.
   *
   * \return The nominator of the rational.
   */
  T nominator();

  //------------------------------------------------------------------------------
  // Method: denominator
  //
  // Returns the denominator of the variable.
  //------------------------------------------------------------------------------
  /*!
   * The method return the denominator of the rational.
   *
   * \return The denominator of the rational.
   */  
  T denominator();

  //------------------------------------------------------------------------------
  // Method: value
  //
  // Returns the value of the variable.
  // If the variable is not rational, the method returns zero.
  //------------------------------------------------------------------------------
  /*!
   * The method returns the value of the rational. If the denominator of the rational is zero,
   * the method returns zero.
   *
   * \return The value of the rational.
   */
  qreal value();

  //------------------------------------------------------------------------------
  // Method: rational
  //
  // Returns true if the variable is rational; false otherwise.
  //------------------------------------------------------------------------------
  /*!
   * The method determines if the rational is a real number, i.e.,
   * the denominator is inequal to zero.
   *
   * \return True if the rational is a real number; false otherwise.
   */
  bool rational();

protected:

private:
  T nominator_;
  T denominator_;
};

//--------------------------------------------------------------------------------
// Constructor
//--------------------------------------------------------------------------------
template <typename T>
QImageMetaDataRational<T>::QImageMetaDataRational()
{
  nominator_   = 0;
  denominator_ = 0;
}

//--------------------------------------------------------------------------------
// Destructor
//--------------------------------------------------------------------------------
template <typename T>
QImageMetaDataRational<T>::~QImageMetaDataRational()
{

}

//--------------------------------------------------------------------------------
// Init
//--------------------------------------------------------------------------------
template <typename T>
void QImageMetaDataRational<T>::init() {
  nominator_   = 0;
  denominator_ = 0;
}

template <typename T>
void QImageMetaDataRational<T>::init(T nominator,T denominator) {
  nominator_   = nominator;
  denominator_ = denominator;
}

//--------------------------------------------------------------------------------
// Nominator and denominator
//--------------------------------------------------------------------------------
template <typename T>
void QImageMetaDataRational<T>::setNominator(T nominator)
{
  nominator_ = nominator;
}

template <typename T>
void QImageMetaDataRational<T>::setDenominator(T denominator)
{
  denominator_ = denominator;
}

//--------------------------------------------------------------------------------
// Nominator and denominator
//--------------------------------------------------------------------------------
template <typename T>
T QImageMetaDataRational<T>::nominator()
{
  return nominator_;
}

template <typename T>
T QImageMetaDataRational<T>::denominator()
{
  return denominator_;
}

//--------------------------------------------------------------------------------
// Value
//--------------------------------------------------------------------------------
template <typename T>
qreal QImageMetaDataRational<T>::value()
{
  if (this->rational() == false) {
    return 0;
  } else {
    return static_cast<qreal>(nominator_)/static_cast<qreal>(denominator_);
  }
}

//--------------------------------------------------------------------------------
// Rational
//--------------------------------------------------------------------------------
template <typename T>
bool QImageMetaDataRational<T>::rational()
{
  if (denominator_ == 0) {
    return false;
  } else {
    return true;
  }
}

#endif
