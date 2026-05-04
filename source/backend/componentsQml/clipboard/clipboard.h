#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include <QObject>
#include <QQmlEngine>
#include <QClipboard>

class Clipboard : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QString text READ getText WRITE setText NOTIFY textChanged)
    QString m_text;

    QClipboard* qClipboard;
public:
    explicit Clipboard(QObject *parent = nullptr);
    Q_INVOKABLE void copyText() const;

    QString getText() const;

    void setText(QString text);
signals:
    void textChanged();
};

#endif // CLIPBOARD_H
