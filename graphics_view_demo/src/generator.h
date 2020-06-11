#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>
#include <QPoint>

class Generator : public QObject
{
    Q_OBJECT
public:
    explicit Generator(QObject *parent = nullptr);
    virtual ~Generator() override;

    Q_PROPERTY(bool running READ running NOTIFY runningChanged);

    bool running() const;

public slots:
    void run();
    void stop();

signals:
    void generated(const QVector<QPoint> points);
    void runningChanged(bool);

private:
    void timerEvent(QTimerEvent *event) override;

    int timerId = idle;
    static constexpr int idle = 0;
};

#endif // GENERATOR_H
