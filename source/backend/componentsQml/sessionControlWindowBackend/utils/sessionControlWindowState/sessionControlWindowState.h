#ifndef SESSIONCONTROLWINDOWSTATE_H
#define SESSIONCONTROLWINDOWSTATE_H

#include <QObject>

class SessionControlWindowBackend;

class SessionControlWindowState : public QObject {
    Q_OBJECT

public:
    SessionControlWindowState(SessionControlWindowBackend* sessionControlWindowBackend = nullptr);
    virtual ~SessionControlWindowState() = default;

    virtual void nextButtonPressed(SessionControlWindowBackend* sessionControlWindowBackend);
    virtual void preventButtonPressed(SessionControlWindowBackend* sessionControlWindowBackend);
    virtual void intervalTimerFinish(SessionControlWindowBackend* sessionControlWindowBackend);
    virtual bool isSessionFinished(const int& currentImageIndex, const int& countImage);

    virtual void delayImageChanged(SessionControlWindowBackend* sessionControlWindowBackend);
    virtual void roadmapDurationChanged(SessionControlWindowBackend* sessionControlWindowBackend);
};

#endif // SESSIONCONTROLWINDOWSTATE_H
