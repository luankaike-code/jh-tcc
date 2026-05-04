#include "clipboard.h"
#include <QGuiApplication>

Clipboard::Clipboard(QObject *parent) : QObject{parent}, qClipboard(QGuiApplication::clipboard()) {}

void Clipboard::copyText() const {
    qClipboard->setText(m_text);
}

QString Clipboard::getText() const {
    return m_text;
}

void Clipboard::setText(QString text) {
    m_text = text;
    textChanged();
}