#include "city.hpp"

City::City(std::string name, std::size_t population) :
    data(name),
    hash(std::hash<std::string>{}(name)),
    population(population) {}

void City::print() {
    std::cout << this->data << " " << this->population << std::endl;
}