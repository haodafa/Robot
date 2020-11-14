 #ifndef RCQUICKWIDGET_H
#define RCQUICKWIDGET_H

#include <QQuickWidget>

class RCQuickWidget:public QQuickWidget
{
    Q_OBJECT
public:
    RCQuickWidget(QWidget* parent = NULL);

    bool setSource(const QUrl& qmlUrl);
};

#endif // RCQUICKWIDGET_H
