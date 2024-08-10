#include <iostream>
#include <atomic>
#include <thread>

std::atomic<int> value(0);

void increment() {
    for (int i = 0; i < 10000; ++i) {
        ++value;
        std::cout<<"value = "<<value.load()<<std::endl;
    }
}

void check() {
    // 错误做法：不使用 load() 函数，直接比较
    // std::this_thread::sleep_for(std::chrono::seconds(1));
    while (true) {
        if (value == 10000) { // 直接比较 atomic<int> 的值
            std::cout << "Value reached 10000" << std::endl;
            break;
        }
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(check);

    t1.join();
    t2.join();

    return 0;
}
