#pragma once

#include <cstdio>
#include <atomic>
#include <string>

namespace xtl {

class Log {
public:
    enum class LogLevel {
        debug,
        info,
        notice,
        warning,
        error,
        fatal
    };
public:
    static Log* Instance();

    const std::string& GetLogId() const;
    bool IsMatchedLevel(LogLevel level);
    bool SetLogDir(const std::string& dir);
    void SetLogId(const std::string& id);
    void SetLogLevel(LogLevel level);
    int  Write(const char* buf, int len);

private:
    Log();
    Log(Log&&) = delete;
    Log(const Log&) = delete;
    Log& operator=(Log&&) = delete;
    Log& operator=(const Log&) = delete;
    bool SetLogFile();

private:
    FILE* fp_;
    std::string log_dir_;
    std::string log_file_;
    std::atomic<LogLevel> level_;
};

}
