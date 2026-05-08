#include "filesGrabber.h"
#include <QImageReader>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

FilesGrabber::FilesGrabber() {}

QStringList FilesGrabber::getAllImagesAtFolder(const QString& folder) {
    QStringList images;

    QStringList supportedImageFormats;
    for (auto const& i : QImageReader::supportedImageFormats()) {
        supportedImageFormats.push_back("."+i);
    }

    for (auto const& dir_entry : fs::directory_iterator(folder.toStdString())) {
        if (dir_entry.is_directory())
            continue;

        fs::path filePath = dir_entry.path();
        QString qfilePath = QString::fromStdString(dir_entry.path().extension().string());
        bool isSupportedImage = std::find(supportedImageFormats.begin(), supportedImageFormats.end(), qfilePath) != supportedImageFormats.end();

        if(isSupportedImage)
            images.push_back(QString::fromStdString(filePath.string()));
    }

    return images;
}