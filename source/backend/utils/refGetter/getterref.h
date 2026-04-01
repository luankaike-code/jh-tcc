#ifndef GETTERREF_H
#define GETTERREF_H

#include <QObject>
#include <QtQml/qqmlregistration.h>

class GetterRef : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit GetterRef(QObject *parent = nullptr);

    Q_INVOKABLE static void helloWorld(const QString& text);
};

#endif // GETTERREF_H
