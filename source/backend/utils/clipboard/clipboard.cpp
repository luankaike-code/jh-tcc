#include "clipboard.h"
#include <QGuiApplication>

Clipboard* Clipboard::instance = nullptr;

Clipboard::Clipboard() : qClipboard(QGuiApplication::clipboard()) {}

Clipboard* Clipboard::getInstance() {
    if(instance == nullptr) {
        instance = new Clipboard();
    }
    return instance;
}

void Clipboard::copyText(QString text)  {
    qClipboard->setText(text);
}