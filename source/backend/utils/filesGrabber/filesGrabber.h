#ifndef FILESGRABBER_H
#define FILESGRABBER_H

#include <QObject>
#include <QtQml/qqmlregistration.h>

namespace fs = std::filesystem;

class FilesGrabber {
public:
    FilesGrabber() = delete;
    FilesGrabber(const FilesGrabber&) = delete;

    static QStringList getAllImagesAtFolder(const QString& folder);
};

#endif // FILESGRABBER_H
