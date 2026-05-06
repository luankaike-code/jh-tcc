#ifndef HOMEWINDOWBACKEND_H
#define HOMEWINDOWBACKEND_H

#include <QObject>
#include <QQmlEngine>

class HomeWindowBackend : public QObject {
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QString repositoryPath READ getRepositoryPath WRITE setRepositoryPath REQUIRED)
    Q_PROPERTY(int imageCount READ getImageCount WRITE setImageCount REQUIRED)
    Q_PROPERTY(int imageDelay READ getImageDelay WRITE setImageDelay REQUIRED)

    QString m_repositoryPath;
    int m_imageCount;
    int m_imageDelay;

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

    void setRepositoryPath(QString repositoryPath);
    void setImageCount(int imageCount);
    void setImageDelay(int imageDelay);

signals:
    void sessionStarted();
    void sessionFinished();

    void errorInvalidRepositoryPath();
    void errorEmptyRepositoryPath();
    void errorEmptyImageDelay();
    void errorEmptyImageCount();
};

#endif // HOMEWINDOWBACKEND_H
