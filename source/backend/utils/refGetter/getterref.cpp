#include "getterref.h"
#include <iostream>

GetterRef::GetterRef(QObject *parent) : QObject{parent} {
    std::cout << "fui criado UwU: " << std::endl;
}

void GetterRef::helloWorld(const QString& text) {
    std::cout << "hello world: " << text.toStdString() << std::endl;
}