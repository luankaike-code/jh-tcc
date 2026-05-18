#include "sessionModeReader.h"

SessionModeReader::SessionModeReader(QObject* parent) : QObject(parent) {}

bool SessionModeReader::hasTimerLimit(const SessionModes::Enum& sessionModeValue) {
    return sessionModeValue != SessionModes::Enum::InfinityTime && sessionModeValue != SessionModes::Enum::Sandbox;
}

bool SessionModeReader::hasImagesLimit(const SessionModes::Enum& sessionModeValue) {
    return sessionModeValue != SessionModes::Enum::InfinityImages && sessionModeValue != SessionModes::Enum::Sandbox;
}

bool SessionModeReader::hasRoadmap(const SessionModes::Enum& sessionModeValue) {
    return sessionModeValue == SessionModes::Enum::Classroom;
}