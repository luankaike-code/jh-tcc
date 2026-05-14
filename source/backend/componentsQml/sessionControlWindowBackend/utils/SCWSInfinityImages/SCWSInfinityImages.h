#ifndef SCWSINFINITYIMAGES_H
#define SCWSINFINITYIMAGES_H

#include "../sessionControlWindowState/sessionControlWindowState.h"

class SessionControlWindowBackend;

class SCWSInfinityImages : public SessionControlWindowState {
public:
    SCWSInfinityImages(SessionControlWindowBackend* sessionControlWindowBackend);

    bool isSessionFinished(const int& currentImageIndex, const int& countImage) override;
};

#endif // SCWSINFINITYIMAGES_H
