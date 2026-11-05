/*
 * SPDX-FileCopyrightText: 2026 luankaike-code <https://github.com/luankaike-code>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef RESPONSEDATA_H
#define RESPONSEDATA_H

template<typename T>
class ResponseData {
public:
    enum Status {
        OK,
        ERROR_NOT_HANDLER,
        ERROR_HANDLER
    };

    Status status;
    T data;

    ResponseData() = default;
    inline ResponseData(Status status, T data) : status(status), data(data) {};
};

#endif // RESPONSEDATA_H
