#include "RCQuickWidget.h"
#include <QDebug>
#include <QQmlContext>
#include <QQmlEngine>

RCQuickWidget::RCQuickWidget(QWidget* parent):
    QQuickWidget(parent)
{
    rootContext()->engine()->addImportPath(QStringLiteral("qrc:/qml"));
}

bool RCQuickWidget::setSource(const QUrl& qmlUrl)
{
    QQuickWidget::setSource(qmlUrl);

    if(status() != Ready)
    {
        qDebug() << "qml source error";
        return false;
    }
    return true;
}
