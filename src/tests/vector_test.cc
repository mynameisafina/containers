#include <gtest/gtest.h>

#include <vector>

#include "../s21_vector.h"

// ------Vector Member functions----------

TEST(vector_test, default_constructor) {
  s21::vector<int> s21_vector;
  EXPECT_EQ(s21_vector.size(), 0);
  EXPECT_EQ(s21_vector.capacity(), 0);
  EXPECT_TRUE(s21_vector.empty());
}

TEST(vector_test, parameterized_constructor) {
  s21::vector<int> s21_vector(3);
  EXPECT_EQ(s21_vector.size(), 3);
  EXPECT_EQ(s21_vector.capacity(), 3);
  EXPECT_FALSE(s21_vector.empty());
}

TEST(vector_test, parameterized_constructor_1) {
  s21::vector<int> s21_vector(0);

  EXPECT_EQ(s21_vector.size(), 0);
  EXPECT_EQ(s21_vector.capacity(), 0);
  EXPECT_EQ(s21_vector.data(), nullptr);
  EXPECT_TRUE(s21_vector.empty());
}

TEST(vector_test, initializer_list) {
  s21::vector<int> s21_vector = {1, 2, 3};
  EXPECT_EQ(s21_vector.size(), 3);
  EXPECT_EQ(s21_vector.capacity(), 3);
  EXPECT_EQ(s21_vector.front(), 1);
  EXPECT_EQ(s21_vector.back(), 3);
  EXPECT_EQ(s21_vector.at(1), 2);
  EXPECT_FALSE(s21_vector.empty());
}

TEST(vector_test, initializer_list_1) {
  s21::vector<int> s21_vector = {};

  EXPECT_EQ(s21_vector.size(), 0);
  EXPECT_EQ(s21_vector.capacity(), 0);
  EXPECT_EQ(s21_vector.data(), nullptr);
  EXPECT_TRUE(s21_vector.empty());
}

TEST(vector_test, copy_constructor) {
  s21::vector<int> s21_vector = {1, 2, 3};
  s21::vector<int> t_vector(s21_vector);
  EXPECT_EQ(s21_vector.size(), t_vector.size());
  EXPECT_EQ(s21_vector.capacity(), t_vector.capacity());
  EXPECT_EQ(s21_vector.front(), t_vector.front());
  EXPECT_EQ(s21_vector.back(), t_vector.back());
  EXPECT_EQ(s21_vector.at(1), t_vector.at(1));
  EXPECT_EQ(s21_vector.empty(), t_vector.empty());
}

TEST(vector_test, move_constructor) {
  s21::vector<int> s21_vector = {1, 2, 3};
  s21::vector<int> t_vector(std::move(s21_vector));
  EXPECT_EQ(t_vector.size(), 3);
  EXPECT_EQ(t_vector.capacity(), 3);
  EXPECT_EQ(t_vector.front(), 1);
  EXPECT_EQ(t_vector.back(), 3);
  EXPECT_EQ(t_vector.at(1), 2);
  EXPECT_NE(t_vector.data(), nullptr);
  EXPECT_FALSE(t_vector.empty());

  EXPECT_EQ(s21_vector.size(), 0);
  EXPECT_EQ(s21_vector.capacity(), 0);
  EXPECT_EQ(s21_vector.data(), nullptr);
  EXPECT_TRUE(s21_vector.empty());
}

// ------Vector Element access---------------

TEST(vector_test, at) {
  s21::vector<int> s21_vector = {1, 2, 3};
  EXPECT_EQ(s21_vector.at(0), 1);
  EXPECT_EQ(s21_vector.at(1), 2);
  EXPECT_EQ(s21_vector.at(2), 3);
}

TEST(vector_test, at_char_const) {
  const s21::vector<char> s21_vector = {'a', 'b', 'c'};
  EXPECT_EQ(s21_vector.at(0), 'a');
  EXPECT_EQ(s21_vector.at(1), 'b');
  EXPECT_EQ(s21_vector.at(2), 'c');
}

TEST(vector_test, at_insert) {
  s21::vector<int> s21_vector = {1, 2, 3};
  s21_vector.at(1) = 777;
  EXPECT_EQ(s21_vector.at(0), 1);
  EXPECT_EQ(s21_vector.at(1), 777);
  EXPECT_EQ(s21_vector.at(2), 3);
}

