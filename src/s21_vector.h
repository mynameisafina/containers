#ifndef SRC_S21_VECTOR_H_
#define SRC_S21_VECTOR_H_

#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {
template <class T>
class vector {
  // public attribures
 public:
  // -------------Vector Member type-----------------------------------------
  using value_type =
      T;  // T defines the type of an element (T is template parameter)
  using reference = T &;  // T & defines the type of the reference to an element
  using const_reference =
      const T &;         // const T & defines the type of the constant reference
  using iterator = T *;  // T * or internal class VectorIterator<T> defines the
                         // type for iterating through the container
  using const_iterator =
      const T *;  // const T * or internal class VectorConstIterator<T> defines
                  // the constant type for iterating through the container
  using size_type = std::size_t;  // size_t defines the type of the container
                                  // size (standard type is size_t)
  // ---------------Vector Member functions----------------------------------
  // default constructor, creates empty vector
  vector() : m_size(0), m_capacity(0), arr(nullptr) {}
  // parameterized constructor, creates the vector of size n
  explicit vector(size_type n) : vector() {
    size_type zero = 0;
    m_size = m_capacity = n;
    if (n > zero) {
      arr = new value_type[m_capacity];
    }
  }
  // initializer list constructor, creates vector initizialized using
  // std::initializer_list
  vector(std::initializer_list<value_type> const &items)
      : vector(items.size()) {
    size_type i = 0;
    for (auto it = items.begin(); it != items.end(); it++) {
      arr[i] = *it;
      i++;
    }
  }
  // copy constructor
  vector(const vector &v)
      : m_size(v.m_size),
        m_capacity(v.m_capacity),
        arr(new value_type[m_capacity]) {
    for (size_type i = 0; i < m_size; i++) {
      arr[i] = v.arr[i];
    }
  }
  // move constructor
  vector(vector &&v) : vector() { operator=(std::move(v)); }
  // destructor
  ~vector() { delete[] arr; }
  // assignment operator overload for moving object
  vector &operator=(vector &&v) {
    if (this != &v) {
      delete[] arr;
      m_size = v.m_size;
      m_capacity = v.m_capacity;
      arr = v.arr;
      v.m_size = 0;
      v.m_capacity = 0;
      v.arr = nullptr;
    }
    return *this;
  }
  // ---------------Vector Element access----------------------------------
  // access specified element with bounds checking
  reference at(size_type pos) {
    if (pos >= m_size) {
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
    if (pos >= m_size) {
      throw std::out_of_range(
          "The position of the returned element does not match the range of "
          "the container");
    } else {
      return arr[pos];
    }
  }
  // access specified element
  const_reference operator[](size_type pos) const { return arr[pos]; }
  // access the first element
  const_reference front() const {
    if (empty()) {
      throw std::logic_error(
          "Cannot access front element because vector is empty");
    }
    return arr[0];
  }
  // access the last element
  const_reference back() const {
    if (empty()) {
      throw std::logic_error(
          "Cannot access back element because vector is empty");
    }
    return arr[m_size - 1];
  }
  // direct access to the underlying array
  iterator data() noexcept { return arr; }
  // direct access to the underlying array
  const_iterator data() const noexcept { return arr; }

  // ------------Vector Iterators----------------------------------------

  // returns an iterator to the beginning
  iterator begin() noexcept { return arr; }
  // returns an const iterator to the beginning
  const_iterator begin() const noexcept { return arr; }
  // returns an iterator to the end
  iterator end() noexcept { return arr + m_size; }
  // returns an const iterator to the end
  const_iterator end() const noexcept { return arr + m_size; }

  // -------------Vector Capacity------------------------------------------

  // checks whether the container is empty
  bool empty() const noexcept { return begin() == end(); }
  // returns the number of elements
  size_type size() const noexcept { return m_size; }
  // returns the maximum possible number of elements
  size_type max_size() const noexcept {
    return (std::numeric_limits<size_type>::max() / sizeof(value_type) / 2);
  }
  // allocate storage of size elements and copies current array elements to a
  // newely allocated array
  void reserve(size_type size) {
    if (size > max_size()) {
      throw std::length_error(
          "The new capacity number entered is greater than the maximum number "
          "of items the container can hold.");
    } else {
      if (size > m_capacity) {
        access_to_vector_capacity(size);
      }
    }
  }
  // returns the number of elements that can be held in currently allocated
  // storage
  size_type capacity() const noexcept { return m_capacity; }
  // reduces memory usage by freeing unused memory
  void shrink_to_fit() {
    if (m_capacity > m_size) {
      access_to_vector_capacity(m_size);
    }
  }

  // ------------Vector Modifiers---------------------------------------------

  // clears the contents
  void clear() noexcept { m_size = 0; }
  // inserts elements into concrete pos and returns the iterator that points to
  // the new element
  iterator insert(iterator pos, const_reference value) {
    size_type zero = 0;
    size_type shift = std::distance(begin(), pos);
    if (shift < zero || shift > m_size) {
      throw std::out_of_range("The specified position is outside the vector");
    }
    if (m_size + 1 > m_capacity) {
      reserve(m_capacity * 2);
    }
    value_type buf = arr[shift];
    m_size++;
    arr[shift] = value;
    for (size_type i = shift + 1; i < m_size; i++) {
      std::swap(buf, arr[i]);
    }
    return arr + shift;
  }
  // erases element at pos
  void erase(iterator pos) {
    size_type zero = 0;
    size_type shift = std::distance(begin(), pos);
    if (shift < zero || shift > m_size) {
      throw std::out_of_range("The specified position is outside the vector");
    }
    std::copy(const_cast<iterator>(pos) + 1, end(), arr + shift);
    m_size--;
  }
  // adds an element to the end
  void push_back(const_reference value) { insert(end(), value); }
  // removes the last element
  void pop_back() {
    if (empty()) {
      throw std::logic_error("vector is empty, can't delete last element");
    }
    m_size--;
  }
  // swaps the contents
  void swap(vector &other) {
    std::swap(arr, other.arr);
    std::swap(m_size, other.m_size);
    std::swap(m_capacity, other.m_capacity);
  }
  // inserts new elements into the container directly before pos
  template <class... Args>
  iterator emplace(const_iterator pos, Args &&...args) {
    auto shift = pos - begin();
    iterator it = nullptr;
    for (const auto &element : {std::forward<Args>(args)...}) {
      it = insert(begin() + shift, element);
      shift++;
    }
    return it;
  }
  // appends new elements to the end of the container
  template <class... Args>
  void emplace_back(Args &&...args) {
    for (const auto &element : {std::forward<Args>(args)...}) {
      push_back(element);
    }
  }
  // private attributes
 private:
  size_type m_size;
  size_type m_capacity;
  T *arr;
  // allocated memory
  void access_to_vector_capacity(size_type size) {
    iterator buff = new value_type[size];
    for (size_type i = 0; i < m_size; ++i) {
      buff[i] = std::move(arr[i]);
    }
    delete[] arr;
    arr = buff;
    m_capacity = size;
  }
};
}  // namespace s21

#endif  // SRC_S21_VECTOR_H_
