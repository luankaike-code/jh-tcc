#include "getterfiles.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

GetterFiles::GetterFiles(QObject *parent) : QObject{parent} {
    std::cout << "fui criado UwU: " << std::endl;
}

void GetterFiles::getAllImagesAtFolder(const QString& folder) {
    std::vector<QString> images;

    for (auto const& dir_entry : fs::directory_iterator(folder.toStdString())) {
        if (dir_entry.is_directory())
            continue;

        images.push_back(QString::fromStdString(dir_entry.path()));
    }

    emit gottedAllImagesAtFolder(images);
}

void GetterFiles::helloWorld(const QString& text) {
    std::cout << "hello world: " << text.toStdString() << std::endl;
}