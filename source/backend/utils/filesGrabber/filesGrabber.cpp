#include "filesGrabber.h"
#include <QImageReader>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

FilesGrabber::FilesGrabber(QObject *parent) : QObject{parent} {}

void FilesGrabber::getAllImagesAtFolder(const QString& folder) {
    std::vector<QString> images;

    std::vector<std::string> supportedImageFormats;
    for (auto const& i : QImageReader::supportedImageFormats()) {
        supportedImageFormats.push_back("."+i.toStdString());
    }

    if(!fs::is_directory(folder.toStdString())) {
        emit invalidDirectoryPath(folder);
        return;
    }

    for (auto const& dir_entry : fs::directory_iterator(folder.toStdString())) {
        if (dir_entry.is_directory())
            continue;

        fs::path filePath = dir_entry.path();
        bool isSupportedImage = std::find(supportedImageFormats.begin(), supportedImageFormats.end(), filePath.extension().string()) != supportedImageFormats.end();

        if(isSupportedImage)
            images.push_back(QString::fromStdString(filePath.string()));
    }

    emit gottedAllImagesAtFolder(images);
}