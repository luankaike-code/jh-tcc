#ifndef FILESGRABBER_H
#define FILESGRABBER_H

#include <QObject>
#include <QtQml/qqmlregistration.h>

namespace fs = std::filesystem;

class FilesGrabber : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit FilesGrabber(QObject *parent = nullptr);

    Q_INVOKABLE void getAllImagesAtFolder(const QString& folder);
signals:
    void gottedAllImagesAtFolder(std::vector<QString> images);
    void invalidDirectoryPath(QString path);
};

#endif // FILESGRABBER_H
