#include "xtl/log/impl/LogStream.h"
#include <pthread.h>
#include <unistd.h>
#include <cstring>
#include <chrono>

namespace xtl {

namespace {

const char* log_level_string[] {
    "debug",
    "info",
    "notice",
    "warning",
    "error",
    "fatal"
};

}

LogStream::LogStream(const char* file, int line, xtl::Log::LogLevel level)
    : line_(line)
    , file_(file)
    , level_str_(nullptr)
    , stream_(nullptr) {
    if (xtl::Log::Instance()->IsMatchedLevel(level)) {
        level_str_ = log_level_string[(int)level];
        stream_ = new StringStream();
        AppendHeader();
    }
}

LogStream::~LogStream() {
    if (stream_) {
        stream_->Append('\n');
        xtl::Log::Instance()->Write(stream_->GetBuffer(), stream_->Size());
        delete stream_;
    }
}

void LogStream::AppendHeader() {
    auto current_time = std::chrono::system_clock::now();
    stream_->AppendCurrentTime("%F %T").Append('.');
    stream_->Append(std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count() % 1000);
    stream_->Append('|').Append(level_str_);
    stream_->Append("|process:").Append(getpid());
    stream_->Append("|thread:").Append(pthread_self());
    stream_->Append("|logid:").Append(xtl::Log::Instance()->GetLogId());
    const char* file_name = strrchr(file_, '/');
    if (!file_name) {
        file_name = strrchr(file_, '\\');
    }
    if (file_name) {
        ++file_name;
        stream_->Append("|").Append(file_name).Append(':').Append(line_);
    }
    stream_->Append('|');
}

}
