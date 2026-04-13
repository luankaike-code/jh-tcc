#ifndef GETTERFILES_H
#define GETTERFILES_H

#include <QObject>
#include <QtQml/qqmlregistration.h>

namespace fs = std::filesystem;

class GetterFiles : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit GetterFiles(QObject *parent = nullptr);

    Q_INVOKABLE void getAllImagesAtFolder(const QString& folder);
signals:
    void gottedAllImagesAtFolder(std::vector<QString> images);
    void invalidDirectoryPath(QString path);
};

#endif // GETTERFILES_H
