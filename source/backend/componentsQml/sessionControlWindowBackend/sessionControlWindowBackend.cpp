#include "sessionControlWindowBackend.h"
#include "../../helpers/sessionModeReader.h"

SessionControlWindowBackend::SessionControlWindowBackend(QObject *parent) : QObject{parent} {
    setCurrentImageIndex(1);
}

SessionModes::Enum SessionControlWindowBackend::getSessionModes() const {
    return m_sessionModes;
}

bool SessionControlWindowBackend::getHasTimerLimit() const {
    return m_hasTimerLimit;
}

bool SessionControlWindowBackend::getHasImagesLimit() const {
    return m_hasImagesLimit;
}

int SessionControlWindowBackend::getImagesCount() const {
    return m_currentImageIndex;
}

int SessionControlWindowBackend::getCurrentImageIndex() const {
    return m_currentImageIndex;
}

void SessionControlWindowBackend::setSessionModes(SessionModes::Enum sessionModes) {
    setHasTimerLimit(SessionModeReader::hasTimerLimit(sessionModes));
    setHasImagesLimit(SessionModeReader::hasImagesLimit(sessionModes));

    m_sessionModes = sessionModes;
    sessionModesChanged();
}

void SessionControlWindowBackend::setHasTimerLimit(bool hasTimerLimit) {
    m_hasTimerLimit = hasTimerLimit;
    hasTimerLimitChanged();
}

void SessionControlWindowBackend::setHasImagesLimit(bool hasImagesLimit) {
    m_hasImagesLimit = hasImagesLimit;
    hasImagesLimitChanged();
}

void SessionControlWindowBackend::setImagesCount(int imagesCount) {
    m_imagesCount = imagesCount;
}

void SessionControlWindowBackend::setCurrentImageIndex(int currentImageIndex) {
    m_currentImageIndex = currentImageIndex;
    currentImageIndexChanged();
}
