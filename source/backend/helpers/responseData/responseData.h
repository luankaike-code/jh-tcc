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
