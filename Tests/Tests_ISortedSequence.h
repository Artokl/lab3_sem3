#ifndef TRAINING_SFML_TESTS_ISORTEDSEQUENCE_H
#define TRAINING_SFML_TESTS_ISORTEDSEQUENCE_H
#include "../ISortedSequence.h"
#include <cassert>

inline int test_red_black_tree_default_constructor_int() {
    const RedBlackTree<int> tree;
    assert(tree.GetSequence().empty());

    std::cout << "Test passed: test_red_black_tree_default_constructor_int\n";
    return 1;
}

inline int test_red_black_tree_add_int() {
    RedBlackTree<int> tree;
    tree.Add(3);
    tree.Add(1);
    tree.Add(5);
    tree.Add(2);
    tree.Add(4);

    const std::vector expected = {1, 2, 3, 4, 5};
    assert(tree.GetSequence() == expected);

    std::cout << "Test passed: test_red_black_tree_add_int\n";
    return 1;
}

inline int test_sorted_sequence_default_constructor_int() {
    const ISortedSequence<int> sequence;
    assert(sequence.GetIsEmpty());
    assert(sequence.GetLength() == 0);

    std::cout << "Test passed: test_sorted_sequence_default_constructor_int\n";
    return 1;
}

inline int test_sorted_sequence_add_int() {
    ISortedSequence<int> sequence;
    sequence.Add(3);
    sequence.Add(1);
    sequence.Add(5);
    sequence.Add(2);
    sequence.Add(4);

    const std::vector expected = {1, 2, 3, 4, 5};
    assert(sequence.GetSequence() == expected);

    std::cout << "Test passed: test_sorted_sequence_add_int\n";
    return 1;
}

inline int test_sorted_sequence_get_first_int() {
    ISortedSequence<int> sequence;
    sequence.Add(3);
    sequence.Add(1);
    sequence.Add(5);

    assert(sequence.GetFirst() == 1);

    std::cout << "Test passed: test_sorted_sequence_get_first_int\n";
    return 1;
}

inline int test_sorted_sequence_get_last_int() {
    ISortedSequence<int> sequence;
    sequence.Add(3);
    sequence.Add(1);
    sequence.Add(5);

    assert(sequence.GetLast() == 5);

    std::cout << "Test passed: test_sorted_sequence_get_last_int\n";
    return 1;
}

inline int test_sorted_sequence_index_of_int() {
    ISortedSequence<int> sequence;
    sequence.Add(3);
    sequence.Add(1);
    sequence.Add(5);

    assert(sequence.IndexOf(1) == 0);
    assert(sequence.IndexOf(5) == 2);
    assert(sequence.IndexOf(2) == -1);

    std::cout << "Test passed: test_sorted_sequence_index_of_int\n";
    return 1;
}

// Тест метода GetSubsequence
inline int test_sorted_sequence_get_subsequence_int() {
    ISortedSequence<int> sequence;
    sequence.Add(3);
    sequence.Add(1);
    sequence.Add(5);
    sequence.Add(2);
    sequence.Add(4);

    const ISortedSequence<int> subsequence = sequence.GetSubsequence(1, 3);

    const std::vector expected = {2, 3, 4};
    assert(subsequence.GetSequence() == expected);

    std::cout << "Test passed: test_sorted_sequence_get_subsequence_int\n";
    return 1;
}

// Тест всех методов и конструкторов
inline void test_sorted_sequence() {
    constexpr int total_tests = 6;
    const int passed_tests = test_sorted_sequence_default_constructor_int() +
                             test_sorted_sequence_add_int() +
                             test_sorted_sequence_get_first_int() +
                             test_sorted_sequence_get_last_int() +
                             test_sorted_sequence_index_of_int() +
                             test_sorted_sequence_get_subsequence_int();

    const int failed_tests = total_tests - passed_tests;
    std::cout << "_____________________________________________________________\n";
    std::cout << "Total ISortedSequence tests: " << total_tests << ", Passed: " << passed_tests << ", Failed: " << failed_tests << std::endl;
    std::cout << "_____________________________________________________________\n";
}

// Тест всех методов и конструкторов
inline void test_red_black_tree() {
    constexpr int total_tests = 2;
    const int passed_tests = test_red_black_tree_default_constructor_int() +
                             test_red_black_tree_add_int();

    const int failed_tests = total_tests - passed_tests;
    std::cout << "_____________________________________________________________\n";
    std::cout << "Total Red-Black Tree tests: " << total_tests << ", Passed: " << passed_tests << ", Failed: " << failed_tests << std::endl;
    std::cout << "_____________________________________________________________\n";
}



#endif //TRAINING_SFML_TESTS_ISORTEDSEQUENCE_H