TEST(vector_test, at_throw) {
  s21::vector<int> s21_vector = {1, 2, 3};
  EXPECT_ANY_THROW(s21_vector.at(3));
}

TEST(vector_test, at_throw_const) {
  const s21::vector<int> s21_vector = {1, 2, 3};
  EXPECT_ANY_THROW(s21_vector.at(3));
}

TEST(vector_test, operator_sq_brackets) {
  s21::vector<int> s21_vector = {1, 2, 3};
  EXPECT_EQ(s21_vector[0], 1);
  EXPECT_EQ(s21_vector[1], 2);
  EXPECT_EQ(s21_vector[2], 3);
}

TEST(vector_test, operator_sq_brackets_char_const) {
  const s21::vector<char> s21_vector = {'a', 'b', 'c'};
  EXPECT_EQ(s21_vector[0], 'a');
  EXPECT_EQ(s21_vector[1], 'b');
  EXPECT_EQ(s21_vector[2], 'c');
}

TEST(vector_test, operator_sq_brackets_insert) {
  s21::vector<int> s21_vector = {1, 2, 3};
  s21_vector[1] = 777;
  EXPECT_EQ(s21_vector[0], 1);
  EXPECT_EQ(s21_vector[1], 777);
  EXPECT_EQ(s21_vector[2], 3);
}

TEST(vector_test, front) {
  s21::vector<int> s21_vector = {1, 2, 3};
  EXPECT_EQ(s21_vector.front(), 1);
}

TEST(vector_test, front_throw) {
  s21::vector<int> s21_vector;
  EXPECT_ANY_THROW(s21_vector.front());
}

TEST(vector_test, back) {
  s21::vector<int> s21_vector = {1, 2, 3};
  EXPECT_EQ(s21_vector.back(), 3);
}

TEST(vector_test, back_throw) {
  s21::vector<int> s21_vector;
  EXPECT_ANY_THROW(s21_vector.back());
}

TEST(vector_test, data) {
  s21::vector<int> s21_vector = {1, 2, 3};
  auto example = s21_vector.data();
  EXPECT_EQ(s21_vector.front(), *example);
}

TEST(vector_test, data_const) {
  const s21::vector<int> s21_vector = {1, 2, 3};
  const auto example = s21_vector.data();
  EXPECT_EQ(s21_vector.front(), *example);
}

TEST(vector_test, data_empty) {
  s21::vector<int> s21_vector;
  EXPECT_EQ(s21_vector.data(), nullptr);
}

// -----------Vector Iterators-----------------

TEST(vector_test, begin) {
  s21::vector<int> s21_vector = {1, 2, 3};
  auto example = s21_vector.begin();
  EXPECT_EQ(s21_vector.front(), *example);
}

TEST(vector_test, begin_empty) {
  s21::vector<int> s21_vector;
  EXPECT_EQ(s21_vector.begin(), nullptr);
}

TEST(vector_test, end) {
  s21::vector<int> s21_vector = {1, 2, 3};
  auto example = s21_vector.end() - 1;
  EXPECT_EQ(s21_vector.back(), *example);
}

TEST(vector_test, end_empty) {
  s21::vector<int> s21_vector;
  EXPECT_EQ(s21_vector.end(), nullptr);
}

// ---------Vector Capacity-------------------

TEST(vector_test, empty) {
  s21::vector<int> s21_vector;
  EXPECT_TRUE(s21_vector.empty());
}

TEST(vector_test, not_empty) {
  s21::vector<int> s21_vector = {1, 2, 3};
  EXPECT_FALSE(s21_vector.empty());
}

TEST(vector_test, size) {
  s21::vector<int> s21_vector = {1, 2, 3};
  EXPECT_EQ(s21_vector.size(), 3);
}

TEST(vector_test, size_empty) {
  s21::vector<int> s21_vector;
  EXPECT_EQ(s21_vector.size(), 0);
}

TEST(vector_test, max_size_int) {
  s21::vector<int> s21_v_int;
  std::vector<int> std_v_int;
  EXPECT_EQ(s21_v_int.max_size(), std_v_int.max_size());
}

TEST(vector_test, max_size_char) {
  s21::vector<char> s21_v_char;
  std::vector<char> std_v_char;
  EXPECT_EQ(s21_v_char.max_size(), std_v_char.max_size());
}

