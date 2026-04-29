#include <gtest/gtest.h>

#include <array>

#include "../s21_array.h"

// -----------Array Member functions--------------------

TEST(array_test, default_costructor) {
  s21::array<int, 3> s21_array;
  std::array<int, 3> std_array;
  EXPECT_EQ(s21_array.size(), std_array.size());
  EXPECT_EQ(s21_array.max_size(), std_array.max_size());
  EXPECT_EQ(s21_array.empty(), std_array.empty());
}

TEST(array_test, initializer_list_int) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  std::array<int, 3> std_array = {1, 2, 3};
  EXPECT_EQ(s21_array.size(), std_array.size());
  EXPECT_EQ(s21_array.max_size(), std_array.max_size());
  for (std::size_t i = 0; i < 3; i++) {
    EXPECT_EQ(s21_array.at(i), std_array.at(i));
  }
}

TEST(array_test, initializer_list_char) {
  s21::array<char, 3> s21_array = {'a', 'b', 'c'};
  std::array<char, 3> std_array = {'a', 'b', 'c'};
  EXPECT_EQ(s21_array.size(), std_array.size());
  EXPECT_EQ(s21_array.max_size(), std_array.max_size());
  for (std::size_t i = 0; i < 3; i++) {
    EXPECT_EQ(s21_array.at(i), std_array.at(i));
  }
}

TEST(array_test, initializer_list_float) {
  s21::array<float, 3> s21_array = {1.234, 5.678, 9.123};
  std::array<float, 3> std_array = {1.234, 5.678, 9.123};
  EXPECT_EQ(s21_array.size(), std_array.size());
  EXPECT_EQ(s21_array.max_size(), std_array.max_size());
  for (std::size_t i = 0; i < 3; i++) {
    EXPECT_EQ(s21_array.at(i), std_array.at(i));
  }
}

TEST(array_test, initializer_list_big_size) {
  s21::array<int, 10> s21_array = {1, 2, 3};
  std::array<int, 10> std_array = {1, 2, 3};
  EXPECT_EQ(s21_array.size(), std_array.size());
  EXPECT_EQ(s21_array.max_size(), std_array.max_size());
  for (std::size_t i = 0; i < 10; i++) {
    EXPECT_EQ(s21_array.at(i), std_array.at(i));
  }
}

TEST(array_test, initializer_list_throw) {
  try {
    s21::array<int, 3> s21_array = {1, 2, 3, 4};
  } catch (std::out_of_range &ex) {
    EXPECT_EQ(
        ex.what(),
        std::string("The number of initializer clauses in the initializer list "
                    "exceeds the number of elements of the aggregate"));
  }
}

TEST(array_test, copy_constructor_int) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  s21::array<int, 3> s21_test(s21_array);
  EXPECT_EQ(s21_array.size(), s21_test.size());
  EXPECT_EQ(s21_array.max_size(), s21_test.max_size());
  for (std::size_t i = 0; i < 3; i++) {
    EXPECT_EQ(s21_array.at(i), s21_test.at(i));
  }
}

TEST(array_test, copy_constructor_char) {
  s21::array<char, 3> s21_array = {'a', 'b', 'c'};
  s21::array<char, 3> s21_test(s21_array);
  EXPECT_EQ(s21_array.size(), s21_test.size());
  EXPECT_EQ(s21_array.max_size(), s21_test.max_size());
  for (std::size_t i = 0; i < 3; i++) {
    EXPECT_EQ(s21_array.at(i), s21_test.at(i));
  }
}

TEST(array_test, copy_constructor_float) {
  s21::array<float, 3> s21_array = {1.234, 5.678, 9.123};
  s21::array<float, 3> s21_test(s21_array);
  EXPECT_EQ(s21_array.size(), s21_test.size());
  EXPECT_EQ(s21_array.max_size(), s21_test.max_size());
  for (std::size_t i = 0; i < 3; i++) {
    EXPECT_EQ(s21_array.at(i), s21_test.at(i));
  }
}

TEST(array_test, copy_constructor_big_size) {
  s21::array<int, 10> s21_array = {1, 2, 3};
  s21::array<int, 10> s21_test(s21_array);
  EXPECT_EQ(s21_array.size(), s21_test.size());
  EXPECT_EQ(s21_array.max_size(), s21_test.max_size());
  for (std::size_t i = 0; i < 10; i++) {
    EXPECT_EQ(s21_array.at(i), s21_test.at(i));
  }
}

TEST(array_test, move_constuctor_int) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  s21::array<int, 3> s21_test(std::move(s21_array));
  std::array<int, 3> std_array = {1, 2, 3};
  std::array<int, 3> std_test(std::move(std_array));
  EXPECT_EQ(s21_test.size(), std_test.size());
  EXPECT_EQ(s21_test.max_size(), std_test.max_size());
  for (std::size_t i = 0; i < 3; i++) {
    EXPECT_EQ(s21_test.at(i), std_test.at(i));
  }
}

