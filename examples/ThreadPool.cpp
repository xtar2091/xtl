#include <iostream>
#include <string>
#include <xtl/ThreadPool.h>

int main() {
    xtl::ThreadPool tp;
    tp.Start(3);
    auto f1 = tp.Append([]()->int {
        return 1;
    });
    auto f2 = tp.Append([]()->std::string {
        return "2";
    });
    std::cout<<"f1 result:"<<f1.get()<<std::endl;
    std::cout<<"f2 result:"<<f2.get()<<std::endl;
    tp.Stop();
    return 0;
}
