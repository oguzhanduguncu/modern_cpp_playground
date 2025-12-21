//
// Created by oguzh on 21.12.2025.
//
#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>
struct performance {
    std::atomic<int> id = 0;
    std::atomic<int> size = 0;
};

struct alignas(64) padded_performance {
    std::atomic<int> id = 0;
};

void counter(std::atomic<int> &count) {
    for (int i = 0; i < 300'000; i++ ) {
        count.fetch_add(1, std::memory_order_relaxed);
    }
}

int main() {
    performance p1;
    padded_performance p3,p4;
    std::thread t1(counter,std::ref(p1.id));
    std::thread t2(counter,std::ref(p1.size));
    auto start1 = std::chrono::steady_clock::now();
    t1.join();
    t2.join();
    auto end1 = std::chrono::steady_clock::now();
    std::thread t3(counter,std::ref(p3.id));
    std::thread t4(counter,std::ref(p4.id));
    auto start2 = std::chrono::steady_clock::now();
    t3.join();
    t4.join();
    auto end2 = std::chrono::steady_clock::now();
    std::cout << (end1 - start1).count() << '\n';
    std::cout << (end2 - start2).count() << '\n';

}