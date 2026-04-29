#ifndef SRC_S21_SET_H_
#define SRC_S21_SET_H_

#include "s21_tree.h"

/*
    Implementation of set
    Set is an associative container of unique elements. This means that the same
   element can’t be added to a set twice. The set container is associative,
   because it is also represented as a tree like the map container, and
   therefore also stores elements in a sorted order. The difference between a
   map and a set is that in the set the value itself is unique and not the key
   as well as the value in the tree is not checked by the key, but by the value
   itself. There is an appropriate exception when you add an already existing
   element to a set.
*/

namespace s21 {
template <typename Key>
class set {
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using tree = RBTree<value_type>;
  using size_type = std::size_t;

 public:
  using iterator = typename tree::iterator;
  using const_iterator = typename tree::const_iterator;

  // default constructor, creates an empty set
  set() : tree_(){};

  // initializer list constructor, creates the set initizialized using
  // std::initializer_list
  set(std::initializer_list<value_type> const& items) {
    for (auto it : items) {
      tree_.insert(it);
    }
  };

  // copy constructor
  set(const set& s) : tree_(s.tree_){};

  // move constructor
  set(set&& s) : tree_(std::move(s.tree_)){};

  // default constructor
  ~set() = default;

  // assignment operator overload for copying an object
  set& operator=(const set& other) {
    tree_ = other.tree_;
    return *this;
  };

  // assignment operator overload for moving an object
  set& operator=(set&& other) {
    tree_ = std::move(other.tree_);
    return *this;
  }

  // inserts a node and returns an iterator to where the element is in the
  // container and bool denoting whether the insertion took place
  std::pair<iterator, bool> insert(const_reference key) {
    return tree_.insert(key);
  };

  // erases an element at pos
  void erase(iterator pos) { tree_.erase(pos); };

  // checks whether the container is empty
  bool empty() const noexcept { return tree_.empty(); };

  // returns the number of elements
  size_type size() const noexcept { return tree_.size(); };

  // returns the maximum possible number of elements
  size_type max_size() const noexcept { return tree_.max_size(); };

  // clears the contents
  void clear() { tree_.clear(); };

  // swaps the contents
  void swap(set& other) { tree_.swap(other.tree_); };

  // splices nodes from another container
  void merge(set& other) noexcept { tree_.merge(other.tree_); };

  // finds an element with a specific key
  iterator find(const_reference key) { return tree_.find(key); };

  // finds an element with a specific key for const set
  const_iterator find(const_reference key) const { return tree_.find(key); };

  // checks if the container contains an element with a specific key
  bool contains(const_reference key) const { return tree_.contains(key); };

  // returns an iterator to the beginning
  iterator begin() noexcept { return tree_.begin(); };

  // returns an iterator to the beginning for const set
  const_iterator begin() const noexcept { return tree_.begin(); };

  // returns an iterator to the end
  iterator end() noexcept { return tree_.end(); };

  // returns an iterator to the end for const set
  const_iterator end() const noexcept { return tree_.end(); };

  // inserts new elements into the container
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> emplace(Args&&... args) {
    return tree_.emplace(std::forward<Args>(args)...);
  };

 private:
  // red black tree variable
  tree tree_;
};
}  // namespace s21

#endif  // SRC_S21_SET_H_