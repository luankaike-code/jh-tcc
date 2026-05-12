#ifndef HOMEWINDOWBACKEND_H
#define HOMEWINDOWBACKEND_H

#include <QObject>
#include <QQmlEngine>
#include "../../enums/sessionModes.h"

class HomeWindowBackend : public QObject {
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QString repositoryPath READ getRepositoryPath WRITE setRepositoryPath REQUIRED)
    Q_PROPERTY(int imageCount READ getImageCount WRITE setImageCount REQUIRED)
    Q_PROPERTY(int imageDelay READ getImageDelay WRITE setImageDelay REQUIRED)
    Q_PROPERTY(SessionModes::Enum sessionMode READ getSessionMode WRITE setSessionMode REQUIRED)

    QString m_repositoryPath;
    int m_imageCount;
    int m_imageDelay;
    SessionModes::Enum m_sessionMode;

    bool propertysValueAreValids();
    void openSessionWindow();

public slots:
    void emitSessionFinished();

public:
    explicit HomeWindowBackend(QObject *parent = nullptr);

    Q_INVOKABLE void startSession();

    QString getRepositoryPath() const;
    int getImageCount() const;
    int getImageDelay() const;
    SessionModes::Enum getSessionMode() const;

    void setRepositoryPath(QString repositoryPath);
    void setImageCount(int imageCount);
    void setImageDelay(int imageDelay);
    void setSessionMode(SessionModes::Enum sessionMode);

signals:
    void sessionStarted();
    void sessionFinished();

    void errorInvalidRepositoryPath();
    void errorEmptyRepositoryPath();
    void errorEmptyImageDelay();
    void errorEmptyImageCount();
};

#endif // HOMEWINDOWBACKEND_H
