#include "xtl/string/StringStream.h"
#include "xtl/string/impl/StringStreamImp.h"

namespace xtl {

StringStream::StringStream() {
    impl_ = new StringStreamImpl();
}

StringStream::StringStream(int len) {
    impl_ = new StringStreamImpl(len);
}

StringStream::StringStream(char* buf, int len) {
    impl_ = new StringStreamImpl(buf, len);
}

StringStream::StringStream(StringStream&& other) {
    impl_ = other.impl_;
    other.impl_ = nullptr;
}

StringStream::StringStream(const StringStream& other) {
    impl_ = other.impl_->Clone();
}

StringStream& StringStream::operator=(StringStream&& other) {
    if (impl_) {
        delete impl_;
        impl_ = nullptr;
    }
    impl_ = other.impl_;
    other.impl_ = nullptr;
    return *this;
}

StringStream& StringStream::operator=(const StringStream& other) {
    if (impl_) {
        delete impl_;
        impl_ = nullptr;
    }
    impl_ = other.impl_->Clone();
    return *this;
}

StringStream::~StringStream() {
    if (impl_) {
        delete impl_;
        impl_ = nullptr;
    }
}

StringStream& StringStream::operator<<(char c) {
    impl_->Append(c);
    return *this;
}

StringStream& StringStream::operator<<(short n) {
    impl_->Append(n);
    return *this;
}

StringStream& StringStream::operator<<(unsigned short n) {
    impl_->Append(n);
    return *this;
}

StringStream& StringStream::operator<<(int n) {
    impl_->Append(n);
    return *this;
}

StringStream& StringStream::operator<<(unsigned int n) {
    impl_->Append(n);
    return *this;
}

StringStream& StringStream::operator<<(long n) {
    impl_->Append(n);
    return *this;
}

StringStream& StringStream::operator<<(unsigned long n) {
    impl_->Append(n);
    return *this;
}

StringStream& StringStream::operator<<(long long n) {
    impl_->Append(n);
    return *this;
}

StringStream& StringStream::operator<<(unsigned long long n) {
    impl_->Append(n);
    return *this;
}

StringStream& StringStream::operator<<(const char* s) {
    impl_->Append(s);
    return *this;
}

StringStream& StringStream::operator<<(const std::string& s) {
    impl_->Append(s);
    return *this;
}

StringStream& StringStream::Append(char c) {
		impl_->Append(c);
		return *this;
	}

	StringStream& StringStream::Append(short n) {
		impl_->Append(n);
		return *this;
	}

	StringStream& StringStream::Append(unsigned short n) {
		impl_->Append(n);
		return *this;
	}

	StringStream& StringStream::Append(int n) {
		impl_->Append(n);
		return *this;
	}

	StringStream& StringStream::Append(unsigned int n) {
		impl_->Append(n);
		return *this;
	}

	StringStream& StringStream::Append(long n) {
		impl_->Append(n);
		return *this;
	}

	StringStream& StringStream::Append(unsigned long n) {
		impl_->Append(n);
		return *this;
	}

	StringStream& StringStream::Append(long long n) {
		impl_->Append(n);
		return *this;
	}

	StringStream& StringStream::Append(unsigned long long n) {
		impl_->Append(n);
		return *this;
	}

	StringStream& StringStream::Append(const char* s) {
		impl_->Append(s);
		return *this;
	}

	StringStream& StringStream::Append(const char* s, int len) {
		impl_->Append(s, len);
		return *this;
	}

	StringStream& StringStream::Append(const std::string& s) {
		impl_->Append(s);
		return *this;
	}

	StringStream& StringStream::AppendCurrentTime(const char* fmt) {
		impl_->AppendCurrentTime(fmt);
		return *this;
	}

	void StringStream::Clear() {
		impl_->Clear();
	}

	const char* StringStream::GetBuffer() const {
		return impl_->GetBuffer();
	}

	std::string StringStream::GetString() {
		return impl_->GetString();
	}

	int StringStream::Size() const {
		return impl_->Size();
	}

	int StringStream::Available() const {
		return impl_->Available();
	}

}
