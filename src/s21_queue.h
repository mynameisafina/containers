#ifndef SRC_S21_QUEUE_H
#define SRC_S21_QUEUE_H

#include "s21_list.h"

namespace s21 {
template <typename T>
class queue {
  // ------------------------------ PUBLIC ------------------------------
 public:
  // Queue Member type
  using value_type =
      T;  // T defines the type of an element (T is template parameter)
  using reference = T &;  // T & defines the type of the reference to an element
  using const_reference =
      const T &;  // const T & defines the type of the constant reference
  using size_type = std::size_t;  // Size_t defines the type of the container
                                  // size (standard type is size_t)

  // Queue Member functions
  // Default constructor, creates empty queue
  queue() : list_() {}

  // Initializer list constructor, creates list initizialized using
  // std::initializer_list
  queue(std::initializer_list<value_type> const &items) : list_(items) {}

  // Copy constructor
  queue(const queue &q) : list_(q.list_) {}

  // Move constructor
  queue(queue &&q) : list_(std::move(q.list_)) {}

  // Destructor
  ~queue() = default;

  // Assignment operator overload for coping object
  queue &operator=(const queue &q) {
    list_ = q.list_;
    return *this;
  }

  // Assignment operator overload for moving object
  queue &operator=(queue &&q) noexcept {
    list_ = std::move(q.list_);
    return *this;
  }

  // Queue Element access
  // Access the first element
  reference front() noexcept { return list_.front(); }

  // Access the first const element
  const_reference front() const noexcept { return list_.front(); }

  // Access the last element
  reference back() noexcept { return list_.back(); }

  // Access the last const element
  const_reference back() const noexcept { return list_.back(); }

  // Queue Capacity
  // Checks whether the container is empty
  bool empty() const noexcept { return list_.empty(); }

  // Returns the number of elements
  size_type size() const noexcept { return list_.size(); }

  // Queue Modifiers
  // Inserts an element at the end
  void push(const_reference value) { list_.push_back(value); }

  // Removes the first element
  void pop() { list_.pop_front(); }

  // Swaps the contents
  void swap(queue &other) { list_.swap(other.list_); }

  // Appends new elements to the end of the container
  template <typename... Args>
  void emplace_back(Args &&...args) {
    list_.emplace_back(std::forward<Args>(args)...);
  }

  // ------------------------------ PRIVATE ------------------------------
 private:
  s21::list<T> list_;
};  // queue
}  // namespace s21

#endif  // SRC_S21_QUEUE_H
