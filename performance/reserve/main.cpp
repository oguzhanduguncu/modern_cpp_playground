//
// Created by oguzh on 16.12.2025.
//
#include <vector>
#include <chrono>
#include <iostream>

int counter;
template <typename T>
class customAllocator {
public:
    typedef T value_type;
    customAllocator() noexcept {}
    T* allocate(std::size_t n)
    {
        counter++;
        return static_cast<T*>(
            ::operator new(n * sizeof(T)));
    }
    void deallocate(T* p, std::size_t n) noexcept
    {
        ::operator delete(p);
    }
};
std::vector<int,customAllocator<int>> make_without_reserve(std::size_t n) {
    std::vector<int,customAllocator<int>> v;
    for (std::size_t i = n; i > 0; --i) {
        v.push_back(static_cast<int>(i));
    }
    return v;
}

std::vector<int,customAllocator<int>> make_with_reserve(std::size_t n) {
    std::vector<int,customAllocator<int>> v;
    v.reserve(n);
    for (std::size_t i = n; i > 0; --i) {
        v.push_back(static_cast<int>(i));
    }
    return v;
}

int main() {
    constexpr long long int N = 1'000'000;
    const auto t1 = std::chrono::steady_clock::now();
    std::vector<int,customAllocator<int>> v = make_without_reserve(N);
    std::cout << counter << std::endl;
    const auto t2 = std::chrono::steady_clock::now();
    counter = 0;
    std::vector<int,customAllocator<int>> v2 = make_with_reserve(N);
    std::cout << counter << std::endl;
    const auto t3 = std::chrono::steady_clock::now();
    std::cout << "Without reserve: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << std::endl;
    std::cout << "With reserve: " <<std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count() << std::endl;
}