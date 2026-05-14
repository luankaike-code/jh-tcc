#include "SCWSInfinityImages.h"

#include "../../sessionControlWindowBackend.h"

SCWSInfinityImages::SCWSInfinityImages(SessionControlWindowBackend* sessionControlWindowBackend) {
    sessionControlWindowBackend->startTimer();
}

bool SCWSInfinityImages::isSessionFinished(const int& currentImageIndex, const int& countImage) {
    return false;
}