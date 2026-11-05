// SPDX-FileCopyrightText: 2026 luankaike-code <https://github.com/luankaike-code>
//
// SPDX-License-Identifier: GPL-3.0-or-later

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

void Clipboard::copyText(const QString& text)  {
    qClipboard->setText(text);
}