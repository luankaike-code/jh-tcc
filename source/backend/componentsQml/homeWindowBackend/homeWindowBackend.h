#ifndef HOMEWINDOWBACKEND_H
#define HOMEWINDOWBACKEND_H

#include <QObject>
#include <QQmlEngine>
#include <utility>
#include "../../enums/sessionModes.h"
#include "../../helpers/responseData/responseData.h"

class HomeWindowBackend : public QObject {
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QString repositoryPath READ getRepositoryPath WRITE setRepositoryPath REQUIRED)
    Q_PROPERTY(int imageCount READ getImageCount WRITE setImageCount REQUIRED)
    Q_PROPERTY(int imageDelay READ getImageDelay WRITE setImageDelay REQUIRED)
    Q_PROPERTY(int roadmapDuration READ getRoadmapDuration WRITE setRoadmapDuration REQUIRED)
    Q_PROPERTY(SessionModes::Enum sessionMode READ getSessionMode WRITE setSessionMode NOTIFY sessionModeChanged REQUIRED)

    QString m_repositoryPath;
    int m_imageCount;
    int m_imageDelay;
    int m_roadmapDuration;
    SessionModes::Enum m_sessionMode;

    bool propertysValueAreValids();
    void openSessionWindow();
    ResponseData<QStringList> tryGetAllImagesAtRepositoryPath();

public slots:
    void emitSessionFinished();

public:
    explicit HomeWindowBackend(QObject* parent = nullptr);

    Q_INVOKABLE void startSession();

    const QString& getRepositoryPath() const;
    const int& getImageCount() const;
    const int& getImageDelay() const;
    const SessionModes::Enum& getSessionMode() const;
    const int& getRoadmapDuration() const;

    void setRoadmapDuration(const int& roadmapDuration);
    void setRepositoryPath(const QString& repositoryPath);
    void setImageCount(const int& imageCount);
    void setImageDelay(const int& imageDelay);
    void setSessionMode(const SessionModes::Enum& sessionMode);

signals:
    void sessionModeChanged();

    void sessionStarted();
    void sessionFinished();

    void errorInvalidRepositoryPath();
    void errorEmptyRepositoryPath();
    void errorEmptyImageDelay();
    void errorEmptyImageCount();
    void errorEmptyRoadmapDuration();
    void errorNoneImageFound();
};

#endif // HOMEWINDOWBACKEND_H
