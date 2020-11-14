#ifndef RCQMLWIDGETHOLDER_H
#define RCQMLWIDGETHOLDER_H

#include <QWidget>
#include "ui_RCQmlWidgetHolder.h"
#include <QQmlContext>
#include <QQuickItem>
#include <QQmlEngine>
#include <QQmlApplicationEngine>

#include "RCQuickWidget.h"

namespace Ui {
class RCQmlWidgetHolder;
}

class RCQmlWidgetHolder : public QWidget
{
    Q_OBJECT

public:
    RCQmlWidgetHolder(QWidget *parent = nullptr);
    ~RCQmlWidgetHolder();

    QQmlContext* getRootContext(void);
    QQuickItem* getRootObject(void);
    QQmlEngine* getEngine(void);
    QQmlApplicationEngine* getApplicationEngine(void);

    void setContextPropertyObject(const QString& name, QObject* object);

    bool setSource(const QUrl& qmlUrl);

private:
    Ui::RCQmlWidgetHolder ui;
    QQmlApplicationEngine* engine;

};

#endif // RCQMLWIDGETHOLDER_H
