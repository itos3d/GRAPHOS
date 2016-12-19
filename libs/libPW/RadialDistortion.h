#ifndef RADIALDISTORTION_H
#define RADIALDISTORTION_H

#include <QVector>

#include "CamDistortion.h"

/*!
 \brief Base class representing camera distortion as radial distortion model.

*/
class RadialDistortion : public CamDistortion
{
public:
/*!
 \brief Constructor

*/
    RadialDistortion();
    /*!
     \brief Destructor

    */
    ~RadialDistortion();

    /*!
     \brief Gets the principal ponit value in pixels.

     \return float principal point in pixels.
    */
    double getPP();
    /*!
     \brief Gets the principal poin of symmetry in pixels.

     \return float principal poin of symmetry in pixels.
    */
    double getSymmetryPP();
    /*!
     \brief Gets the focal lenght in pixels.

     \return float focal lenght in pixels.
    */
    double getFocal();
    /*!
     \brief Gets a coefficient of radial distortion.

     \param index Position of the coefficient in the vector of coefficients.
     \return float the coefficient at position indicated by index.
    */
    double getRadialDistCoef(int index);
    /*!
     \brief Gets the image height in pixels.

     \return int image height in pixels.
    */
    int getImageHeight();
    /*!
     \brief gets the image widt in pixels.

     \return int Image widt in pixels.
    */
    int getImageWidt();

    /*!
     \brief Sets the principal ponit value in pixels.

     \param pp principal ponit value in pixels.
    */
    void setPP(double pp);
    /*!
     \brief Sets the principal poin of symmetry in pixels.

     \param symmetryPP principal poin of symmetry in pixels.
    */
    void setSymmetryPP(double symmetryPP);
    /*!
     \brief Sets the focal lenght in pixels.

     \param f focal lenght in pixels.
    */
    void setFocal(double f);
    /*!
     \brief Sets the image height in pixels.

     \param height the image height in pixels.
    */
    void setImageHeight(int height);
    /*!
     \brief Sets the image widt in pixels.

     \param widt the image widt in pixels.
    */
    void setImageWidt(int widt);
    /*!
     \brief Append a coefficient of radial distortion at the of the coefficients vector.

     \param coef A coefficient of radial distortion.
    */
    void addRadialCoef(double coef);

private:
    double   mPP;
    double   mSymmetryPP;
    double   mFocal;
    int     mRadialDistCoefsCount;
    int     mImageHeight;
    int     mImageWidt;
    QVector <double>   mRadialDistCoefs;
};

#endif // RADIALDISTORTION_H