TEST(vector_test, max_size_double) {
  s21::vector<double> s21_v_double;
  std::vector<double> std_v_double;
  EXPECT_EQ(s21_v_double.max_size(), std_v_double.max_size());
}

TEST(vector_test, reserve) {
  s21::vector<int> s21_vector = {1, 2, 3};
  s21_vector.reserve(6);
  std::vector<int> std_vector = {1, 2, 3};
  std_vector.reserve(6);
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  auto i = 0;
  for (auto it = std_vector.begin(); it != std_vector.end(); it++) {
    EXPECT_EQ(s21_vector.at(i), *it);
    i++;
  }
}

TEST(vector_test, reserve_max_size) {
  s21::vector<int> s21_vector(3);
  EXPECT_ANY_THROW(s21_vector.reserve(2305843009213693952));
}

TEST(vector_test, shrink_to_fit) {
  s21::vector<int> s21_vector = {1, 2, 3};
  s21_vector.reserve(10);
  std::vector<int> std_vector = {1, 2, 3};
  std_vector.reserve(10);
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());

  s21_vector.shrink_to_fit();
  std_vector.shrink_to_fit();
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  auto i = 0;
  for (auto it = std_vector.begin(); it != std_vector.end(); it++) {
    EXPECT_EQ(s21_vector.at(i), *it);
    i++;
  }
}

// -----------Vector Modifiers---------------------------------

TEST(vector_test, clear) {
  s21::vector<int> s21_vector = {1, 2, 3};
  s21_vector.clear();
  std::vector<int> std_vector = {1, 2, 3};
  std_vector.clear();
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
}

TEST(vector_test, insert_begin) {
  s21::vector<int> s21_vector = {1, 2, 3};
  s21_vector.insert(s21_vector.begin(), 100);
  std::vector<int> std_vector = {1, 2, 3};
  std_vector.insert(std_vector.begin(), 100);
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());

  auto i = 0;
  for (auto it = std_vector.begin(); it != std_vector.end(); it++) {
    EXPECT_EQ(s21_vector.at(i), *it);
    i++;
  }
}

TEST(vector_test, insert_begin_char) {
  s21::vector<char> s21_vector = {'a', 'b', 'c'};
  s21_vector.insert(s21_vector.begin(), 'd');
  std::vector<char> std_vector = {'a', 'b', 'c'};
  std_vector.insert(std_vector.begin(), 'd');
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());

  auto i = 0;
  for (auto it = std_vector.begin(); it != std_vector.end(); it++) {
    EXPECT_EQ(s21_vector.at(i), *it);
    i++;
  }
}

TEST(vector_test, insert_end) {
  s21::vector<int> s21_vector = {1, 2, 3};
  s21_vector.insert(s21_vector.end(), 100);
  std::vector<int> std_vector = {1, 2, 3};
  std_vector.insert(std_vector.end(), 100);
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());

  auto i = 0;
  for (auto it = std_vector.begin(); it != std_vector.end(); it++) {
    EXPECT_EQ(s21_vector.at(i), *it);
    i++;
  }
}

TEST(vector_test, insert_middle) {
  s21::vector<int> s21_vector = {1, 2, 3};
  s21_vector.insert(s21_vector.begin() + 1, 100);
  std::vector<int> std_vector = {1, 2, 3};
  std_vector.insert(std_vector.begin() + 1, 100);
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());

  auto i = 0;
  for (auto it = std_vector.begin(); it != std_vector.end(); it++) {
    EXPECT_EQ(s21_vector.at(i), *it);
    i++;
  }
}

TEST(vector_test, insert_throw_before_begin) {
  s21::vector<int> s21_vector = {1, 2, 3};
  EXPECT_ANY_THROW(s21_vector.insert(s21_vector.begin() - 1, 100));
}

TEST(vector_test, insert_throw_after_end) {
  s21::vector<int> s21_vector = {1, 2, 3};
  EXPECT_ANY_THROW(s21_vector.insert(s21_vector.end() + 1, 100));
}

TEST(vector_test, erase_begin) {
  s21::vector<int> s21_vector = {1, 2, 3};
  s21_vector.erase(s21_vector.begin());
  std::vector<int> std_vector = {1, 2, 3};
  std_vector.erase(std_vector.begin());
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());

  auto i = 0;
  for (auto it = std_vector.begin(); it != std_vector.end(); it++) {
    EXPECT_EQ(s21_vector.at(i), *it);
    i++;
  }
}

