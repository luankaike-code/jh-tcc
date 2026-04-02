#ifndef GETTERFILES_H
#define GETTERFILES_H

#include <QObject>
#include <QtQml/qqmlregistration.h>

class GetterFiles : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit GetterFiles(QObject *parent = nullptr);

    Q_INVOKABLE static void helloWorld(const QString& text);
};

#endif // GETTERFILES_H
