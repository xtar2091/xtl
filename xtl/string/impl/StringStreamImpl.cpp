#include "xtl/string/impl/StringStreamImp.h"

#include <cstring>

namespace xtl {

StringStreamImpl::StringStreamImpl() {
    len_ = 1024;
    buf_ = new char[len_];
    tail_ = buf_;
    *tail_ = '\0';
    expand_threshold_ = 1024 * 1024;
}

StringStreamImpl::StringStreamImpl(int len) {
    len_ = len;
    buf_ = new char[len_];
    tail_ = buf_;
    *tail_ = '\0';
    expand_threshold_ = 1024 * 1024;
}

StringStreamImpl::StringStreamImpl(char* buf, int len) {
    len_ = len;
    buf_ = buf;
    tail_ = buf_;
    *tail_ = '\0';
    expand_threshold_ = 0;
}

StringStreamImpl::~StringStreamImpl() {
    if (expand_threshold_ > 0) {
        delete []buf_;
    }
}

StringStreamImpl& StringStreamImpl::Append(char c) {
    int left = static_cast<int>(len_ - (tail_ - buf_));
    if (left <= 1) {
        if (!Expand(0)) {
            return *this;
        }
    }
    *tail_++ = c;
    *tail_ = '\0';
    return *this;
}

StringStreamImpl& StringStreamImpl::Append(short n) {
    if (n < 0) {
        Append('-');
        n = -n;
    }
    return Append(static_cast<unsigned long long>(n));
}

StringStreamImpl& StringStreamImpl::Append(unsigned short n) {
    return Append(static_cast<unsigned long long>(n));
}

StringStreamImpl& StringStreamImpl::Append(int n) {
    if (n < 0) {
        Append('-');
        n = -n;
    }
    return Append(static_cast<unsigned long long>(n));
}

StringStreamImpl& StringStreamImpl::Append(unsigned int n) {
    return Append(static_cast<unsigned long long>(n));
}

StringStreamImpl& StringStreamImpl::Append(long n) {
    if (n < 0) {
        Append('-');
        n = -n;
    }
    return Append(static_cast<unsigned long long>(n));
}

StringStreamImpl& StringStreamImpl::Append(unsigned long n) {
    return Append(static_cast<unsigned long long>(n));
}

StringStreamImpl& StringStreamImpl::Append(long long n) {
    if (n < 0) {
        Append('-');
        n = -n;
    }
    return Append(static_cast<unsigned long long>(n));
}

StringStreamImpl& StringStreamImpl::Append(unsigned long long n) {
    if (n == 0) {
        return Append('0');
    }
    int count = 0;//nµÄÎ»Êý
    int num = n % 10;
    int left = static_cast<int>(len_ - (tail_ - buf_));
    while (n) {
        if (left <= 1) {
            if (!Expand(0)) {
                return *this;
            }
            left = static_cast<int>(len_ - (tail_ - buf_));
        }
        *tail_++ = num + '0';
        left--;
        count++;
        n /= 10;
        num = n % 10;
    }
    *tail_ = '\0';
    char c;
    char* tail = tail_ - 1;
    char* head = tail_ - count;
    while (head < tail) {
        c = *head;
        *head = *tail;
        *tail = c;
        ++head;
        --tail;
    }
    return *this;
}

StringStreamImpl& StringStreamImpl::Append(const char* s) {
    Append(s, static_cast<int>(strlen(s)));
    return *this;
}

StringStreamImpl& StringStreamImpl::Append(const char* s, int slen) {
    int left = static_cast<int>(len_ - (tail_ - buf_));
    if (left <= slen) {
        if (!Expand(slen)) {
            return *this;
        }
    }
    memcpy(tail_, s, slen);
    tail_ += slen;
    *tail_ = '\0';
    return *this;
}

StringStreamImpl& StringStreamImpl::Append(const std::string& s) {
    Append(s.c_str(), static_cast<int>(s.size()));
    return *this;
}

bool StringStreamImpl::Expand(int min_expand_len) {
    if (expand_threshold_ == 0) {
        return false;
    }
    int new_len = len_ + min_expand_len;
    if (new_len < expand_threshold_) {
        new_len += new_len;
    }
    else {
        new_len += (new_len * 20 / 100);
    }
    int total_size = static_cast<int>(tail_ - buf_);
    char* new_buf = new char[new_len];
    memcpy(new_buf, buf_, total_size);
    delete[]buf_;
    buf_ = new_buf;
    tail_ = buf_ + total_size;
    len_ = new_len;
    return true;
}

StringStreamImpl* StringStreamImpl::Clone() {
    int total_size = static_cast<int>(tail_ - buf_);
    StringStreamImpl* new_impl = new StringStreamImpl(len_);
    memcpy(new_impl->buf_, buf_, total_size);
    new_impl->tail_ = new_impl->buf_ + total_size;
    *new_impl->tail_ = '\0';
    return new_impl;
}

void StringStreamImpl::Clear() {
    tail_ = buf_;
    *tail_ = '\0';
}

}
