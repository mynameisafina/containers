#include <gtest/gtest.h>

#include <random>
#include <stack>

#include "../s21_containers.h"

TEST(stack_test, create_and_size) {
  s21::stack<double> A;
  EXPECT_EQ(A.size(), 0);
  s21::stack<double> C = {1.78, 0.99, -1.53};
  EXPECT_EQ(C.size(), 3);
  s21::stack<char> D = {'C', 'A', 'T'};
  EXPECT_EQ(D.size(), 3);
}

TEST(stack_test, create_1) {
  s21::stack<double> A = {1.78, 0.99, -1.53};
  s21::stack<double> B = A;
  EXPECT_EQ(A.top(), B.top());
  EXPECT_EQ(A.size(), B.size());
}

TEST(stack_test, create_2) {
  const s21::stack<double> A = {1.78, 0.99, -1.53};
  s21::stack<double> A2 = A;
  EXPECT_EQ(A2.size(), A.size());
  s21::stack<double> B = std::move(A2);
  EXPECT_EQ(B.size(), A.size());
  EXPECT_EQ(A2.size(), 0);
  EXPECT_EQ(A.top(), B.top());
}

TEST(stack_test, create_and_pop) {
  s21::stack<std::string> A = {"Cats", "are", "the", "best"};
  s21::stack<std::string> B = A;
  std::string a, b;
  while (!A.empty()) {
    a = A.top();
    b = B.top();
    EXPECT_EQ(a, b);
    A.pop();
    B.pop();
  }
  EXPECT_EQ(A.size(), 0);
  EXPECT_EQ(B.size(), 0);
}

TEST(stack_test, create_and_pop_2) {
  s21::stack<std::string> A = {"Cats", "are", "the", "best", " ", ""};
  s21::stack<std::string> A2 = A;
  EXPECT_EQ(A2.size(), A.size());
  s21::stack<std::string> B = std::move(A2);
  EXPECT_EQ(B.size(), A.size());
  EXPECT_EQ(A2.size(), 0);
  std::string a, b;
  while (!A.empty()) {
    a = A.top();
    b = B.top();
    EXPECT_EQ(a, b);
    A.pop();
    B.pop();
  }
  EXPECT_EQ(A.size(), 0);
  EXPECT_EQ(B.size(), 0);
}

TEST(stack_test, create_list_1) {
  std::initializer_list<double> L = {1.78, 0.99, -1.53};
  s21::stack<double> A = L;
  std::stack<double> B(L);
  EXPECT_EQ(B.size(), A.size());
  double a, b;
  while (!B.empty()) {
    a = A.top();
    b = B.top();
    EXPECT_EQ(a, b);
    A.pop();
    B.pop();
  }
  EXPECT_EQ(B.size(), A.size());
}

TEST(stack_test, create_list_2) {
  std::initializer_list<std::string> L = {"Cats", "are", "the", "best",
                                          " ",    "",    "!"};
  s21::stack<std::string> A = L;
  std::stack<std::string> B(L);
  EXPECT_EQ(B.size(), A.size());
  std::string a, b;
  while (!B.empty()) {
    a = A.top();
    b = B.top();
    EXPECT_EQ(a, b);
    A.pop();
    B.pop();
  }
  EXPECT_EQ(B.size(), A.size());
}

TEST(stack_test, assignment_copy_1) {
  const s21::stack<double> A = {1.78, 0.99, -1.53};
  s21::stack<double> B;
  EXPECT_EQ(B.size(), 0);
  B = A;
  EXPECT_EQ(B.size(), A.size());
  EXPECT_EQ(A.top(), B.top());
}

TEST(stack_test, assignment_copy_2) {
  const s21::stack<std::string> A = {"Cats", "are", "the", "best"};
  s21::stack<std::string> B;
  EXPECT_EQ(B.size(), 0);
  B = A;
  EXPECT_EQ(B.size(), A.size());
  EXPECT_EQ(A.top(), B.top());
}

