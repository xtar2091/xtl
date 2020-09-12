#pragma once

#include "xtl/log/impl/Log.h"
#include "xtl/string/StringStream.h"

namespace xtl {

class LogStream {
public:
    LogStream(const char* file, int line, xtl::Log::LogLevel level);
    LogStream(LogStream&&) = delete;
    LogStream(const LogStream&) = delete;
    LogStream& operator=(LogStream&&) = delete;
    LogStream& operator=(const LogStream&) = delete;
    ~LogStream();

    template<class T>
    LogStream& operator<<(const T& val) {
        if (stream_) {
            stream_->Append(val);
        }
        return *this;
    }

private:
    void AppendHeader();

private:
    int line_;
    const char* file_;
    const char* level_str_;
    StringStream* stream_;
};

}
