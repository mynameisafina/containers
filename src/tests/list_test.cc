#include <gtest/gtest.h>

#include <list>
#include <random>

#include "../s21_containers.h"

TEST(list_test, create_and_size) {
  s21::list<double> A;
  EXPECT_EQ(A.size(), 0);
  const s21::list<double> B(7);
  EXPECT_EQ(B.size(), 7);
  s21::list<double> C = {1.78, 0.99, -1.53};
  EXPECT_EQ(C.size(), 3);
  s21::list<char> D = {'C', 'A', 'T'};
  EXPECT_EQ(D.size(), 3);
}

TEST(list_test, create_and_iter_1) {
  s21::list<double> A = {1.78, 0.99, -1.53};
  s21::list<double> B = A;
  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (int i = 0; i < 3; i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(list_test, create_and_iter_2) {
  const s21::list<double> A = {1.78, 0.99, -1.53};
  s21::list<double> A2 = A;
  EXPECT_EQ(A2.size(), 3);
  s21::list<double> B = std::move(A2);
  EXPECT_EQ(B.size(), 3);
  EXPECT_EQ(A2.size(), 0);
  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (int i = 0; i < 3; i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(list_test, create_and_iter_3) {
  s21::list<std::string> A = {"Cats", "are", "the", "best"};
  s21::list<std::string> B = A;
  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (std::size_t i = 0; i < A.size(); i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(list_test, create_and_iter_4) {
  const s21::list<std::string> A = {"Cats", "are", "the", "best"};
  s21::list<std::string> A2 = A;
  EXPECT_EQ(A2.size(), 4);
  s21::list<std::string> B = std::move(A2);
  EXPECT_EQ(B.size(), 4);
  EXPECT_EQ(A2.size(), 0);
  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (std::size_t i = 0; i < 4; i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(list_test, create_list_1) {
  std::initializer_list<double> L = {1.78, 0.99, -1.53};
  s21::list<double> A = L;
  std::list<double> B = L;
  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (int i = 0; i < 3; i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(list_test, create_list_2) {
  std::initializer_list<std::string> L = {"Cats", "are", "the", "best"};
  s21::list<std::string> A = L;
  std::list<std::string> B = L;
  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (std::size_t i = 0; i < A.size(); i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(list_test, assignment_copy_1) {
  const s21::list<double> A = {1.78, 0.99, -1.53};
  s21::list<double> B;
  EXPECT_EQ(B.size(), 0);
  B = A;
  EXPECT_EQ(B.size(), 3);
  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (int i = 0; i < 3; i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(list_test, assignment_copy_2) {
  const s21::list<std::string> A = {"Cats", "are", "the", "best"};
  s21::list<std::string> B;
  EXPECT_EQ(B.size(), 0);
  B = A;
  EXPECT_EQ(B.size(), A.size());
  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (std::size_t i = 0; i < A.size(); i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(list_test, assignment_move_1) {
  s21::list<double> A = {1.78, 0.99, -1.53};
  s21::list<double> A2 = A;
  EXPECT_EQ(A2.size(), 3);
  s21::list<double> B;
  EXPECT_EQ(B.size(), 0);
  B = std::move(A2);
  EXPECT_EQ(B.size(), 3);
  EXPECT_EQ(A2.size(), 0);
  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (int i = 0; i < 3; i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(list_test, assignment_move_2) {
  s21::list<std::string> A = {"Cats", "are", "the", "best"};
  s21::list<std::string> A2 = A;
  EXPECT_EQ(A2.size(), A.size());
  s21::list<std::string> B;
  EXPECT_EQ(B.size(), 0);
  B = std::move(A2);
  EXPECT_EQ(B.size(), A.size());
  EXPECT_EQ(A2.size(), 0);
  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (std::size_t i = 0; i < A.size(); i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(list_test, front_back_1) {
  std::initializer_list<double> L = {1.78, 0.99, -1.53};
  s21::list<double> A = L;
  std::list<double> B = L;
  EXPECT_EQ(A.front(), B.front());
  EXPECT_EQ(A.back(), B.back());
}

TEST(list_test, front_back_2) {
  std::initializer_list<char> L = {'C', 'A', 'T'};
  s21::list<char> A = L;
  std::list<char> B = L;
  EXPECT_EQ(A.front(), B.front());
  EXPECT_EQ(A.back(), B.back());
}

TEST(list_test, front_back_const) {
  std::initializer_list<double> L = {1.78, 0.99, -1.53};
  const s21::list<double> A = L;
  const std::list<double> B = L;
  EXPECT_EQ(A.front(), B.front());
  EXPECT_EQ(A.back(), B.back());
}

TEST(list_test, begin_end_1) {
  std::initializer_list<double> L = {1.78, 0.99, -1.53};
  s21::list<double> A = L;
  std::list<double> B = L;
  EXPECT_EQ(*A.begin(), *B.begin());
  EXPECT_EQ(*(--A.end()), *(--B.end()));
}

TEST(list_test, begin_end_2) {
  std::initializer_list<std::string> L = {"Cats", "are", "the", "best"};
  s21::list<std::string> A = L;
  std::list<std::string> B = L;
  EXPECT_EQ(*A.begin(), *B.begin());
  EXPECT_EQ(*(--A.end()), *(--B.end()));
}

TEST(list_test, const_begin_end) {
  std::initializer_list<double> L = {1.78, 0.99, -1.53};
  const s21::list<double> A = L;
  const std::list<double> B = L;
  EXPECT_EQ(*(++A.begin()), *(++B.begin()));
  EXPECT_EQ(*(--A.end()), *(--B.end()));
}

TEST(list_test, empty) {
  s21::list<double> A;
  ASSERT_TRUE(A.empty());
  const s21::list<double> B(7);
  ASSERT_FALSE(B.empty());
  s21::list<double> C = {1.78, 0.99, -1.53};
  ASSERT_FALSE(C.empty());
  C = A;
  ASSERT_TRUE(C.empty());
}

TEST(list_test, max_size) {
  const s21::list<int> A;
  const std::list<int> B;
  EXPECT_EQ(A.max_size(), B.max_size());

  s21::list<double> A1;
  std::list<double> B1;
  EXPECT_EQ(A1.max_size(), B1.max_size());

  s21::list<std::string> A2;
  std::list<std::string> B2;
  EXPECT_EQ(A1.max_size(), B1.max_size());
}

TEST(list_test, clear) {
  std::initializer_list<double> L = {1.78, 0.99, -1.53};
  s21::list<double> A = L;
  A.clear();
  ASSERT_TRUE(A.empty());
  EXPECT_EQ(A.size(), 0);
}

TEST(list_test, insert_1) {
  s21::list<int> A;
  std::list<int> B;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(1, 100000);
  int elem;
  for (int n = 0; n < 10; ++n) {
    elem = dist(gen);
    A.insert(A.begin(), elem);
    B.insert(B.begin(), elem);
  }

  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (int i = 0; i < 10; i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(list_test, insert_2) {
  s21::list<double> A;
  std::list<double> B;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-10.0, 10.0);
  double elem;
  for (int n = 0; n < 10; ++n) {
    elem = dis(gen);
    A.insert(A.begin(), elem);
    B.insert(B.begin(), elem);
  }

  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (int i = 0; i < 10; i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(list_test, erase) {
  std::initializer_list<double> L = {1.78, 0.99, -1.53, 4.88, 111.303, -43.5};
  s21::list<double> A = L;
  std::list<double> B = L;
  A.erase(++A.begin());
  A.erase(--(--A.end()));
  B.erase(++B.begin());
  B.erase(--(--B.end()));

  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (std::size_t i = 0; i < L.size() - 2; i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(list_test, push_back) {
  s21::list<double> A;
  std::list<double> B;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-10.0, 10.0);
  double elem;
  for (int n = 0; n < 10; ++n) {
    elem = dis(gen);
    A.push_back(elem);
    B.push_back(elem);
  }

  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (int i = 0; i < 10; i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(list_test, push_front) {
  s21::list<double> A;
  std::list<double> B;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-10.0, 10.0);
  double elem;
  for (int n = 0; n < 10; ++n) {
    elem = dis(gen);
    A.push_front(elem);
    B.push_front(elem);
  }

  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (int i = 0; i < 10; i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(list_test, pop_back_front) {
  std::initializer_list<double> L = {1.78, 0.99, -1.53, 4.88, 111.303, -43.5};
  s21::list<double> A = L;
  std::list<double> B = L;
  A.pop_back();
  A.pop_front();
  B.pop_back();
  B.pop_front();

  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (std::size_t i = 0; i < L.size() - 2; i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(list_test, swap) {
  std::initializer_list<double> L = {1.78, 0.99, -1.53, 4.88, 111.303, -43.5};
  s21::list<double> A = L;
  std::list<double> B = L;
  std::initializer_list<double> L2 = {-9.87, -6.5, -4.321, 0.12, 3, 4567, 8.9};
  s21::list<double> A2 = L2;
  std::list<double> B2 = L2;
  A.swap(A2);
  B.swap(B2);

  auto iter_A = A.begin();
  auto iter_B = B.begin();
  auto iter_A2 = A2.begin();
  auto iter_B2 = B2.begin();
  for (std::size_t i = 0; i < L.size();
       i++, ++iter_A, ++iter_B, ++iter_A2, ++iter_B2) {
    EXPECT_EQ(*iter_A, *iter_B);
    EXPECT_EQ(*iter_A2, *iter_B2);
  }
}

TEST(list_test, merge) {
  std::initializer_list<double> L = {1.78, 0.99, -1.53, 4.88, 111.303, -43.5};
  s21::list<double> A = L;
  std::list<double> B = L;
  std::initializer_list<double> L2 = {-9.87, -6.5, -4.321, 0.12, 3, 4567, 8.9};
  s21::list<double> A2 = L2;
  std::list<double> B2 = L2;
  A.merge(A2);
  B.merge(B2);

  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (std::size_t i = 0; i < L.size() * 2; i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(list_test, splice) {
  std::initializer_list<double> L = {1.78, 0.99, -1.53, 4.88, 111.303, -43.5};
  s21::list<double> A = L;
  std::list<double> B = L;
  std::initializer_list<double> L2 = {-9.87, -6.5, -4.321, 0.12, 3, 4567, 8.9};
  s21::list<double> A2 = L2;
  std::list<double> B2 = L2;
  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (std::size_t i = 0; i < L.size() / 2; i++, ++iter_A, ++iter_B) {
  }
  A.splice(iter_A, A2);
  B.splice(iter_B, B2);

  iter_A = A.begin();
  iter_B = B.begin();
  for (std::size_t i = 0; i < L.size() * 2; i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(list_test, reverse) {
  s21::list<double> A;
  std::list<double> B;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-10.0, 10.0);
  double elem;
  for (int n = 0; n < 10; ++n) {
    elem = dis(gen);
    A.push_back(elem);
    B.push_back(elem);
  }
  A.reverse();
  B.reverse();

  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (int i = 0; i < 10; i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(list_test, unique) {
  std::initializer_list<double> L = {1.78,    0.99,    -1.53, -1.53,
                                     4.88,    4.88,    0.99,  111.303,
                                     111.303, 111.303, -1.53, -43.5};
  s21::list<double> A = L;
  std::list<double> B = L;
  A.unique();
  B.unique();

  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (std::size_t i = 0; i < B.size(); i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(list_test, sort_1) {
  s21::list<double> A;
  std::list<double> B;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-10.0, 10.0);
  double elem;
  for (int n = 0; n < 10; ++n) {
    elem = dis(gen);
    A.push_back(elem);
    B.push_back(elem);
  }
  A.sort();
  B.sort();

  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (int i = 0; i < 10; i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(list_test, sort_2) {
  std::initializer_list<double> L = {1.78,    0.99,    -1.53, -1.53,
                                     4.88,    4.88,    0.99,  111.303,
                                     111.303, 111.303, -1.53, -43.5};
  s21::list<double> A = L;
  std::list<double> B = L;
  A.sort();
  B.sort();

  auto iter_A = A.begin();
  auto iter_B = B.begin();
  for (std::size_t i = 0; i < B.size(); i++, ++iter_A, ++iter_B) {
    EXPECT_EQ(*iter_A, *iter_B);
  }
}

TEST(list_test, front_0) {
  s21::list<int> a = {1, 2, 3};
  std::list<int> b = {1, 2, 3};
  auto it1 = a.front();
  auto i = b.front();
  EXPECT_EQ(it1, i);
}

TEST(list_test, size_0) {
  s21::list<int> a = {1, 2, 3, 5, 6};
  s21::list<int> b(5);
  s21::list<int> c = a;
  auto a1 = a.size();
  EXPECT_EQ(a1, 5);
  s21::list<int> d = {1, 2, 3, 5, 6, 9, 0};
  d = a;
  s21::list<int> test1 = {1, 2, 3, 5, 6};
  s21::list<int> test2(5);
  test1 = test2;
  EXPECT_EQ(test1.size(), test2.size());
}

TEST(list_test, size2_0) {
  s21::list<int> a;
  auto a1 = a.size();
  EXPECT_EQ(a1, 0);
}

TEST(list_test, is_empty_true_0) {
  s21::list<int> a;
  auto a1 = a.empty();
  ASSERT_TRUE(a1);
}

TEST(list_test, is_empty_false_0) {
  s21::list<int> a = {1, 23, 43};
  auto a1 = a.empty();
  ASSERT_FALSE(a1);
}

TEST(list_test, back_0) {
  s21::list<int> a = {1, 23, 43, 3};
  auto a1 = a.back();
  EXPECT_EQ(a1, 3);
}

TEST(list_test, back2_0) {
  s21::list<int> a = {};
  auto a1 = a.back();
  EXPECT_EQ(a1, 0);
}

TEST(list_test, push_front1_0) {
  s21::list<int> a = {};
  a.push_front(1);
  a.push_front(3);
  a.push_front(5);
  std::list<int> b = {5, 3, 1};
  auto i = b.begin();
  for (auto it = a.begin(); it != a.end(); ++it) {
    EXPECT_EQ(*it, *i);
    ++i;
  }
}

TEST(list_test, push_front2_0) {
  s21::list<int> a = {};
  a.push_front(1);
  a.push_front(3);
  a.push_front(5);
  a.push_front(5);
  a.push_front(5);
  std::list<int> b = {5, 5, 5, 3, 1};
  auto i = b.begin();
  for (auto it = a.begin(); it != a.end(); ++it) {
    EXPECT_EQ(*it, *i);
    ++i;
  }
}

TEST(list_test, push_back_1_pop_0) {
  s21::list<int> a = {};
  a.push_back(1);
  a.push_back(2);
  a.push_back(3);
  std::list<int> b = {1, 2, 3};
  auto i = b.begin();
  for (auto it = a.begin(); it != a.end(); ++it) {
    EXPECT_EQ(*it, *i);
    ++i;
  }
  a.pop_back();
  b = {1, 2};
  auto it3 = b.begin();
  for (auto it = a.begin(); it != a.end(); ++it) {
    EXPECT_EQ(*it, *it3);
    ++it3;
  }
}

TEST(list_test, push_back_2_pop_0) {
  s21::list<int> a;
  a.push_back(1);
  std::list<int> b = {1};
  auto i = b.begin();
  for (auto it = a.begin(); it != a.end(); ++it) {
    EXPECT_EQ(*it, *i);
    ++i;
  }
  a.pop_back();
  EXPECT_EQ(a.empty(), true);
}

TEST(list_test, pop_front_0) {
  s21::list<int> a;
  a.push_front(1);
  a.push_front(321);
  a.pop_front();
  s21::list<int> b = {1};
  auto i = b.begin();
  for (auto it = a.begin(); it != a.end(); ++it) {
    EXPECT_EQ(*it, *i);
    ++i;
  }
}

TEST(list_test, swap_1_0) {
  s21::list<int> a1 = {0, 2, 4, 6};
  s21::list<int> a2 = {6, 4, 2, 0};
  a1.swap(a2);
  std::list<int> a3 = {0, 2, 4, 6};
  std::list<int> a4 = {6, 4, 2, 0};
  a4.swap(a3);
  auto it_original = a3.begin();
  for (auto it = a1.begin(); it != a1.end(); ++it) {
    EXPECT_EQ(*it_original, *it);
    it_original++;
  }
}

TEST(list_test, reverse_0) {
  s21::list<int> a1 = {0, 2, 4, 6};
  std::list<int> a2 = {0, 2, 4, 6};
  a1.reverse();
  a2.reverse();
  auto it = a1.begin();
  for (auto it_original = a2.begin(); it_original != a2.end(); ++it_original) {
    EXPECT_EQ(*it_original, *it);
    it++;
  }
}

TEST(list_test, max_size_2_0) {
  s21::list<int> a1;
  std::list<int> a2;
  EXPECT_EQ(a1.max_size(), a2.max_size());
}

TEST(tests_of_List, unique_1_0) {
  s21::list<int> a = {0, 1, 254, 333, 333, 12, 1};
  std::list<int> b = {0, 1, 254, 333, 333, 12, 1};
  a.unique();
  b.unique();
  auto it = a.begin();
  for (auto i = b.begin(); i != b.end(); ++i) {
    EXPECT_EQ(*it, *i);
    ++it;
  }
}

TEST(list_test, unique_2_0) {
  s21::list<int> a = {0, 0, 0, 0, 0, 0};
  std::list<int> b = {0, 0, 0, 0, 0, 0};
  a.unique();
  b.unique();
  auto it = a.begin();
  for (auto i = b.begin(); i != b.end(); ++i) {
    EXPECT_EQ(*it, *i);
    ++it;
  }
}

TEST(list_test, unique_3_0) {
  s21::list<int> a = {5, 4, 3, 2, 1, 5};
  std::list<int> b = {5, 4, 3, 2, 1, 5};
  a.unique();
  b.unique();
  auto it = a.begin();
  for (auto i = b.begin(); i != b.end(); ++i) {
    EXPECT_EQ(*it, *i);
    ++it;
  }
}

TEST(list_test, insert_0) {
  s21::list<int> a = {-1, 0, 2};
  std::list<int> b = {-1, 0, 2};
  auto i = a.begin();
  auto it_std = b.begin();
  auto it_std_2 = a.insert(i, -2);
  auto i2 = b.insert(it_std, -2);
  EXPECT_EQ(*it_std_2, *i2);
}

TEST(list_test, merge_1_0) {
  s21::list<int> a = {1, 5, 7};
  s21::list<int> b = {2, 2, 4};
  s21::list<int> res = {1, 2, 2, 4, 5, 7};
  a.merge(b);

  auto it = a.begin();
  for (auto i = res.begin(); i != res.end(); ++i) {
    EXPECT_EQ(*it, *i);
    ++it;
  }

  EXPECT_EQ(res.size(), a.size());
  EXPECT_EQ(b.empty(), true);
}

TEST(list_test, sort_1_0) {
  s21::list<int> a = {100000, 43, 2, 3, 41, -11, 3, 0, 32};
  std::list<int> b = {100000, 43, 2, 3, 41, -11, 3, 0, 32};
  a.sort();
  b.sort();
  auto it = b.begin();
  for (auto i = a.begin(); i != a.end(); i++) {
    EXPECT_EQ(*it, *i);
    ++it;
  }
}

TEST(list_test, sort_2_0) {
  s21::list<int> a = {1, 1, 1, 1};
  std::list<int> b = {1, 1, 1, 1};
  a.sort();
  b.sort();
  auto it = b.begin();
  for (auto i = a.begin(); i != a.end(); i++) {
    EXPECT_EQ(*it, *i);
    ++it;
  }
}

TEST(list_test, sort_3_0) {
  s21::list<int> a = {5, 8, 1, 4, 2, 3, 6, 7, 0};
  a.sort();
  auto it = a.begin();
  for (int i = 0; i < 9; ++i, ++it) {
    EXPECT_EQ(*it, i);
  }
}

TEST(list_test, erase_1_0) {
  s21::list<int> a = {10, 10, 20, 30, 40, 50, 60};
  s21::list<int>::iterator it = a.begin();

  a.erase(it);
  auto i = a.begin();
  int j = 10;
  size_t size = 0;
  while (size < a.size()) {
    EXPECT_EQ(j, *i);
    j += 10;
    i++, size++;
  }
}

TEST(list_test, splice_1_0) {
  s21::list<int> a = {0, 1, 3};
  s21::list<int> b = {4, 5};
  auto i = a.begin();
  ++i;
  ++i;
  ++i;
  a.splice(i, b);
  auto it = a.begin();

  std::list<int> a1 = {0, 1, 3};
  std::list<int> b1 = {4, 5};
  auto i_res = a1.begin();
  ++i_res;
  ++i_res;
  ++i_res;
  a1.splice(i_res, b1);

  for (auto it_res = a1.begin(); it_res != a1.end(); it_res++, it++) {
    EXPECT_EQ(*it, *it_res);
  }
}

TEST(list_test, emplace_front_0) {
  s21::list<int> a = {6, 7, 8};
  a.emplace_front(1, 2, 3, 4, 5);
  auto it = a.begin();
  for (int i = 1; i <= 8; i++, ++it) {
    EXPECT_EQ(*it, i);
  }

  EXPECT_FALSE(a.begin() == a.end());
  it--;
  it--;
  EXPECT_EQ(*it, 7);
}

TEST(list_test, const_list_0) {
  const s21::list<int> a = {1, 2, 3};
  auto it = a.begin();
  auto it2 = a.begin();
  it--;
  it++;
  --it;
  EXPECT_FALSE(*it == *it2);
  EXPECT_EQ(a.front(), 1);
  EXPECT_EQ(a.back(), 3);
}

TEST(list_test, emplace_back_1_0) {
  s21::list<int> a = {1, 2, 3, 4};
  a.emplace_back(1, 1, 2, 5, 6);
  auto it = a.size();
  EXPECT_EQ(9, it);
  EXPECT_EQ(a.front(), 1);
  EXPECT_EQ(a.back(), 6);
}

TEST(list_test, constructor_move_0) {
  s21::list<int> a = {1, 2, 3, 4};
  s21::list<int> b = std::move(a);
  EXPECT_FALSE(a.begin() != a.end());
}

TEST(list_test, operator_copy_0) {
  s21::list<int> a = {1, 2, 3, 4};
  s21::list<int> b = {1, 2};
  b = a;
  EXPECT_EQ(b.size(), 4);
}