TEST(stack_test, assignment_move_1) {
  s21::stack<double> A = {1.78, 0.99, -1.53};
  s21::stack<double> A2 = A;
  EXPECT_EQ(A2.size(), 3);
  s21::stack<double> B;
  EXPECT_EQ(B.size(), 0);
  B = std::move(A2);
  EXPECT_EQ(B.size(), 3);
  EXPECT_EQ(A2.size(), 0);
  EXPECT_EQ(A.top(), B.top());
}

TEST(stack_test, assignment_move_2) {
  s21::stack<std::string> A = {"Cats", "are", "the", "best"};
  s21::stack<std::string> A2 = A;
  EXPECT_EQ(A2.size(), A.size());
  s21::stack<std::string> B;
  EXPECT_EQ(B.size(), 0);
  B = std::move(A2);

  EXPECT_EQ(B.size(), A.size());
  EXPECT_EQ(A2.size(), 0);
  std::string a, b;
  while (!B.empty()) {
    a = A.top();
    b = B.top();
    EXPECT_EQ(a, b);
    A.pop();
    B.pop();
  }
  EXPECT_EQ(B.size(), A.size());
}

TEST(stack_test, top_1) {
  std::initializer_list<double> L = {1.78, 0.99, -1.53};
  s21::stack<double> A = L;
  std::stack<double> B(L);
  EXPECT_EQ(A.top(), B.top());
  A.pop();
  B.pop();
  EXPECT_EQ(A.top(), B.top());
}

TEST(stack_test, top_2) {
  std::initializer_list<char> L = {'C', 'A', 'T'};
  s21::stack<char> A = L;
  std::stack<char> B(L);
  EXPECT_EQ(A.top(), B.top());
  A.pop();
  B.pop();
  EXPECT_EQ(A.top(), B.top());
}

TEST(stack_test, top_const) {
  std::initializer_list<double> L = {1.78, 0.99, -1.53};
  const s21::stack<double> A = L;
  const std::stack<double> B(L);
  EXPECT_EQ(A.top(), B.top());
  EXPECT_EQ(A.size(), B.size());
}

TEST(stack_test, empty) {
  s21::stack<double> A;
  ASSERT_TRUE(A.empty());
  s21::stack<double> C = {1.78, 0.99, -1.53};
  ASSERT_FALSE(C.empty());
  s21::stack<char> D = {'C', 'A', 'T'};
  ASSERT_FALSE(D.empty());
  C = A;
  ASSERT_TRUE(C.empty());
}

TEST(stack_test, push_pop) {
  s21::stack<double> A;
  std::stack<double> B;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-10.0, 10.0);
  double elem;
  for (int n = 0; n < 10; ++n) {
    elem = dis(gen);
    A.push(elem);
    B.push(elem);
  }

  EXPECT_EQ(B.size(), A.size());
  double a, b;
  while (!B.empty()) {
    a = A.top();
    b = B.top();
    EXPECT_EQ(a, b);
    A.pop();
    B.pop();
  }
  EXPECT_EQ(B.size(), A.size());
}

TEST(stack_test, swap_1) {
  std::initializer_list<double> L = {1.78, 0.99, -1.53, 4.88, 111.303, -43.5};
  s21::stack<double> A = L;
  std::stack<double> B(L);
  std::initializer_list<double> L2 = {-9.87, -6.5, -4.321, 0.12, 3, 4567, 8.9};
  s21::stack<double> A2 = L2;
  std::stack<double> B2(L2);
  A.swap(A2);
  B.swap(B2);

  EXPECT_EQ(B.size(), A.size());
  double a, b;
  while (!B.empty()) {
    a = A.top();
    b = B.top();
    EXPECT_EQ(a, b);
    A.pop();
    B.pop();
  }
  EXPECT_EQ(B.size(), A.size());
}

