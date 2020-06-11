#include "mainwidget.h"

#include <QHBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QThread>
#include <QVBoxLayout>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
  , generator(new Generator())
{
    this->init();
}

MainWidget::~MainWidget()
{

}

QSize MainWidget::sizeHint() const
{
    return QSize(800, 600);
}

void MainWidget::init()
{
    auto thread = new QThread(this);
    generator->moveToThread(thread);
    thread->start();
    connect(this, &MainWidget::destroyed,
            this, [thread](){
        thread->terminate();
        thread->wait();
    });

    auto view = new QGraphicsView;
    view->setScene(new QGraphicsScene(this));
    view->setRenderHint(QPainter::HighQualityAntialiasing);

    auto run = new QPushButton(QIcon(":/icons/start.png"), QStringLiteral(""));
    auto pause = new QPushButton(QIcon(":/icons/pause.png"), QStringLiteral(""));
    auto stop = new QPushButton(QIcon(":/icons/stop.png"), QStringLiteral(""));

    run->setToolTip(tr("run"));
    pause->setToolTip(tr("pause"));
    stop->setToolTip(tr("stop"));

    connect(run, &QPushButton::clicked,
            generator.data(), &Generator::run);
    connect(pause, &QPushButton::clicked,
            generator.data(), &Generator::stop);
    connect(stop, &QPushButton::clicked,
            generator.data(), &Generator::stop);

    connect(stop, &QPushButton::clicked,
            this, [view](){ view->scene()->clear();});

    connect(generator.data(), &Generator::generated,
            this, [=](const QVector<QPoint> points){
        for (auto point : points)
            view->scene()->addEllipse(QRectF(point, QSize(10, 10)), Qt::NoPen, Qt::gray);
    });
    connect(generator.data(), &Generator::runningChanged,
            this, [=](bool running){
        run->setEnabled(!running);
        pause->setEnabled(running);
    });

    emit generator->runningChanged(generator->running());

    auto buttons = new QHBoxLayout;
    buttons->addStretch();
    buttons->addWidget(run);
    buttons->addWidget(pause);
    buttons->addWidget(stop);
    buttons->addStretch();

    auto layout = new QVBoxLayout;
    layout->addWidget(view);
    layout->addLayout(buttons);
    this->setLayout(layout);

    this->setWindowIcon(QIcon(":/icons/logo.png"));
    this->setWindowTitle(tr("Demo application"));
}