TEST(array_test, move_constuctor_char) {
  s21::array<char, 3> s21_array = {'a', 'b', 'c'};
  s21::array<char, 3> s21_test(std::move(s21_array));
  std::array<char, 3> std_array = {'a', 'b', 'c'};
  std::array<char, 3> std_test(std::move(std_array));
  EXPECT_EQ(s21_test.size(), std_test.size());
  EXPECT_EQ(s21_test.max_size(), std_test.max_size());
  for (std::size_t i = 0; i < 3; i++) {
    EXPECT_EQ(s21_test.at(i), std_test.at(i));
  }
}

TEST(array_test, move_constuctor_float) {
  s21::array<float, 3> s21_array = {1.234, 5.678, 9.123};
  s21::array<float, 3> s21_test(std::move(s21_array));
  std::array<float, 3> std_array = {1.234, 5.678, 9.123};
  std::array<float, 3> std_test(std::move(std_array));
  EXPECT_EQ(s21_test.size(), std_test.size());
  EXPECT_EQ(s21_test.max_size(), std_test.max_size());
  for (std::size_t i = 0; i < 3; i++) {
    EXPECT_EQ(s21_test.at(i), std_test.at(i));
  }
}

TEST(array_test, move_constuctor_big_size) {
  s21::array<int, 10> s21_array = {1, 2, 3};
  s21::array<int, 10> s21_test(std::move(s21_array));
  std::array<int, 10> std_array = {1, 2, 3};
  std::array<int, 10> std_test(std::move(std_array));
  EXPECT_EQ(s21_test.size(), std_test.size());
  EXPECT_EQ(s21_test.max_size(), std_test.max_size());
  for (std::size_t i = 0; i < 3; i++) {
    EXPECT_EQ(s21_test.at(i), std_test.at(i));
  }
}

// -----------Array Element access---------------------

TEST(array_test, at) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  EXPECT_EQ(s21_array.at(0), 1);
  EXPECT_EQ(s21_array.at(1), 2);
  EXPECT_EQ(s21_array.at(2), 3);
}

TEST(array_test, at_char_const) {
  const s21::array<char, 3> s21_array = {'a', 'b', 'c'};
  EXPECT_EQ(s21_array.at(0), 'a');
  EXPECT_EQ(s21_array.at(1), 'b');
  EXPECT_EQ(s21_array.at(2), 'c');
}

TEST(array_test, at_double) {
  s21::array<double, 3> s21_array = {1.23, 2.13, 3.12};
  EXPECT_EQ(s21_array.at(0), 1.23);
  EXPECT_EQ(s21_array.at(1), 2.13);
  EXPECT_EQ(s21_array.at(2), 3.12);
}

TEST(array_test, at_insert) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  s21_array.at(1) = 777;
  EXPECT_EQ(s21_array.at(0), 1);
  EXPECT_EQ(s21_array.at(1), 777);
  EXPECT_EQ(s21_array.at(2), 3);
}

TEST(array_test, at_throw) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  EXPECT_ANY_THROW(s21_array.at(3));
}

TEST(array_test, at_throw_const) {
  const s21::array<int, 3> s21_array = {1, 2, 3};
  EXPECT_ANY_THROW(s21_array.at(3));
}

TEST(array_test, operator_sq_brackets) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  EXPECT_EQ(s21_array[0], 1);
  EXPECT_EQ(s21_array[1], 2);
  EXPECT_EQ(s21_array[2], 3);
}

TEST(array_test, operator_sq_brackets_char_const) {
  const s21::array<char, 3> s21_array = {'a', 'b', 'c'};
  EXPECT_EQ(s21_array[0], 'a');
  EXPECT_EQ(s21_array[1], 'b');
  EXPECT_EQ(s21_array[2], 'c');
}

TEST(array_test, operator_sq_brackets_insert) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  s21_array[1] = 777;
  EXPECT_EQ(s21_array[0], 1);
  EXPECT_EQ(s21_array[1], 777);
  EXPECT_EQ(s21_array[2], 3);
}

TEST(array_test, front) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  EXPECT_EQ(s21_array.front(), 1);
}

TEST(array_test, back) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  EXPECT_EQ(s21_array.back(), 3);
}

TEST(array_test, data) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  auto example = s21_array.data();
  EXPECT_EQ(s21_array.front(), *example);
}

TEST(array_test, data_const) {
  const s21::array<int, 3> s21_array = {1, 2, 3};
  const auto example = s21_array.data();
  EXPECT_EQ(s21_array.front(), *example);
}

// ------------Array Iterators-----------------------

TEST(array_test, begin) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  auto it = s21_array.begin();
  auto it1 = it;
  it1++;
  auto it2 = it1;
  it2++;
  EXPECT_EQ(*it, s21_array[0]);
  EXPECT_EQ(*it1, s21_array[1]);
  EXPECT_EQ(*it2, s21_array[2]);
}

TEST(array_test, begin_front) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  auto example = s21_array.begin();
  EXPECT_EQ(s21_array.front(), *example);
}

TEST(array_test, end) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  auto it = s21_array.end() - 1;
  auto it1 = it;
  it1--;
  auto it2 = it1;
  it2--;
  EXPECT_EQ(*it, s21_array[2]);
  EXPECT_EQ(*it1, s21_array[1]);
  EXPECT_EQ(*it2, s21_array[0]);
}

