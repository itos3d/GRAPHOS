#include "RadialDistortion.h"


RadialDistortion::RadialDistortion()
{
}

RadialDistortion::~RadialDistortion()
{
}

double RadialDistortion::getPP()
{
    return mPP;
}

double RadialDistortion::getSymmetryPP()
{
    return mSymmetryPP;
}

double RadialDistortion::getFocal()
{
    return mFocal;
}

double RadialDistortion::getRadialDistCoef(int index)
{
    return mRadialDistCoefs.at(index);
}

int RadialDistortion::getImageHeight()
{
    return mImageHeight;
}

int RadialDistortion::getImageWidt()
{
    return mImageWidt;
}

void RadialDistortion::setPP(double pp)
{
    mPP = pp;
}

void RadialDistortion::setSymmetryPP(double symmetryPP){
    mSymmetryPP = symmetryPP;
}

void RadialDistortion::setFocal(double f){
    mFocal = f;
}

void RadialDistortion::setImageHeight(int height){
    mImageHeight = height;
}

void RadialDistortion::setImageWidt(int widt){
    mImageWidt = widt;
}

void RadialDistortion::addRadialCoef(double coef)
{
    mRadialDistCoefs.append(coef);
}
