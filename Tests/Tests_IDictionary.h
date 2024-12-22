#ifndef TRAINING_SFML_TESTS_DICTIONARY_H
#define TRAINING_SFML_TESTS_DICTIONARY_H

#include "../IDictionary.h"
#include <cassert>
#include <iostream>

// Тест конструктора по умолчанию
template <typename TKey, typename TValue>
int test_dictionary_default_constructor() {
    IDictionary<TKey, TValue> dictionary;
    assert(dictionary.Size() == 0);

    std::cout << "Test passed: test_dictionary_default_constructor\n";
    return 1;
}

// Тест метода Add
template <typename TKey, typename TValue>
int test_dictionary_add() {
    IDictionary<TKey, TValue> dictionary;
    dictionary.Add(1, "One");
    dictionary.Add(2, "Two");
    dictionary.Add(3, "Three");
    assert(dictionary.Size() == 3);

    std::cout << "Test passed: test_dictionary_add\n";
    return 1;
}

// Тест метода Get
template <typename TKey, typename TValue>
int test_dictionary_get() {
    IDictionary<TKey, TValue> dictionary;
    dictionary.Add(1, "One");
    dictionary.Add(2, "Two");
    dictionary.Add(3, "Three");
    assert(dictionary.Get(2) == "Two");

    std::cout << "Test passed: test_dictionary_get\n";
    return 1;
}

// Тест метода Contains
template <typename TKey, typename TValue>
int test_dictionary_contains() {
    IDictionary<TKey, TValue> dictionary;
    dictionary.Add(1, "One");
    dictionary.Add(2, "Two");
    dictionary.Add(3, "Three");
    assert(dictionary.Contains(2));

    std::cout << "Test passed: test_dictionary_contains\n";
    return 1;
}

// Тест метода Remove
template <typename TKey, typename TValue>
int test_dictionary_remove() {
    IDictionary<TKey, TValue> dictionary;
    dictionary.Add(1, "One");
    dictionary.Add(2, "Two");
    dictionary.Add(3, "Three");
    dictionary.Remove(2);
    assert(dictionary.Size() == 2);
    assert(!dictionary.Contains(2));

    std::cout << "Test passed: test_dictionary_remove\n";
    return 1;
}

// Тест всех методов и конструкторов
inline void test_idictionary() {
    constexpr int total_tests = 5;
    const int passed_tests = test_dictionary_default_constructor<int, std::string>() +
                             test_dictionary_add<int, std::string>() +
                             test_dictionary_get<int, std::string>() +
                             test_dictionary_contains<int, std::string>() +
                             test_dictionary_remove<int, std::string>();

    const int failed_tests = total_tests - passed_tests;
    std::cout << "_____________________________________________________________\n";
    std::cout << "Total Dictionary tests: " << total_tests << ", Passed: " << passed_tests << ", Failed: " << failed_tests << std::endl;
    std::cout << "_____________________________________________________________\n";
}

#endif //TRAINING_SFML_TESTS_DICTIONARY_H