TEST(array_test, end_back) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  auto example = s21_array.end() - 1;
  EXPECT_EQ(s21_array.back(), *example);
}

// -----------Array Capacity---------------------

TEST(array_test, empty) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  std::array<int, 3> std_array = {1, 2, 3};
  EXPECT_EQ(s21_array.empty(), std_array.empty());
}

TEST(array_test, empty_1) {
  s21::array<int, 3> s21_array;
  std::array<int, 3> std_array;
  EXPECT_EQ(s21_array.empty(), std_array.empty());
}

TEST(array_test, size) {
  s21::array<int, 3> s21_array;
  std::array<int, 3> std_array;
  EXPECT_EQ(s21_array.size(), std_array.size());
}

TEST(array_test, size_1) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  std::array<int, 3> std_array = {1, 2, 3};
  EXPECT_EQ(s21_array.size(), std_array.size());
}

TEST(array_test, size_2) {
  s21::array<int, 10> s21_array = {1, 2, 3};
  std::array<int, 10> std_array = {1, 2, 3};
  EXPECT_EQ(s21_array.size(), std_array.size());
}

TEST(array_test, max_size) {
  s21::array<int, 3> s21_array;
  std::array<int, 3> std_array;
  EXPECT_EQ(s21_array.max_size(), std_array.max_size());
}

TEST(array_test, max_size_1) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  std::array<int, 3> std_array = {1, 2, 3};
  EXPECT_EQ(s21_array.max_size(), std_array.max_size());
}

TEST(array_test, max_size_2) {
  s21::array<int, 10> s21_array = {1, 2, 3};
  std::array<int, 10> std_array = {1, 2, 3};
  EXPECT_EQ(s21_array.max_size(), std_array.max_size());
}

// -------------Array Modifiers--------------------------

TEST(array_test, swap) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  s21::array<int, 3> s21_test = {5, 4, 3};
  s21_array.swap(s21_test);
  std::array<int, 3> std_array = {1, 2, 3};
  std::array<int, 3> std_test = {5, 4, 3};
  std_array.swap(std_test);
  EXPECT_EQ(s21_array.size(), std_array.size());
  EXPECT_EQ(s21_test.size(), std_test.size());

  auto i = 0;
  for (auto it = std_array.begin(); it != std_array.end(); it++) {
    EXPECT_EQ(s21_array.at(i), *it);
    i++;
  }

  auto j = 0;
  for (auto it = std_test.begin(); it != std_test.end(); it++) {
    EXPECT_EQ(s21_test.at(j), *it);
    j++;
  }
}

TEST(array_test, swap_empty) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  s21::array<int, 3> s21_test = {};
  s21_array.swap(s21_test);
  std::array<int, 3> std_array = {1, 2, 3};
  std::array<int, 3> std_test = {};
  std_array.swap(std_test);
  EXPECT_EQ(s21_array.size(), std_array.size());
  EXPECT_EQ(s21_test.size(), std_test.size());

  auto i = 0;
  for (auto it = std_array.begin(); it != std_array.end(); it++) {
    EXPECT_EQ(s21_array.at(i), *it);
    i++;
  }

  auto j = 0;
  for (auto it = std_test.begin(); it != std_test.end(); it++) {
    EXPECT_EQ(s21_test.at(j), *it);
    j++;
  }
}

TEST(array_test, fill) {
  s21::array<int, 3> s21_array;
  s21_array.fill(1);
  std::array<int, 3> std_array;
  std_array.fill(1);
  EXPECT_EQ(s21_array.size(), std_array.size());

  auto i = 0;
  for (auto it = std_array.begin(); it != std_array.end(); it++) {
    EXPECT_EQ(s21_array.at(i), *it);
    i++;
  }
}

TEST(array_test, fill_1) {
  s21::array<int, 3> s21_array = {1};
  s21_array.fill(2);
  std::array<int, 3> std_array = {1};
  std_array.fill(2);
  EXPECT_EQ(s21_array.size(), std_array.size());

  auto i = 0;
  for (auto it = std_array.begin(); it != std_array.end(); it++) {
    EXPECT_EQ(s21_array.at(i), *it);
    i++;
  }
}

TEST(array_test, fill_double) {
  s21::array<double, 3> s21_array = {1.23, 2.13, 3.12};
  s21_array.fill(1);
  std::array<double, 3> std_array = {1.23, 2.13, 3.12};
  std_array.fill(1);
  EXPECT_EQ(s21_array.size(), std_array.size());

  auto i = 0;
  for (auto it = std_array.begin(); it != std_array.end(); it++) {
    EXPECT_EQ(s21_array.at(i), *it);
    i++;
  }
}

TEST(array_test, fill_char) {
  s21::array<char, 3> s21_array = {'a', 'b', 'c'};
  s21_array.fill('a');
  std::array<char, 3> std_array = {'a', 'b', 'c'};
  std_array.fill('a');
  EXPECT_EQ(s21_array.size(), std_array.size());

  auto i = 0;
  for (auto it = std_array.begin(); it != std_array.end(); it++) {
    EXPECT_EQ(s21_array.at(i), *it);
    i++;
  }
}