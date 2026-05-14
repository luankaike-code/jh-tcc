#ifndef SESSIONCONTROLWINDOWSTATE_H
#define SESSIONCONTROLWINDOWSTATE_H

class SessionControlWindowBackend;

class SessionControlWindowState {
public:
    SessionControlWindowState();
    virtual ~SessionControlWindowState() = default;

    virtual void nextButtonPressed(SessionControlWindowBackend* sessionControlWindowBackend);
    virtual void preventButtonPressed(SessionControlWindowBackend* sessionControlWindowBackend);
    virtual void intervalTimerFinish(SessionControlWindowBackend* sessionControlWindowBackend);
    virtual bool isSessionFinished(const int& currentImageIndex, const int& countImage);
};

#endif // SESSIONCONTROLWINDOWSTATE_H
