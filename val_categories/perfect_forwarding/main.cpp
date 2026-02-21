//
// Created by oguzh on 21.02.2026.
//
#include<iostream>
#include <utility>
class identity {
    std::string name_ = "";
public:
    identity() = default;
    identity(std::string name) : name_(std::move(name)) {
        std::cout << "ctor with " << name_ << "\n";
    };
    identity(const identity& other) : name_(other.name_) {
        std::cout << "copy constructor identity with " << name_ << "\n" ;
    }
    identity(identity&& other)  noexcept : name_(std::move(other.name_)) {
        std::cout << "move constructor identity with " << name_ << "\n";
    }

};
class shape {
    std::string name_;
    identity name_id;
    int size = 0;
    public:
    template<typename T>
    shape(std::string name, T&& name_id) : name_(std::move(name)), name_id(std::forward<T>(name_id)) {
        std::cout << "universal reference - string arg \n";
    };
    shape(std::string name, int a) : name_(std::move(name)), size(a) {
        std::cout << "integer argument \n";
    }
};

int main() {
    shape sq("sq", identity("osan"));
    identity ex {"oguzhan"};
    shape tri("tri", ex);
    shape circ("circ", "literal");
    shape t("t", 5);
    int e = 5;
    shape k("k", e);
    size_t s = 6;
   // shape exp("exp", s);
    return 0;
}