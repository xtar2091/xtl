#include <cstring>
#include <chrono>
#include <iostream>
#include <string>
#include <sstream>
#include "xtl/string/StringStream.h"

void Test2() {
    long long int total_test_count = 100000000;
    char buf[1024];
    std::string str;
    std::ostringstream oss;
    xtl::StringStream ss;

    std::cout << "total test count:" << total_test_count << std::endl;

    {
        auto start = std::chrono::steady_clock::now();
        for (long long i = 0; i < total_test_count; i++) {
            snprintf(buf, sizeof(buf), "%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %s",
                -10001, -10000, -9999, -11, -10, -9, 0, 9, 10, 11, 9999, 10000, 10001, "abcdefghijklmnopqrstuvwxyz");
        }
        auto end = std::chrono::steady_clock::now();
        std::cout << "snprintf cost:" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
    }

    {
        auto start = std::chrono::steady_clock::now();
        for (long long i = 0; i < total_test_count; i++) {
            oss << -10001 << ", " << 10000 << ", " << -9999 << ", " << -11 << ", " << -10 << ", " << -9 << ", " << 0 << ", " << 9 << ", " << 10 << ", " << 11 << ", "
                << 9999 << ", " << 10000 << ", " << 10001 << ", abcdefghijklmnopqrstuvwxyz";
            oss.str("");
        }
        auto end = std::chrono::steady_clock::now();
        std::cout << "ostringstream cost:" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
    }

    {
        auto start = std::chrono::steady_clock::now();
        for (long long i = 0; i < total_test_count; i++) {
            ss << -10001 << ", " << 10000 << ", " << -9999 << ", " << -11 << ", " << -10 << ", " << -9 << ", " << 0 << ", " << 9 << ", " << 10 << ", " << 11 << ", "
                << 9999 << ", " << 10000 << ", " << 10001 << ", abcdefghijklmnopqrstuvwxyz";
            ss.Clear();
        }
        auto end = std::chrono::steady_clock::now();
        std::cout << "StringStream cost:" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
    }
}

int main() {
    xtl::StringStream ss;
    ss<<-10001<<", "<<-10000<<", "<<-9999<<", "<<-100<<", "<<-11<<", "<<-10<<", "<<-9<<", "<<0<<", "
        <<9<<", "<<10<<", "<<11<<", "<<100<<", "<<9999<<", "<<10000<<", "<<10001<<", abc";
    std::cout<<ss.GetBuffer()<<std::endl;

    xtl::StringStream ss2(std::move(ss));
    ss2<<"|||";
    std::cout<<ss2.GetBuffer()<<std::endl;
    //Test2();
    return 0;
}
