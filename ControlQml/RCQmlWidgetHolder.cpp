#include "RCQmlWidgetHolder.h"


RCQmlWidgetHolder::RCQmlWidgetHolder(QWidget *parent) :
    QWidget(parent)
{
    ui.setupUi(this);

    engine = new QQmlApplicationEngine;

    ui.qmlWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
}

RCQmlWidgetHolder::~RCQmlWidgetHolder()
{

}

QQmlApplicationEngine* RCQmlWidgetHolder::getApplicationEngine(void)
{
    return engine;
}

void RCQmlWidgetHolder::setContextPropertyObject(const QString& name, QObject* object)
{
    ui.qmlWidget->rootContext()->setContextProperty(name,object);
}

QQmlContext* RCQmlWidgetHolder::getRootContext(void)
{
    return ui.qmlWidget->rootContext();
}

QQuickItem* RCQmlWidgetHolder::getRootObject(void)
{
    return ui.qmlWidget->rootObject();
}

QQmlEngine* RCQmlWidgetHolder::getEngine(void)
{
    return ui.qmlWidget->engine();
}

bool RCQmlWidgetHolder::setSource(const QUrl& qmlUrl)
{
    return ui.qmlWidget->setSource(qmlUrl);
}