TEST(stack_test, swap_2) {
  std::initializer_list<std::string> L = {"Cats", "are", "the", "best",
                                          " ",    "",    "!"};
  s21::stack<std::string> A = L;
  std::stack<std::string> B(L);
  std::initializer_list<std::string> L2 = {"Salamanders", "Capybaras",
                                           "Alpacas", "Honey Badgers"};
  s21::stack<std::string> A2 = L2;
  std::stack<std::string> B2(L2);
  A.swap(A2);
  B.swap(B2);

  EXPECT_EQ(B.size(), A.size());
  std::string a, b;
  while (!B.empty()) {
    a = A.top();
    b = B.top();
    EXPECT_EQ(a, b);
    A.pop();
    B.pop();
  }
  EXPECT_EQ(B.size(), A.size());
}

TEST(stack_test, emplace_front) {
  s21::stack<int> A = {1, 2, 3};
  s21::stack<int> B = {5, 1, 2, 5, 6, 1, 2, 3};
  A.emplace_front(5, 1, 2, 5, 6);

  EXPECT_EQ(B.size(), A.size());
  double a, b;
  while (!B.empty()) {
    a = A.top();
    b = B.top();
    EXPECT_EQ(a, b);
    A.pop();
    B.pop();
  }
  EXPECT_EQ(B.size(), A.size());
}

TEST(stack_test, size) {
  s21::stack<int> a;
  a.push(3);
  auto size = a.size();
  EXPECT_EQ(1, size);

  s21::stack<int> b;
  auto size_2 = b.size();
  EXPECT_EQ(0, size_2);
}

TEST(stack_test, test) {
  s21::stack<int> a{1, 2, 4};
  a.push(3);
  auto size = a.size();
  EXPECT_EQ(4, size);
  s21::stack<int> c = a;
  EXPECT_EQ(c.size(), a.size());
  s21::stack<int> d = std::move(a);
  EXPECT_EQ(0, a.size());
  s21::stack<int> b;
  auto size_2 = b.size();
  EXPECT_EQ(0, size_2);
  s21::stack<int> test1;
  test1 = std::move(d);
  EXPECT_EQ(0, d.size());
}

TEST(stack_test, test2) {
  s21::stack<int> a{1, 2, 4, 5, 6, 7};
  s21::stack<int> b;
  b = std::move(a);
  EXPECT_EQ(a.size(), 0);
}

TEST(stack_test, push_and_pop) {
  s21::stack<int> a;
  a.push(1);
  a.push(2);
  a.push(3);
  a.push(4);
  a.push(5);
  int i = 5;
  size_t size = 1;
  while (size <= a.size()) {
    EXPECT_EQ(i, a.top());
    a.pop();
    i--;
    size++;
  }
  a.pop();
  a.pop();
  a.push(1);
  a.push(2);
  a.push(3);
  i = 3;
  size = 1;
  while (size <= a.size()) {
    EXPECT_EQ(i, a.top());
    a.pop();
    i--;
    size++;
  }
}

TEST(stack_test, push_and_pop_2) {
  s21::stack<int> a;
  a.pop();
  auto it = a.top();
  EXPECT_EQ(it, 0);
  EXPECT_EQ(a.empty(), true);
}

TEST(stack_test, top) {
  s21::stack<int> a;
  a.push(3);
  a.push(33);
  a.push(333);
  auto it = a.top();
  EXPECT_EQ(333, it);
  a.pop();
  it = a.top();
  EXPECT_EQ(33, it);
}

TEST(stack_test, eq) {
  s21::stack<int> a;
  s21::stack<int> b;
  a.push(11);
  a.push(22);
  a.push(33);
  b = a;
  size_t size = 1;
  while (size <= a.size()) {
    EXPECT_EQ(b.top(), a.top());
    a.pop();
    b.pop();
    size++;
  }
}

TEST(stack_test, swap) {
  s21::stack<int> a;
  s21::stack<int> b;
  a.push(5);
  a.push(4);
  a.push(3);
  a.push(2);
  a.push(1);
  a.swap(b);
  size_t size = b.size();
  for (size_t i = 1; i <= size; i++) {
    EXPECT_EQ(b.top(), i);
    b.pop();
  }
  EXPECT_EQ(b.empty(), true);
}
