#include "getterfiles.h"
#include <iostream>

GetterFiles::GetterFiles(QObject *parent) : QObject{parent} {
    std::cout << "fui criado UwU: " << std::endl;
}

void GetterFiles::helloWorld(const QString& text) {
    std::cout << "hello world: " << text.toStdString() << std::endl;
}