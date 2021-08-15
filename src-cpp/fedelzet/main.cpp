



#include <QtMultimedia/QCamera>
#include <QtMultimedia/QCameraImageCapture>
#include <QtMultimedia/QCameraInfo>
#include <QImage>
#include <iostream>
#include <QDebug>
#include <QList>

bool checkCameraAvailability()
{
    if (QCameraInfo::availableCameras().count() > 0)
        return true;
    else
        return false;
}


int main()
{
    const QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
qDebug()<<cameras;
    QCamera camera(cameras[0]);
    QCameraImageCapture imCap(camera);
    camera.setCaptureMode(QCamera::CaptureStillImage);
    camera.start();
    camera.searchAndLock();
    imCap.capture();
    camera.unlock();



    QImage img = imCap.getQImage(); //take the image buffer of camera
    img.save("test.jpg");
    return 0;
}
