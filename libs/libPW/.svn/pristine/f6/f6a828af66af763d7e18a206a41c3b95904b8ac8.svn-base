#include <exiv2/exiv2.hpp>
#include <exiv2/tags.hpp>

#include "CameraExifIO.h"
#include <QStringList>

using namespace PW;

CameraExifIO::CameraExifIO(QString imagePath):
    mImagePath(imagePath)
{
}

void CameraExifIO::setImagePath(QString imagePath)
{
    mImagePath = imagePath;
}

void CameraExifIO::read(Camera *camera)
{
    Exiv2::Image::AutoPtr imageExif = Exiv2::ImageFactory::open(mImagePath.toStdString());
    imageExif->readMetadata();
    Exiv2::ExifData &exifData = imageExif->exifData();
    Exiv2::ExifData::const_iterator iterator = Exiv2::model(exifData);
    //            Exiv2::ExifData::const_iterator iterator = exifData.findKey(Exiv2::ExifKey("Exif.Image.Model"));
    Exiv2::ExifData::const_iterator end = exifData.end();
    QString cameraModel = "";
    if (iterator != end)
        cameraModel = QString::fromStdString(iterator->value().toString ());

    //    iterator = exifData.findKey(Exiv2::ExifKey("Exif.Photo.LensModel"));
    iterator = Exiv2::lensName(exifData);
    end = exifData.end();
    QString lens = "";
    if (iterator != end){
        lens = QString::fromStdString(iterator->print(&exifData));
        //        lens = QString::fromStdString(iterator->value().toString ());
    }
    else{
        iterator = Exiv2::lensName(exifData);
        end = exifData.end();
        if (iterator != end)
            lens = QString::fromStdString(iterator->print(&exifData));
    }

    //  OBTENER EL RESTO DEL EXIF
    iterator = Exiv2::focalLength(exifData);
    end = exifData.end();
    QString focal = "";
    double focalLength = 0;
    if (iterator != end){
        focal = QString::fromStdString(iterator->value().toString ());
        if(!focal.isEmpty()){
            QStringList focalSplit = focal.split("/");
            if (focalSplit.count() == 2)
                focal = QString::number(focalSplit.at(0).toDouble()/focalSplit.at(1).toDouble());
            else if(focalSplit.count()!=1)
                focal = "";
        }
        focalLength = focal.toDouble();
    }

    iterator = exifData.findKey(Exiv2::ExifKey("Exif.Photo.FocalLengthIn35mmFilm"));
    end = exifData.end();
    QString focal35 = "";
    double scaleFactor = 0;
    if (iterator != end){
        focal35 = QString::fromStdString(iterator->value().toString ());
        if (!focal35.isEmpty()){
            QStringList focalSplit = focal35.split("/");
            if (focalSplit.count() == 2){
                scaleFactor = focalSplit.at(0).toDouble()/focalSplit.at(1).toDouble();
            }
            else if(focalSplit.count() ==1)
            {
                scaleFactor = focal35.toDouble()/focal.toDouble();
            }
        }
    }

    camera->setName(cameraModel);
    camera->setLensName(lens);
    camera->setDeclaredFocal(focalLength);
    camera->setScaleFactor35(scaleFactor);
}

void CameraExifIO::write(Camera *camera)
{
    Exiv2::Image::AutoPtr imageExif = Exiv2::ImageFactory::open(mImagePath.toStdString());
    imageExif->readMetadata();
    Exiv2::ExifData &exifData = imageExif->exifData();

    if (!camera->getName().isEmpty())
        exifData["Exif.Image.Model"] = camera->getName().toStdString();
    if (!camera->getLensName().isEmpty())
        exifData["Exif.Photo.LensModel"] = camera->getLensName().toStdString();
    if (camera->getDeclaredFocal() != 0)
        exifData["Exif.Image.FocalLength"] = Exiv2::DoubleValue(camera->getDeclaredFocal());
    if (camera->getScaleFactor35() != 0)
        exifData["Exif.Photo.FocalLengthIn35mmFilm"] = Exiv2::DoubleValue(camera->getDeclaredFocal() * camera->getScaleFactor35());

    imageExif->setExifData(exifData);
    imageExif->writeMetadata();
}

void CameraExifIO::writeCameraName(QString name)
{
    Exiv2::Image::AutoPtr imageExif = Exiv2::ImageFactory::open(mImagePath.toStdString());
    imageExif->readMetadata();
    Exiv2::ExifData &exifData = imageExif->exifData();
    exifData["Exif.Image.Model"] = name.toStdString();
    imageExif->setExifData(exifData);
    imageExif->writeMetadata();
}

void CameraExifIO::writeLensName(QString lensName)
{
    Exiv2::Image::AutoPtr imageExif = Exiv2::ImageFactory::open(mImagePath.toStdString());
    imageExif->readMetadata();
    Exiv2::ExifData &exifData = imageExif->exifData();
    exifData["Exif.Photo.LensModel"] = lensName.toStdString();
    imageExif->setExifData(exifData);
    imageExif->writeMetadata();
}

void CameraExifIO::writeFocalLegth(double focal)
{
    Exiv2::Image::AutoPtr imageExif = Exiv2::ImageFactory::open(mImagePath.toStdString());
    imageExif->readMetadata();
    Exiv2::ExifData &exifData = imageExif->exifData();
    exifData["Exif.Image.FocalLength"] = Exiv2::DoubleValue(focal);
    imageExif->setExifData(exifData);
    imageExif->writeMetadata();
}

void CameraExifIO::writeFocalLegth35(double focal35)
{
    Exiv2::Image::AutoPtr imageExif = Exiv2::ImageFactory::open(mImagePath.toStdString());
    imageExif->readMetadata();
    Exiv2::ExifData &exifData = imageExif->exifData();
    exifData["Exif.Photo.FocalLengthIn35mmFilm"] = Exiv2::DoubleValue(focal35);
    imageExif->setExifData(exifData);
    imageExif->writeMetadata();
}
