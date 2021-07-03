#include <QThread>

#ifndef KOMMUNIKACIO_H
#define KOMMUNIKACIO_H


class Kommunikacio : public QThread
{
    Q_OBJECT
public:
    Kommunikacio();
private:
    void run();
};

#endif // KOMMUNIKACIO_H