TEST(vector_test, erase_begin_char) {
  s21::vector<char> s21_vector = {'a', 'b', 'c'};
  s21_vector.erase(s21_vector.begin());
  std::vector<char> std_vector = {'a', 'b', 'c'};
  std_vector.erase(std_vector.begin());
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());

  auto i = 0;
  for (auto it = std_vector.begin(); it != std_vector.end(); it++) {
    EXPECT_EQ(s21_vector.at(i), *it);
    i++;
  }
}

TEST(vector_test, erase_end) {
  s21::vector<int> s21_vector = {1, 2, 3};
  s21_vector.erase(s21_vector.end() - 1);
  std::vector<int> std_vector = {1, 2, 3};
  std_vector.erase(std_vector.end() - 1);
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());

  auto i = 0;
  for (auto it = std_vector.begin(); it != std_vector.end(); it++) {
    EXPECT_EQ(s21_vector.at(i), *it);
    i++;
  }
}

TEST(vector_test, erase_middle) {
  s21::vector<int> s21_vector = {1, 2, 3};
  s21_vector.erase(s21_vector.end() - 2);
  std::vector<int> std_vector = {1, 2, 3};
  std_vector.erase(std_vector.end() - 2);
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());

  auto i = 0;
  for (auto it = std_vector.begin(); it != std_vector.end(); it++) {
    EXPECT_EQ(s21_vector.at(i), *it);
    i++;
  }
}

TEST(vector_test, erase_throw_before_begin) {
  s21::vector<int> s21_vector = {1, 2, 3};
  EXPECT_ANY_THROW(s21_vector.erase(s21_vector.begin() - 2));
}

TEST(vector_test, erase_throw_after_end) {
  s21::vector<int> s21_vector = {1, 2, 3};
  EXPECT_ANY_THROW(s21_vector.erase(s21_vector.end() + 2));
}

TEST(vector_test, push_back_eq) {
  s21::vector<int> s21_vector = {1, 2, 3};
  s21_vector.push_back(100);
  std::vector<int> std_vector = {1, 2, 3};
  std_vector.push_back(100);
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());

  auto i = 0;
  for (auto it = std_vector.begin(); it != std_vector.end(); it++) {
    EXPECT_EQ(s21_vector.at(i), *it);
    i++;
  }
}

TEST(vector_test, push_back_eq_char) {
  s21::vector<char> s21_vector = {'a', 'b', 'c'};
  s21_vector.push_back(100);
  std::vector<char> std_vector = {'a', 'b', 'c'};
  std_vector.push_back(100);
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());

  auto i = 0;
  for (auto it = std_vector.begin(); it != std_vector.end(); it++) {
    EXPECT_EQ(s21_vector.at(i), *it);
    i++;
  }
}

TEST(vector_test, push_back_not_eq) {
  s21::vector<int> s21_vector = {1, 2, 3};
  s21_vector.reserve(4);
  s21_vector.push_back(100);
  std::vector<int> std_vector = {1, 2, 3};
  std_vector.reserve(4);
  std_vector.push_back(100);
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());

  auto i = 0;
  for (auto it = std_vector.begin(); it != std_vector.end(); it++) {
    EXPECT_EQ(s21_vector.at(i), *it);
    i++;
  }
}

TEST(vector_test, push_back_negative) {
  s21::vector<int> s21_vector = {1, 2, 3};
  s21_vector.push_back(-100);
  std::vector<int> std_vector = {1, 2, 3};
  std_vector.push_back(-100);
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());

  auto i = 0;
  for (auto it = std_vector.begin(); it != std_vector.end(); it++) {
    EXPECT_EQ(s21_vector.at(i), *it);
    i++;
  }
}

TEST(vector_test, push_back_double) {
  s21::vector<double> s21_vector = {1, 2, 3};
  s21_vector.push_back(12.21);
  std::vector<double> std_vector = {1, 2, 3};
  std_vector.push_back(12.21);
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());

  auto i = 0;
  for (auto it = std_vector.begin(); it != std_vector.end(); it++) {
    EXPECT_EQ(s21_vector.at(i), *it);
    i++;
  }
}

