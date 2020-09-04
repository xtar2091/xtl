#pragma once

#include <string>

namespace xtl {

class StringStreamImpl {
public:
    /**
     * 默认构造函数，缓冲区自动扩展
     */
    StringStreamImpl();

    /**
     * 缓冲区初始化长度为len，自动扩展
     */
    StringStreamImpl(int len);

    /**
     * 使用固定缓冲区，不扩展
     */
    StringStreamImpl(char* buf, int len);

    StringStreamImpl(StringStreamImpl&& other) = delete;
    StringStreamImpl(const StringStreamImpl& other) = delete;
    StringStreamImpl& operator=(StringStreamImpl&& other) = delete;
    StringStreamImpl& operator=(const StringStreamImpl& other) = delete;
    ~StringStreamImpl();

    StringStreamImpl& Append(char c);
    StringStreamImpl& Append(short n);
    StringStreamImpl& Append(unsigned short n);
    StringStreamImpl& Append(int n);
    StringStreamImpl& Append(unsigned int n);
    StringStreamImpl& Append(long n);
    StringStreamImpl& Append(unsigned long n);
    StringStreamImpl& Append(long long n);
    StringStreamImpl& Append(unsigned long long n);
    StringStreamImpl& Append(const char* s);
    StringStreamImpl& Append(const char* s, int len);
    StringStreamImpl& Append(const std::string& s);

    StringStreamImpl* Clone();

    void Clear();
    const char* GetBuffer() const { return buf_; }
    std::string GetString() { return std::string(buf_); }
    int Size() { return static_cast<int>(tail_ - buf_); }

private:
    bool Expand(int min_expand_len);

private:
    int len_;//缓冲区总长度
    char* buf_;//缓冲区指针
    char* tail_;//游标，缓冲区可写的第一个位置
    int expand_threshold_;//扩展阈值，缓冲区长度小于此阈值时翻倍，大于等于此阈值时增长20%
};

}
