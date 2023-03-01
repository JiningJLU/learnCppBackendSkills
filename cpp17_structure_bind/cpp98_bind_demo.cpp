#include <iostream>
#include <string>
#include <map>

int main()
{
    std::map<std::string, int> cities;
    cities["beijing"] = 0;
    cities["shanghai"] = 1;
    cities["guangzhou"] = 2;
    cities["shenzhen"] = 3;
    // 这就是结构化绑定，其实就是py的解包
    for (const auto &[k, v] : cities)
    {
        std::cout << k << ": " << v << std::endl;
    }
    std::pair<std::map<std::string, int>::iterator, int> insertResult = cities.insert(std::pair<std::string, int>("shanghai", 2));
    auto insertResult2 = cities.insert(std::pair<std::string, int>("shanghai", 2));
    std::cout << "Is insertion successful?"
              << (insertResult2.second ? "true" : "false")
              << ", element key: " << insertResult2.first->first << ", value: "
              << insertResult2.first->second << std::endl;
    return 0;
}