/*
 * SPDX-FileCopyrightText: 2026 luankaike-code <https://github.com/luankaike-code>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include <QObject>
#include <QQmlEngine>
#include <QClipboard>

class Clipboard {
    QClipboard* qClipboard;
    static Clipboard* instance;

    Clipboard();
public:
    Clipboard(Clipboard& other) = delete;
    void operator=(const Clipboard& other) = delete;

    static Clipboard* getInstance();
    void copyText(const QString& text);
};

#endif // CLIPBOARD_H
