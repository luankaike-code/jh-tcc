#include "sessionControlWindowState.h"

#include "../../sessionControlWindowBackend.h"
#include <iostream>

SessionControlWindowState::SessionControlWindowState(SessionControlWindowBackend* sessionControlWindowBackend) : QObject{sessionControlWindowBackend} {
    connect(sessionControlWindowBackend, &SessionControlWindowBackend::delayImageChanged, this, [this, sessionControlWindowBackend](){
        this->delayImageChanged(sessionControlWindowBackend);
    });

    connect(sessionControlWindowBackend, &SessionControlWindowBackend::roadmapDurationChanged, this, [this, sessionControlWindowBackend](){
        this->roadmapDurationChanged(sessionControlWindowBackend);
    });
}

bool SessionControlWindowState::isSessionFinished(const int& currentImageIndex, const int& countImage) {
    return currentImageIndex > countImage;
}

void SessionControlWindowState::delayImageChanged(SessionControlWindowBackend* sessionControlWindowBackend) {}

void SessionControlWindowState::roadmapDurationChanged(SessionControlWindowBackend* sessionControlWindowBackend) {}

void SessionControlWindowState::nextButtonPressed(SessionControlWindowBackend* sessionControlWindowBackend) {
    sessionControlWindowBackend->resetTimer();
    sessionControlWindowBackend->goToNextImage();
}

void SessionControlWindowState::preventButtonPressed(SessionControlWindowBackend* sessionControlWindowBackend) {
    sessionControlWindowBackend->resetTimer();
    sessionControlWindowBackend->goToPreventImage();
}

void SessionControlWindowState::intervalTimerFinish(SessionControlWindowBackend* sessionControlWindowBackend) {
    sessionControlWindowBackend->setCurrentImageIndex(sessionControlWindowBackend->getCurrentImageIndex()+1);

    if(isSessionFinished(sessionControlWindowBackend->getCurrentImageIndex(), sessionControlWindowBackend->getImagesCount()))
        sessionControlWindowBackend->sessionFinish();

    sessionControlWindowBackend->goToNextImage();
}
