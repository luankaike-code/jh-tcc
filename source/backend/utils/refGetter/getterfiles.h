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

    Q_INVOKABLE void getAllImagesAtFolder(const QString& folder);
    Q_INVOKABLE static void helloWorld(const QString& text);
signals:
    void gottedAllImagesAtFolder(std::vector<QString> images);
};

#endif // GETTERFILES_H
