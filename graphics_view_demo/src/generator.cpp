#include "generator.h"

#include <QRandomGenerator>

Generator::Generator(QObject *parent) : QObject(parent)
{

}

Generator::~Generator()
{

}

bool Generator::running() const
{
    return (timerId != idle);
}

void Generator::run()
{
    if (this->running())
        return;

    timerId = this->startTimer(1000);
    emit runningChanged(this->running());
}

void Generator::stop()
{
    if (!this->running())
        return;

    this->killTimer(timerId);
    timerId = idle;
    emit runningChanged(this->running());
}

void Generator::timerEvent(QTimerEvent* )
{
    int size = QRandomGenerator::system()->generate() % 5;

    QVector<QPoint> points;
    for (int i = 0 ; i < size; i++){
        quint8 x = QRandomGenerator::system()->generate() & 0xFF;
        quint8 y = QRandomGenerator::system()->generate() & 0xFF;
        points.append(QPoint(x, y));
    }

    emit generated(points);

}
