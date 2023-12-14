#ifndef SRC_LIBS_CITY_HPP_
#define SRC_LIBS_CITY_HPP_

#include <iostream>
#include <string>

class City {
public:
    City(std::string name, std::size_t population);

    void print();

public:
    std::string data;
    std::size_t population;
    std::size_t hash;
};

#endif  // SRC_LIBS_CITY_HPP_