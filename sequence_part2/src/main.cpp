#include <iostream>
#include <fstream>

#include "libs/ArraySequence.hpp"
#include "libs/ListSequence.hpp"
#include "libs/Sorter.hpp"
#include "libs/IClocking.hpp"

#define ELEMENTS_MAX 10000
#define ELEMENTS_MIN 10
#define POINTS 15

bool int_cmpf(int a, int b) { return a > b; }

int list_sort() {
    auto array = new ListSequence<int>();

    for (std::size_t i = 0; i < 20; ++i) {
        array->append(rand() % 100);
    }

    for (std::size_t i = 0; i < array->size(); ++i) std::cout << array->get(i) << " ";
    std::cout << std::endl;

    // SorterList<int>::merge_sort_list(array, int_cmpf);
    SorterList<int>::qsort_list(array, int_cmpf);
    
    for (std::size_t i = 0; i < array->size(); ++i) std::cout << array->get(i) << " ";
    std::cout << std::endl;
    delete array;
    return 0;
}

int array_sort() {
    auto array = new ArraySequence<int>();

    for (std::size_t i = 0; i < 20; ++i) {
        array->push_back(rand() % 100);
    }

    for (std::size_t i = 0; i < array->size(); ++i) std::cout << array->get(i) << " ";
    std::cout << std::endl;

    Sorter<int>::merge_sort(array, int_cmpf);

    for (std::size_t i = 0; i < array->size(); ++i) std::cout << array->get(i) << " ";
    std::cout << std::endl;

    delete array;
    return 0;
}

int test_clocking() {
    auto array = new ArraySequence<int>();
    IClocking<ArraySequence<int>, int> clock;

    for (std::size_t i = 0; i < 100000; ++i) {
        array->append(1 + rand() % 100000);
    }
    
    double time = clock.sort_clocking_random_set(1000000, Sorter<int>::qsort, int_cmpf);
    std::cout << time << std::endl;
    time = clock.sort_clocking_random_set(10000, Sorter<int>::bubble_sort, int_cmpf);
    std::cout << time << std::endl;
    time = clock.sort_clocking_random_set(1000000, Sorter<int>::merge_sort, int_cmpf);
    std::cout << time << std::endl;
/*
    time = clock.sort_clocking(array, Sorter<int>::merge_sort, int_cmpf);
    std::cout << time.count() << std::endl;

    time = clock.sort_clocking(array, Sorter<int>::bubble_sort, int_cmpf);
    std::cout << time.count() << std::endl;
    
    time = clock.sort_clocking(array, Sorter<int>::shaker_sort, int_cmpf);
    std::cout << time.count() << std::endl;
*/
    return 0;
}

int test_clocking_list() {
    auto array = new ListSequence<int>();
    IClocking<ListSequence<int>, int> clock;

    for (std::size_t i = 0; i < 100000; ++i) {
        array->append(1 + rand() % 100000);
    }
    
    double time = clock.sort_clocking_random_set(100000, SorterList<int>::qsort_list, int_cmpf);
    std::cout << time << std::endl;
    time = clock.sort_clocking_random_set(100000, SorterList<int>::merge_sort_list, int_cmpf);
    std::cout << time << std::endl;
/*
    time = clock.sort_clocking(array, Sorter<int>::merge_sort, int_cmpf);
    std::cout << time.count() << std::endl;

    time = clock.sort_clocking(array, Sorter<int>::bubble_sort, int_cmpf);
    std::cout << time.count() << std::endl;
    
    time = clock.sort_clocking(array, Sorter<int>::shaker_sort, int_cmpf);
    std::cout << time.count() << std::endl;
*/
    return 0;
}

template<class Contain, typename T>
void push_to_file(const std::string& name, void sort(Contain*, bool(*)(T, T)), std::ofstream &out) {
    IClocking<Contain, T> clock;
    out << name << std::endl;

    for (std::size_t t = 0; t < POINTS; ++t) {
        std::size_t number = ELEMENTS_MIN + (ELEMENTS_MAX - ELEMENTS_MIN) * t / (POINTS - 1);
        out << number << " ";
        double time = clock.sort_clocking_random_set(number, sort, int_cmpf);
        out << (int)(time * 10000) << "\n";
    }
}

void file_clocking() {
    std::ofstream out;
    out.open("../data/file1.txt");

    push_to_file<ArraySequence<int>, int>("ARRAY-QSORT", Sorter<int>::qsort, out);
    push_to_file<ArraySequence<int>, int>("ARRAY-MERGE_SORT", Sorter<int>::merge_sort, out);
    push_to_file<ArraySequence<int>, int>("ARRAY-BUBBLE_SORT", Sorter<int>::bubble_sort, out);
    push_to_file<ArraySequence<int>, int>("ARRAY-SHAKER_SORT", Sorter<int>::shaker_sort, out);

    out.close();
}

void file_clocking_list() {
    std::ofstream out;
    out.open("../data/file2.txt");

    push_to_file<ListSequence<int>, int>("LIST-QSORT", SorterList<int>::qsort_list, out);
    push_to_file<ListSequence<int>, int>("LIST-MERGE_SORT", SorterList<int>::merge_sort_list, out);

    out.close();
}

int main() {
    std::ofstream out;
    out.open("data/options.txt");
    out << POINTS << "\n";
    out.close();

    file_clocking();
    file_clocking_list();

    std::cout << std::endl;
    system("python3 main.py");

    return 0;
}
