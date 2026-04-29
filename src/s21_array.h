#ifndef SRC_S21_ARRAY_H_
#define SRC_S21_ARRAY_H_

#include <initializer_list>
#include <iostream>

namespace s21 {
template <class T, std::size_t N>
class array {
 public:
  // --------------------------Array Member type----------------------------
  using value_type =
      T;  // T defines the type of an element (T is template parameter)
  using reference = T &;  // T & defines the type of the reference to an element
  using const_reference =
      const T &;  // const T & defines the type of the constant reference
  using iterator =
      T *;  // T * defines the type for iterating through the container
  using const_iterator = const T *;  // const T * defines the constant type for
                                     // iterating through the container
  using size_type = std::size_t;     // size_t defines the type of the container
                                     // size (standard type is size_t)

  // -------------------------Array Member functions-------------------------
  // default constructor, creates empty array
  array() {}
  // initializer list constructor, creates array initizialized using
  // std::initializer_list
  array(std::initializer_list<value_type> const &items) {
    if (N < items.size()) {
      throw std::out_of_range(
          "The number of initializer clauses in the initializer list exceeds "
          "the number of elements of the aggregate");
    }
    size_type i = 0;
    for (auto it = items.begin(); it != items.end(); it++) {
      arr[i] = *it;
      i++;
    }
  }
  // copy constructor
  array(const array &a) {
    for (size_type i = 0; i < N; i++) {
      arr[i] = a.arr[i];
    }
  }
  // move constructor
  array(array &&a) { operator=(std::move(a)); }
  // destructor
  ~array() {}
  // assignment operator overload for moving object
  array &operator=(array &&a) {
    if (this != &a) {
      for (size_type i = 0; i < N; i++) {
        arr[i] = std::move(a[i]);
      }
    }
    return *this;
  }
  // ------------------------Array Element access---------------------------
  // access specified element with bounds checking
  reference at(size_type pos) {
    if (pos >= N) {
      throw std::out_of_range(
          "The position of the returned element does not match the range of "
          "the container");
    } else {
      return arr[pos];
    }
  }
  // access specified element
  reference operator[](size_type pos) { return arr[pos]; }
  // access specified element with bounds checking (const)
  const_reference at(size_type pos) const {
    if (pos >= N) {
      throw std::out_of_range(
          "The position of the returned element does not match the range of "
          "the container");
    } else {
      return arr[pos];
    }
  }
  // access specified element (const)
  const_reference operator[](size_type pos) const { return arr[pos]; }
  // access the first element
  const_reference front() const {
    if (N == 0) {
      throw std::logic_error(
          "Cannot access front element because array is empty");
    }
    return arr[0];
  }
  // access the last element
  const_reference back() const {
    if (N == 0) {
      throw std::logic_error(
          "Cannot access back element because array is empty");
    }
    return arr[N - 1];
  }
  // direct access to the underlying array
  iterator data() noexcept { return arr; }
  // direct access to the underlying array (const)
  const_iterator data() const noexcept { return arr; }

  // ------------------------Array Iterators---------------------------------
  // returns an iterator to the beginning
  iterator begin() noexcept { return arr; }
  // returns an const iterator to the beginning
  const_iterator begin() const noexcept { return arr; }
  // returns an iterator to the end
  iterator end() noexcept { return arr + N; }
  // returns an const iterator to the end
  const_iterator end() const noexcept { return arr + N; }

  // -------------------------Array Capacity---------------------------------

  // checks whether the container is empty
  bool empty() const noexcept { return begin() == end(); }
  // returns the number of elements
  size_type size() const noexcept { return N; }
  // returns the maximum possible number of elements
  size_type max_size() const noexcept { return N; }

  // -------------------------Array Modifiers-------------------------------

  // swaps the contents
  void swap(array &other) { std::swap(arr, other.arr); }
  // assigns the given value value to all elements in the container
  void fill(const_reference value) {
    for (size_type i = 0; i < N; i++) {
      arr[i] = value;
    }
  }
  // private attributes
 private:
  value_type arr[N] = {};
};
}  // namespace s21

#endif  // SRC_S21_ARRAY_H_
