#ifndef SRC_S21_STACK_H
#define SRC_S21_STACK_H

#include "s21_list.h"

// #include <iostream>
// #include <initializer_list>
// #include <limits>

namespace s21 {
template <typename T>
class stack {
  // ------------------------------ PUBLIC ------------------------------
 public:
  // Stack Member type
  using value_type =
      T;  // T defines the type of an element (T is template parameter)
  using reference = T&;  // T & defines the type of the reference to an element
  using const_reference =
      const T&;  // const T & defines the type of the constant reference
  using size_type = std::size_t;  // Size_t defines the type of the container
                                  // size (standard type is size_t)

  // Stack Member functions
  // Default constructor, creates empty list
  stack() : list_() {}

  // Initializer list constructor, creates list initizialized using
  // std::initializer_list
  stack(std::initializer_list<value_type> const& items) : list_(items) {}

  // Copy constructor
  stack(const stack& s) : list_(s.list_) {}

  // Move constructor
  stack(stack&& s) : list_(std::move(s.list_)) {}

  // Destructor
  ~stack() = default;

  // Assignment operator overload for coping object
  stack& operator=(const stack& s) {
    list_ = s.list_;
    return *this;
  }

  // Assignment operator overload for moving object
  stack& operator=(stack&& s) noexcept {
    list_ = std::move(s.list_);
    return *this;
  }

  // Stack Element access
  // Accesses the top element
  reference top() noexcept { return list_.back(); }

  // Accesses the top const element
  const_reference top() const noexcept { return list_.back(); }

  // Stack Capacity
  // Checks whether the container is empty
  bool empty() const noexcept { return list_.empty(); }

  // Returns the number of elements
  size_type size() const noexcept { return list_.size(); }

  // Stack Modifiers
  // Inserts an element at the top
  void push(const_reference value) { list_.push_back(value); }

  // Removes the top element
  void pop() { list_.pop_back(); }

  // Swaps the contents
  void swap(stack& other) { list_.swap(other.list_); }

  // Appends new elements to the top of the container
  template <typename... Args>
  void emplace_front(Args&&... args) {
    list_.emplace_front(std::forward<Args>(args)...);
  }

  // ------------------------------ PRIVATE ------------------------------
 private:
  s21::list<T> list_;
};  // stack
}  // namespace s21

#endif  // SRC_S21_STACK_H
