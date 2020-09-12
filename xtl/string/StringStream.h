#pragma once

#include <string>

namespace xtl {

class StringStreamImpl;

class StringStream {
public:
    /**
     * 默认构造函数，缓冲区自动扩展
     */
    StringStream();

    /**
     * 缓冲区初始化长度为len，自动扩展
     */
    StringStream(int len);

    /**
     * 使用固定缓冲区，不扩展
     */
    StringStream(char* buf, int len);

    StringStream(StringStream&& other);
    StringStream(const StringStream& other);
    StringStream& operator=(StringStream&& other);
    StringStream& operator=(const StringStream& other);
    ~StringStream();

    StringStream& operator<<(char c);
    StringStream& operator<<(short n);
    StringStream& operator<<(unsigned short n);
    StringStream& operator<<(int n);
    StringStream& operator<<(unsigned int n);
    StringStream& operator<<(long n);
    StringStream& operator<<(unsigned long n);
    StringStream& operator<<(long long n);
    StringStream& operator<<(unsigned long long n);
    StringStream& operator<<(const char* s);
    StringStream& operator<<(const std::string& s);

    StringStream& Append(char c);
	StringStream& Append(short n);
	StringStream& Append(unsigned short n);
	StringStream& Append(int n);
	StringStream& Append(unsigned int n);
	StringStream& Append(long n);
	StringStream& Append(unsigned long n);
	StringStream& Append(long long n);
	StringStream& Append(unsigned long long n);
	StringStream& Append(const char* s);
	StringStream& Append(const std::string& s);

    StringStream& AppendCurrentTime(const char* fmt);

    void Clear();
	const char* GetBuffer() const;
	std::string GetString();
	int Size() const;

private:
    StringStreamImpl* impl_;
};

}
