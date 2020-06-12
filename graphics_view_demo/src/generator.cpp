#include "generator.h"

#include <QtMath>
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
    //here comes the magic numbers and dark magic
    //because i've got no idea about what should i really do
    int size = QRandomGenerator::system()->generate() % 50;

    QVector<QPoint> points;
    for (int i = 0 ; i < size; i++){
        auto x = i*10 + (QRandomGenerator::system()->generate() & 0x0F);
        auto y = 20*qSqrt(x) + (QRandomGenerator::system()->generate() & 0x0F);
        points.append(QPoint(x,-y));
    }

    emit generated(points);

}
