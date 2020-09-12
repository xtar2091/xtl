#include "xtl/log/impl/Log.h"
#include <memory>

namespace xtl {

namespace {

thread_local std::string local_log_id;

}

Log::Log() {
    fp_ = nullptr;
    level_.store(Log::LogLevel::notice);
}

Log* Log::Instance() {
    static Log log;
    return &log;
}

const std::string& Log::GetLogId() const {
    return local_log_id;
}

bool Log::IsMatchedLevel(LogLevel level) {
    return level >= level_.load();
}

bool Log::SetLogDir(const std::string& dir) {
    log_dir_ = dir;
    return SetLogFile();
}

void Log::SetLogId(const std::string& id) {
    local_log_id = id;
}

void Log::SetLogLevel(Log::LogLevel level) {
    if (level >= Log::LogLevel::debug && level <= Log::LogLevel::fatal) {
        level_.store(level);
    }
}

bool Log::SetLogFile() {
    if (log_dir_.empty()) {
        log_dir_ = "./";
    }
    if (log_dir_.back() != '/' && log_dir_.back() != '\\') {
        log_dir_.push_back('/');
    }
    log_file_ = log_dir_ + "log.log";
    fp_ = fopen(log_file_.c_str(), "a+");
    return fp_ != NULL;
}

int Log::Write(const char* buf, int len) {
    return static_cast<int>(fwrite(buf, 1, static_cast<size_t>(len), fp_));
}

}
