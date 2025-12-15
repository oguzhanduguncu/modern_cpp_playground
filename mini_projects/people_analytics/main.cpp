//
// Created by oguzh on 15.12.2025.
//
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <ranges>
#include <unordered_map>

struct Person {
    std::string name;
    int age;
    std::string city;
    double salary;
};
std::vector<Person> people {
        {"Alice", 30, "Ankara", 5000},
        {"Bob", 22, "Istanbul", 3000},
        {"Charlie", 40, "Ankara", 7000},
        {"Diana", 35, "Izmir", 6500},
        {"Eve", 28, "Istanbul", 4000},
        {"Frank", 50, "Ankara", 9000}
};

int main() {
    std::vector <std::string> senior_names;
    auto names = people
    | std::views::filter([](const Person &p) { return p.age > 30; })
    | std::views::transform([](const Person &p) { return p.name; })
    | std::views::take(3);
    std::ranges::copy(names, std::back_inserter(senior_names));

    std::unordered_map<std::string, int> population;
    std::ranges::for_each(people, [&population](const Person &p) {
        population[p.city]++;
    });

    std::unordered_map<std::string, std::pair<double,int>> salary_acc;

    std::ranges::for_each(people, [&](const Person& p){
        auto& entry = salary_acc[p.city];
        entry.first  += p.salary;
        entry.second += 1;
    });
    auto result = std::ranges::max_element(people, [](const Person &p1, const Person &p2) {
        return p1.salary < p2.salary;
    });
    std::cout << result->salary << std::endl;

    auto it = std::ranges::partition(people,  [](const Person &p) { return p.salary > 6000; });
    auto count = std::ranges::distance(it);
    std::cout << count << '\n';
    return 0;
}