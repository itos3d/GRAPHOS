#ifndef CAMERAEXIFIO_H
#define CAMERAEXIFIO_H

#include "Camera.h"

namespace PW{

class CameraExifIO
{
public:
    CameraExifIO(QString imagePath = "");
    void setImagePath(QString imagePath);

    void read(Camera *camera);
    void write(Camera *camera);
    void writeCameraName(QString name);
    void writeLensName(QString lensName);
    void writeFocalLegth(double focal);
    void writeFocalLegth35(double focal35);

private:
    QString mImagePath;

};

}
#endif // CAMERAEXIFIO_H
