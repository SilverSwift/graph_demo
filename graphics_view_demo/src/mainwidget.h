#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "generator.h"

#include <QScopedPointer>
#include <QWidget>

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
    virtual ~MainWidget() override;

    virtual QSize sizeHint() const override;

signals:

private:
    void init();

    QScopedPointer<Generator, QScopedPointerDeleteLater> generator;

};

#endif // MAINWIDGET_H
