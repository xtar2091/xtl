#include <chrono>
#include <thread>
#include <vector>
#include <mutex>
#include <iostream>
#include "xtl/log/Log.h"

int main() {
    xtl::Log::Instance()->SetLogLevel(xtl::Log::LogLevel::notice);
    xtl::Log::Instance()->SetLogDir("./");
    XLOG_SetLogId("aabbcc");
    XLOG_DEBUG<<"debug";
    XLOG_INFO<<"info";
    XLOG_NOTICE<<"notice";
    XLOG_WARNING<<"warning";
    XLOG_FATAL<<"fatal";
    /*{
        std::vector<std::thread> vec;
        auto start = std::chrono::steady_clock::now();
        for (int i = 0; i < 5; i++) {
            vec.push_back(std::thread([](){
                for (long long int i = 0; i < 10000000; i++) {
                    XLOG_NOTICE<<-10001<<", "<<-10000<<", "<<-9999<<", "<<-11<<", "<<-10<<", "<<-9<<", "<<0<<", "
                        <<9<<", "<<10<<", "<<11<<", "<<9999<<", "<<10000<<", "<<10001<<", abcdefghijklmnopqrstuvwxyz\n";
                }
            }));
        }
        for (auto& thrd : vec) {
            thrd.join();
        }
        auto end = std::chrono::steady_clock::now();
        XLOG_NOTICE<<"total cost:"<<std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()<<"\n";
    }*/
    return 0;
}