TEST(vector_test, push_back_repeatedly) {
  s21::vector<double> s21_vector = {1, 2, 3};
  size_t sz = 10;
  while (sz-- > 0) {
    s21_vector.push_back(12.21);
  }
  std::vector<double> std_vector = {1, 2, 3};
  size_t sz2 = 10;
  while (sz2-- > 0) {
    std_vector.push_back(12.21);
  }
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());

  auto i = 0;
  for (auto it = std_vector.begin(); it != std_vector.end(); it++) {
    EXPECT_EQ(s21_vector.at(i), *it);
    i++;
  }
}

TEST(vector_test, pop_back) {
  s21::vector<int> s21_vector = {1, 2, 3};
  s21_vector.pop_back();
  std::vector<int> std_vector = {1, 2, 3};
  std_vector.pop_back();
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());

  auto i = 0;
  for (auto it = std_vector.begin(); it != std_vector.end(); it++) {
    EXPECT_EQ(s21_vector.at(i), *it);
    i++;
  }
}

TEST(vector_test, pop_back_char) {
  s21::vector<char> s21_vector = {'a', 'b', 'c'};
  s21_vector.pop_back();
  std::vector<char> std_vector = {'a', 'b', 'c'};
  std_vector.pop_back();
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());

  auto i = 0;
  for (auto it = std_vector.begin(); it != std_vector.end(); it++) {
    EXPECT_EQ(s21_vector.at(i), *it);
    i++;
  }
}

TEST(vector_test, pop_back_throw) {
  s21::vector<int> s21_vector;
  EXPECT_ANY_THROW(s21_vector.pop_back());
}

TEST(vector_test, swap) {
  s21::vector<int> s21_vector = {1, 2, 3};
  s21::vector<int> s21_test = {500, 400, 300, 200, 100};
  s21_vector.swap(s21_test);
  std::vector<int> std_vector = {1, 2, 3};
  std::vector<int> std_test = {500, 400, 300, 200, 100};
  std_vector.swap(std_test);
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_test.size(), std_test.size());
  EXPECT_EQ(s21_test.capacity(), std_test.capacity());

  auto i = 0;
  for (auto it = std_vector.begin(); it != std_vector.end(); it++) {
    EXPECT_EQ(s21_vector.at(i), *it);
    i++;
  }

  auto j = 0;
  for (auto it = std_test.begin(); it != std_test.end(); it++) {
    EXPECT_EQ(s21_test.at(j), *it);
    j++;
  }
}

// -----------Vector Emplace---------------------------------

TEST(vector_test, emplace_begin) {
  s21::vector<int> s21_vector = {1, 2, 3};
  auto s21_it = s21_vector.begin();
  s21_vector.emplace(s21_it, 0);

  std::vector<int> std_vector = {1, 2, 3};
  auto std_it = std_vector.begin();
  std_vector.emplace(std_it, 0);

  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  auto i = 0;
  for (auto it = std_vector.begin(); it != std_vector.end(); it++) {
    EXPECT_EQ(s21_vector.at(i), *it);
    i++;
  }
}

TEST(vector_test, emplace_middle) {
  s21::vector<int> s21_vector = {1, 2, 3};
  auto s21_it = s21_vector.begin();
  s21_it++;
  s21_vector.emplace(s21_it, 9, 8, 7);
  std::vector<int> std_vector = {1, 9, 8, 7, 2, 3};

  auto i = 0;
  for (auto it = std_vector.begin(); it != std_vector.end(); it++) {
    EXPECT_EQ(s21_vector.at(i), *it);
    i++;
  }
}

TEST(vector_test, emplace_back) {
  s21::vector<int> s21_vector = {1, 2, 3};
  s21_vector.emplace_back(4);
  std::vector<int> std_vector = {1, 2, 3};
  std_vector.emplace_back(4);

  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  auto i = 0;
  for (auto it = std_vector.begin(); it != std_vector.end(); it++) {
    EXPECT_EQ(s21_vector.at(i), *it);
    i++;
  }
}

TEST(vector_test, emplace_back_1) {
  s21::vector<int> s21_vector = {1, 2, 3};
  s21_vector.emplace_back(4, 5, 6);
  std::vector<int> std_vector = {1, 2, 3, 4, 5, 6};

  auto i = 0;
  for (auto it = std_vector.begin(); it != std_vector.end(); it++) {
    EXPECT_EQ(s21_vector.at(i), *it);
    i++;
  }
}
