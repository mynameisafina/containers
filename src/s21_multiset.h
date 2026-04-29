#ifndef SRC_S21_MULTISET_H
#define SRC_S21_MULTISET_H

#include "s21_tree.h"

/*
    Implementation of multiset
    Multiset is an associative container that follows the logic of a set, but
   allows identical elements to be stored. This container is different from a
   list or vector because the elements in the multiset are sorted instantly,
    just as in a set. But just like a set, a multiset does not allow you to
   refer to an element by its index, but requires referring to its value, which
   can be repeated in a multiset.
*/

namespace s21 {
template <typename Key>
class multiset {
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
  multiset() : tree_(){};

  // initializer list constructor, creates the set initizialized using
  // std::initializer_list
  multiset(std::initializer_list<value_type> const& items) {
    for (auto it : items) {
      tree_.insert_duplicate(it);
    }
  };

  // copy constructor
  multiset(const multiset& s) : tree_(s.tree_){};

  // move constructor
  multiset(multiset&& s) : tree_(std::move(s.tree_)){};

  // destructor
  ~multiset() = default;

  // assignment operator overload for copying an object
  multiset& operator=(const multiset& other) {
    tree_ = other.tree_;
    return *this;
  };

  // assignment operator overload for moving an object
  multiset& operator=(multiset&& other) {
    tree_ = std::move(other.tree_);
    return *this;
  }

  // inserts a node and returns an iterator to where the element is in the
  // container
  iterator insert(const_reference key) { return tree_.insert_duplicate(key); };

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
  void swap(multiset& other) { tree_.swap(other.tree_); };

  // splices nodes from another container
  void merge(multiset& other) { tree_.merge_duplicates(other.tree_); };

  // finds element with a specific key
  iterator find(const_reference key) noexcept { return tree_.find(key); };

  // finds element with a specific key for const multiset
  const_iterator find(const_reference key) const noexcept {
    return tree_.find(key);
  };

  // checks if the container contains element with a specific key
  bool contains(const_reference key) const noexcept {
    return tree_.contains(key);
  };

  // returns an iterator to the beginning
  iterator begin() noexcept { return tree_.begin(); };

  // returns an iterator to the beginning for const multiset
  const_iterator begin() const noexcept { return tree_.begin(); };

  // returns an iterator to the end
  iterator end() noexcept { return tree_.end(); };

  // returns an iterator to the end for const multiset
  const_iterator end() const noexcept { return tree_.end(); };

  // returns the number of elements matching a specific key
  size_type count(const_reference key) const noexcept {
    return tree_.count(key);
  };

  // returns range of elements matching a specific key
  std::pair<iterator, iterator> equal_range(const_reference key) noexcept {
    return tree_.equal_range(key);
  };

  // returns an iterator to the first element not less than the given key
  iterator lower_bound(const_reference key) noexcept {
    return tree_.lower_bound(key);
  };

  // returns an iterator to the first element greater than the given key
  iterator upper_bound(const_reference key) noexcept {
    return tree_.upper_bound(key);
  };

  // returns range of elements matching a specific key
  std::pair<const_iterator, const_iterator> equal_range(
      const_reference key) const noexcept {
    return tree_.equal_range(key);
  };

  // // returns an iterator to the first element not less than the given key for
  // const object
  const_iterator lower_bound(const_reference key) const noexcept {
    return tree_.lower_bound(key);
  };

  // returns an iterator to the first element greater than the given key for
  // const object
  const_iterator upper_bound(const_reference key) const noexcept {
    return tree_.upper_bound(key);
  };

  // inserts new elements into the container
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> emplace(Args&&... args) {
    return tree_.emplace_duplicate(std::forward<Args>(args)...);
  };

 private:
  // red black tree variable
  tree tree_;
};
}  // namespace s21

#endif  // SRC_S21_MULTISET_H