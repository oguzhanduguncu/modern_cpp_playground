//
// Created by oguzh on 23.02.2026.
//
#include <iostream>
class tester {
public:
    tester() {
        std::cout << "ctor \n";
    }
    tester(const tester&) {
        std::cout << "copy ctor \n";
    }
    tester(tester&&) noexcept {
        std::cout << "move ctor \n";
    }
};

template <typename U>
decltype(auto) forwarding_wrapper(U&& x) {
    return std::forward<U>(x);
}


int main() {
    std::cout << "lvalue \n";
    tester obj{};
    tester a = forwarding_wrapper(obj);
    std::cout << "prvalue \n";
    tester b = forwarding_wrapper(tester{});
    std::cout << "xvalue \n";
    tester objx{};
    tester c = forwarding_wrapper(std::move(objx));
    std::cout << "lifetime extension(temporary materialization conversion + reference binding) \n";
    tester&& r = forwarding_wrapper(tester{});
    std::cout << "lifetime extension \n";
    const tester& k = forwarding_wrapper(tester{});
    std::cout << "lifetime extension fails: \n";
    auto x = forwarding_wrapper(tester{}); // value; yeni nesne, extension değil

}