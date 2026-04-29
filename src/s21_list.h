#ifndef SRC_S21_LIST_H
#define SRC_S21_LIST_H

#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class list {
  class ListNode;
  class ListIterator;
  class ListConstIterator;

  // ------------------------------ PUBLIC ------------------------------
 public:
  // List Member type
  using value_type =
      T;  // T defines the type of an element (T is template parameter)
  using reference = T&;  // T & defines the type of the reference to an element
  using const_reference =
      const T&;  // const T & defines the type of the constant reference
  using iterator = ListIterator;  // Internal class ListIterator<T> defines the
                                  // type for iterating through the container
  using const_iterator =
      ListConstIterator;  // Internal class ListConstIterator<T> defines the
                          // constant type for iterating through the container
  using size_type = std::size_t;  // Size_t defines the type of the container
                                  // size (standard type is size_t)

  // List Functions
  // Default constructor, creates empty list
  list() {
    size_ = 0;
    head_ = new ListNode;
  }

  // Parameterized constructor, creates the list of size n
  explicit list(size_type n) : list() {
    while (n > 0) {
      push_front(value_type{});
      n--;
    }
  }

  // Initializer list constructor, creates list initizialized using
  // std::initializer_list
  list(std::initializer_list<value_type> const& items) : list() {
    for (auto& elem : items) push_back(elem);
  }

  // Copy constructor
  list(const list& other) : list() { *this = other; }

  // Move constructor
  list(list&& other) : list() { *this = std::move(other); }

  // Destructor
  ~list() {
    clear();
    delete head_;
  }

  // Assignment operator overload for coping object
  list& operator=(const list& other) {
    if (this != &other) {
      size_type count = other.size_ < size_ ? other.size_ : size_;
      iterator iter = begin();
      const_iterator iter_other = other.begin();
      while (count > 0) {
        *iter++ = *iter_other++;
        count--;
      }
      while (other.size_ < size_) {
        pop_back();
      }
      while (other.size_ > size_) {
        push_back(*iter_other++);
      }
    }
    return *this;
  }

  // Assignment operator overload for moving object
  list& operator=(list&& other) noexcept {
    if (this != &other) {
      clear();
      swap(other);
    }
    return *this;
  }

  // List Element access
  // Access the first element
  reference front() noexcept { return *begin(); }

  // Access the first const element
  const_reference front() const noexcept { return *begin(); }

  // Access the last element
  reference back() noexcept { return *--end(); }

  // Access the last const element
  const_reference back() const noexcept { return *--end(); }

  // List Iterators
  // Returns an iterator to the beginning
  iterator begin() noexcept { return iterator(head_->next_); }

  // Returns an iterator to the beginning(const)
  const_iterator begin() const noexcept { return iterator(head_->next_); }

  // Returns an iterator to the end
  iterator end() noexcept { return iterator(head_); }

  // Returns an iterator to the end(const)
  const_iterator end() const noexcept { return iterator(head_); }

  // List Capacity
  // Checks whether the container is empty
  bool empty() const noexcept { return size_ == 0; }

  // Returns the number of elements
  size_type size() const noexcept { return size_; }

  // Returns the maximum possible number of elements
  size_type max_size() const {
    return ((std::numeric_limits<size_type>::max() / 2) / sizeof(ListNode));
  }

  // List Modifiers
  // Clears the contents
  void clear() {
    while (size_ > 0) pop_back();
  }

  // Inserts element into concrete pos and returns the iterator that points to
  // the new element
  iterator insert(iterator pos, const_reference value) {
    ListNode* new_Node = new ListNode;
    new_Node->data_ = value;
    new_Node->next_ = pos.currentNode_;
    new_Node->prev_ = pos.currentNode_->prev_;

    pos.currentNode_->prev_->next_ = new_Node;
    pos.currentNode_->prev_ = new_Node;
    size_++;
    return iterator(new_Node);
  }

  // Erases element at pos
  void erase(iterator pos) {
    if (pos.currentNode_ != head_) {
      pos.currentNode_->prev_->next_ = pos.currentNode_->next_;
      pos.currentNode_->next_->prev_ = pos.currentNode_->prev_;

      delete pos.currentNode_;
      size_--;
    }
  }

  // Adds an element to the end
  void push_back(const_reference value) { insert(end(), value); }

  // Adds an element to the head
  void push_front(const_reference value) { insert(begin(), value); }

  // Removes the last element
  void pop_back() { erase(--end()); }

  // Removes the first element
  void pop_front() { erase(begin()); }

  // Swaps the contents
  void swap(list& other) {
    if (this != &other) {
      std::swap(size_, other.size_);
      std::swap(head_, other.head_);
    }
  }

  // Merges two sorted lists
  void merge(list& other) {
    if (this != &other) {
      iterator iter = begin();
      iterator iter_other = other.begin();

      while (iter != end() && iter_other != other.end()) {
        if (*iter > *iter_other) {
          insert(iter, *iter_other);
          iterator temp = iter_other;
          ++iter_other;
          other.erase(temp);
        } else {
          ++iter;
        }
      }
      splice(iter, other);
    }
  }

  // Transfers elements from list other starting from pos
  void splice(const_iterator pos, list& other) noexcept {
    if (!other.empty()) {
      iterator iter_other_first = other.begin();
      iterator iter_other_last = --other.end();

      // Начало диапазона для вставки
      pos.currentNode_->prev_->next_ = iter_other_first.currentNode_;
      iter_other_first.currentNode_->prev_ = pos.currentNode_->prev_;

      // Конец диапазона для вставки
      pos.currentNode_->prev_ = iter_other_last.currentNode_;
      iter_other_last.currentNode_->next_ = pos.currentNode_;

      size_ += other.size_;
      other.size_ = 0;
      other.head_->next_ = other.head_;
      other.head_->prev_ = other.head_;
    }
  }

  // Reverses the order of the elements
  void reverse() {
    iterator iter = begin();
    iterator iter_final = iter;
    do {
      std::swap(iter.currentNode_->next_, iter.currentNode_->prev_);
      ++iter;
    } while (iter != iter_final);
  }

  // Removes consecutive duplicate elements
  void unique() {
    iterator iter_prev = begin();
    iterator iter = iter_prev;
    ++iter;
    iterator iter_end = end();
    while (iter != iter_end) {
      if (*iter == *iter_prev) {
        erase(iter);
        iter = iter_prev;
      } else {
        ++iter_prev;
      }
      ++iter;
    }
  }

  // Sorts the elements
  void sort() {
    if (size_ > 1) qsort(begin(), size_);
  }

  // Inserts new elements into the container directly before pos
  template <typename... Args>
  iterator emplace(const_iterator pos, Args&&... args) {
    iterator iter(pos.currentNode_);
    for (auto elem : {std::forward<Args>(args)...}) {
      insert(iter, elem);
    }
    return iter;
  }

  // Appends new elements to the end of the container
  template <typename... Args>
  void emplace_back(Args&&... args) {
    emplace(end(), std::forward<Args>(args)...);
  }

  // Appends new elements to the top of the container
  template <typename... Args>
  void emplace_front(Args&&... args) {
    emplace(begin(), std::forward<Args>(args)...);
  }

  // ------------------------------ PRIVATE ------------------------------
 private:
  // ------------------------- Node -------------------------
  // Node for list
  class ListNode {
   public:
    // Default constructor, creates empty node
    ListNode() {
      data_ = value_type{};
      next_ = this;
      prev_ = this;
    }
    value_type data_;
    ListNode* next_;
    ListNode* prev_;
  };

  // ----------------------- Iterator -----------------------
  // Internal class ListIterator<T> defines the type for iterating through the
  // containe
  class ListIterator {
    friend list;

   public:
    // Default constructor, creates empty iterator
    ListIterator() { currentNode_ = nullptr; }

    // Copy constructor
    ListIterator(const iterator& other) { currentNode_ = other.currentNode_; }
    // Assignment operator overload for coping object
    iterator& operator=(const iterator& other) {
      if (this != &other) currentNode_ = other.currentNode_;
      return *this;
    }

    reference operator*() { return currentNode_->data_; }

    bool operator==(const iterator& other) {
      return currentNode_ == other.currentNode_;
    }

    bool operator!=(const iterator& other) {
      return currentNode_ != other.currentNode_;
    }

    iterator& operator++() {  // prefix
      currentNode_ = currentNode_->next_;
      return *this;
    }

    iterator& operator--() {  // prefix
      currentNode_ = currentNode_->prev_;
      return *this;
    }

    iterator operator++(int) {  // postfix
      iterator temp = *this;
      ++(*this);
      return temp;
    }

    iterator operator--(int) {  // postfix
      iterator temp = *this;
      --(*this);
      return temp;
    }

   private:
    ListIterator(ListNode* Node) { currentNode_ = Node; }

    ListNode* currentNode_;
  };

  // -------------------- Const Iterator --------------------
  // Internal class ListConstIterator<T> defines the constant type for iterating
  // through the container
  class ListConstIterator {
    friend list;
    friend bool operator==(const const_iterator& iter1,
                           const const_iterator& iter2) {
      return iter1.currentNode_ == iter2.currentNode_;
    }
    friend bool operator!=(const const_iterator& iter1,
                           const const_iterator& iter2) {
      return iter1.currentNode_ != iter2.currentNode_;
    }

   public:
    // Default constructor, creates empty iterator
    ListConstIterator() { currentNode_ = nullptr; }

    // Copy constructor
    ListConstIterator(const iterator& other) {
      currentNode_ = other.currentNode_;
    }

    // Copy constructor for const iterator
    ListConstIterator(const const_iterator& other) {
      currentNode_ = other.currentNode_;
    }

    // Assignment operator overload for coping const object
    const_iterator& operator=(const const_iterator& other) {
      if (this != &other) currentNode_ = other.currentNode_;
      return *this;
    }

    const_reference operator*() { return currentNode_->data_; }

    const_iterator& operator++() {  // prefix
      currentNode_ = currentNode_->next_;
      return *this;
    }

    const_iterator& operator--() {  // prefix
      currentNode_ = currentNode_->prev_;
      return *this;
    }

    const_iterator operator++(int) {  // postfix
      const_iterator temp = *this;
      ++(*this);
      return temp;
    }

    const_iterator operator--(int) {  // postfix
      const_iterator temp = *this;
      --(*this);
      return temp;
    }

   private:
    ListNode* currentNode_;
  };

  // -------------------- Data and Qsort --------------------
  // Quick sort
  void qsort(iterator iter_begin, size_type size) {
    if (size > 1) {
      long long i = 0;
      long long j = size - 1;  // Номер последного эл-та
      iterator iter_i = iter_begin;
      iterator iter_j = iter_begin;  // Итератор на последнем эл-те
      for (long long k = 0; k < j; k++, ++iter_j) {
      }

      iterator iter_pivot = iter_begin;
      for (size_type k = 0; k < size / 2; k++, ++iter_pivot) {
      }
      value_type pivot = *iter_pivot;

      do {
        while (*iter_i < pivot) {
          i++;
          ++iter_i;
        }
        while (*iter_j > pivot) {
          j--;
          --iter_j;
        }
        if (i <= j) {
          std::swap(*iter_i, *iter_j);
          i++;
          iter_i++;
          j--;
          iter_j--;
        }
      } while (i <= j);

      if (j > 0) {
        qsort(iter_begin, j + 1);
      }
      if (i < (long long)size) {
        qsort(iter_i, size - i);
      }
    }
  }

  ListNode* head_;  // Service node
  size_type size_;  // Amount of elements

};  // list
}  // namespace s21

#endif  // SRC_S21_LIST_H
