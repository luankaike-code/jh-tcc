#include "getterfiles.h"
#include <filesystem>

namespace fs = std::filesystem;

GetterFiles::GetterFiles(QObject *parent) : QObject{parent} {}

void GetterFiles::getAllImagesAtFolder(const QString& folder) {
    std::vector<QString> images;

    if(!fs::is_directory(folder.toStdString())) {
        emit invalidDirectoryPath(folder);
        return;
    }

    for (auto const& dir_entry : fs::directory_iterator(folder.toStdString())) {
        if (dir_entry.is_directory())
            continue;

        images.push_back(QString::fromStdString(dir_entry.path().string()));
    }

    emit gottedAllImagesAtFolder(images);
}