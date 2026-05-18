#ifndef SESSIONCONTROLWINDOWSTATE_H
#define SESSIONCONTROLWINDOWSTATE_H

#include <QObject>

class SessionControlWindowBackend;

class SessionControlWindowState : public QObject {
    Q_OBJECT

protected:
    void makeConnectionToAutoUpdateTimer(SessionControlWindowBackend* sessionControlWindowBackend);
public:
    SessionControlWindowState(SessionControlWindowBackend* sessionControlWindowBackend = nullptr);
    virtual ~SessionControlWindowState() = default;

    virtual void timerUpdated(SessionControlWindowBackend* sessionControlWindowBackend);
    virtual void nextButtonPressed(SessionControlWindowBackend* sessionControlWindowBackend);
    virtual void preventButtonPressed(SessionControlWindowBackend* sessionControlWindowBackend);
    virtual void intervalTimerFinish(SessionControlWindowBackend* sessionControlWindowBackend);
    virtual bool isSessionFinished(const int& currentImageIndex, const int& countImage);
};

#endif // SESSIONCONTROLWINDOWSTATE_H
