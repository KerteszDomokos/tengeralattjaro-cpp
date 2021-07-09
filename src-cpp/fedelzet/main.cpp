#define PY_SSIZE_T_CLEAN

#include <QApplication>

#include <QCamera>
#include <QCameraImageCapture>
#include <QCameraInfo>
#include <QImage>
#include <iostream>



QByteArray device = QCamera::availableDevices()[0];
        QCamera camera(device);
        QVideoWidget surface;
        surface.resize(320, 240);
        camera.setViewfinder(&surface);


int main()
{
    QCamera camera(device);
    QImage img = camera.getQImage(); //take the image buffer of camera
    img.save("test.jpg");
    return 0;
}

