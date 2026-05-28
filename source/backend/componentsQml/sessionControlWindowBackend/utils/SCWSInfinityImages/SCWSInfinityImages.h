#ifndef SCWSINFINITYIMAGES_H
#define SCWSINFINITYIMAGES_H

#include "../sessionControlWindowState/sessionControlWindowState.h"

class SessionControlWindowBackend;

class SCWSInfinityImages : public SessionControlWindowState {
public:
    SCWSInfinityImages(SessionControlWindowBackend* sessionControlWindowBackend);

    void delayImageChanged(SessionControlWindowBackend* sessionControlWindowBackend) override;
    const bool isSessionFinished(SessionControlWindowBackend* sessionControlWindowBackend) const override;
    void startSession(SessionControlWindowBackend* sessionControlWindowBackend) override;
};

#endif // SCWSINFINITYIMAGES_H
