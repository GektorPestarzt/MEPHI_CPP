#include "test.hpp"

#include <iostream>
#include <fstream>
#include <chrono>
#include <assert.h>

#include "libs/city.hpp"
#include "libs/storage.hpp"

using namespace std::chrono;
#define FILE_NAME "cities.txt"

Storage<City, std::string> *push_from_file(std::ifstream& file);
double clock_item(const std::string& name, Storage<City, std::string> *storage);

void test_cache_time_0();
void test_cache_time_1();
void test_cache_time_2();
void test_cache_time_3();
void test_cache_time_4();
void test_cache_time_5();

int main() {
    test_cache_time_0();
    test_cache_time_1();
    test_cache_time_2();
    test_cache_time_3();
    test_cache_time_4();
    test_cache_time_5();

    std::cout << "Tests passed" << std::endl;
    return 0;
}

void test_cache_time_0() {
        std::ifstream file(FILE_NAME);

    if (file.is_open()) {
        auto storage = push_from_file(file);

        double first_time = clock_item("Addison", storage);
        double second_time = clock_item("Addison", storage);

        assert(second_time * 10 < first_time);
        delete storage;
    }

    file.close();
}

void test_cache_time_1() {
    std::ifstream file(FILE_NAME);

    if (file.is_open()) {
        auto storage = push_from_file(file);

        double first_time = clock_item("Addison", storage);
    
        storage->get_item("Phenix City");
        storage->get_item("San Bruno");
        storage->get_item("Bell Gardens");
        storage->get_item("Rancho Palos Verdes");
        storage->get_item("Apex");
        storage->get_item("Manassas");
        storage->get_item("Minot");
        storage->get_item("Euclid");
        storage->get_item("La Mirada");
        storage->get_item("Saginaw");
        storage->get_item("Huntersville");
        storage->get_item("Palm Desert");
        storage->get_item("Cutler Bay");
        storage->get_item("Wylie");
        storage->get_item("Pine Bluff");
        storage->get_item("Azusa");
        storage->get_item("Monroe");
        storage->get_item("Covina");
        storage->get_item("Parker"); // 20
        storage->get_item("Covina"); // already in cache

        double second_time = clock_item("Addison", storage);

        assert(second_time * 10 < first_time);
        delete storage;
    }

    file.close();
}

void test_cache_time_2() {
        std::ifstream file(FILE_NAME);

    if (file.is_open()) {
        auto storage = push_from_file(file);

        double first_time = clock_item("Addison", storage);

        storage->get_item("Phenix City");
        storage->get_item("San Bruno");
        storage->get_item("Bell Gardens");
        storage->get_item("Rancho Palos Verdes");
        storage->get_item("Apex");
        storage->get_item("Manassas");
        storage->get_item("Minot");
        storage->get_item("Euclid");
        storage->get_item("La Mirada");
        storage->get_item("Saginaw");
        storage->get_item("Huntersville");
        storage->get_item("Palm Desert");
        storage->get_item("Cutler Bay");
        storage->get_item("Wylie");
        storage->get_item("Pine Bluff");
        storage->get_item("Azusa");
        storage->get_item("Monroe");
        storage->get_item("Covina");
        storage->get_item("Parker"); // 20
        storage->get_item("Belleville"); // 21

        double second_time = clock_item("Addison", storage);

        assert(abs(first_time - second_time) < 1E-4);
        delete storage;
    }

    file.close();
}

void test_cache_time_3() {
        std::ifstream file(FILE_NAME);

    if (file.is_open()) {
        auto storage = push_from_file(file);

        storage->get_item("Phenix City");
        storage->get_item("San Bruno");
        storage->get_item("Bell Gardens");
        storage->get_item("Rancho Palos Verdes");
        storage->get_item("Apex");

        double first_time = clock_item("Addison", storage);

        storage->get_item("Manassas");
        storage->get_item("Minot");
        storage->get_item("Euclid");
        storage->get_item("La Mirada");
        storage->get_item("Saginaw");
        storage->get_item("Huntersville");
        storage->get_item("Palm Desert");
        storage->get_item("Cutler Bay");
        storage->get_item("Wylie");
        storage->get_item("Pine Bluff");
        storage->get_item("Azusa");
        storage->get_item("Monroe");
        storage->get_item("Covina");
        storage->get_item("Parker"); // 20

        double second_time = clock_item("Addison", storage);

        assert(second_time * 10 < first_time);
        delete storage;
    }

    file.close();
}

void test_cache_time_4() {
        std::ifstream file(FILE_NAME);

    if (file.is_open()) {
        auto storage = push_from_file(file);

        storage->get_item("Phenix City");
        storage->get_item("San Bruno");
        storage->get_item("Bell Gardens");
        storage->get_item("Rancho Palos Verdes");
        storage->get_item("Apex");
        storage->get_item("Manassas");
        storage->get_item("Minot");
        storage->get_item("Euclid");
        storage->get_item("La Mirada");
        storage->get_item("Saginaw");
        storage->get_item("Huntersville");
        storage->get_item("Palm Desert");
        storage->get_item("Cutler Bay");
        storage->get_item("Wylie");
        storage->get_item("Pine Bluff");
        storage->get_item("Azusa");
        storage->get_item("Monroe");
        storage->get_item("Covina");
        storage->get_item("Parker");
        double first_time = clock_item("Addison", storage); // 20
        double second_time = clock_item("Addison", storage);

        assert(second_time * 10 < first_time);
        delete storage;
    }

    file.close();
}

void test_cache_time_5() {
        std::ifstream file(FILE_NAME);

    if (file.is_open()) {
        auto storage = push_from_file(file);

        storage->get_item("Phenix City");
        storage->get_item("San Bruno");
        storage->get_item("Bell Gardens");
        storage->get_item("Rancho Palos Verdes");
        storage->get_item("Apex");
        storage->get_item("Manassas");
        storage->get_item("Minot");
        storage->get_item("Euclid");
        storage->get_item("La Mirada");
        storage->get_item("Saginaw");
        storage->get_item("Huntersville");
        storage->get_item("Palm Desert");
        storage->get_item("Cutler Bay");
        storage->get_item("Wylie");
        storage->get_item("Pine Bluff");
        storage->get_item("Azusa");
        storage->get_item("Monroe");
        storage->get_item("Covina");
        storage->get_item("Parker");
        storage->get_item("Columbus"); // 20
        double first_time = clock_item("Addison", storage); // 21
        double second_time = clock_item("Addison", storage);

        assert(second_time * 10 < first_time);
        delete storage;
    }

    file.close();
}

Storage<City, std::string> *push_from_file(std::ifstream& file) {
    auto storage = new Storage<City, std::string>();
    std::string city_name;
    std::size_t population;

    std::string buffer;
    while (!file.eof()) {
        std::getline(file, buffer, ',');
        std::getline(file, city_name, ',');
        std::getline(file, buffer, ',');
        file >> population;
        std::getline(file, buffer, ',');
        std::getline(file, buffer, '\n');

        City *data = new City(city_name, population);
        bool status = storage->push_item(data);
    
        if (status) delete data;
    }

    return storage;
}

double clock_item(const std::string& name, Storage<City, std::string> *storage) {
    auto start_clock = high_resolution_clock::now();
    City *item = storage->get_item(name);
    auto stop_clock = high_resolution_clock::now();
    duration<double> duration = stop_clock - start_clock;

    return duration.count();
}