#ifndef SRC_S21_MAP_H_
#define SRC_S21_MAP_H_

#include "s21_tree.h"

/*
    Implemention of map
    A map (dictionary) is an associative container that stores key-value pairs
   sorted in ascending order. It means that each element is associated with some
   unique key, and its position in the map is determined by its key. Maps come
   in handy when you want to associate elements with some other value (not an
   index). For example, an enterprise is purchasing equipment, and each item has
   to be purchased more than once. In this case, it is convenient to use a map
   with a position identifier - purchase volume pair.
*/

namespace s21 {
template <typename Key, typename T>
class map {
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using tree = RBTree<value_type>;
  using size_type = std::size_t;

 public:
  using iterator = typename tree::iterator;
  using const_iterator = typename tree::const_iterator;

  // default constructor, creates an empty map
  map() : tree_(){};

  // initializer list constructor, creates the map initizialized using
  // std::initializer_list
  map(std::initializer_list<value_type> const& items) {
    for (auto it : items) {
      tree_.insert(it);
    }
  };

  // copy constructor
  map(const map& m) : tree_(m.tree_){};

  // move constructor
  map(map&& m) : tree_(std::move(m.tree_)){};

  // destructor
  ~map() = default;

  // assignment operator overload for copying an object
  map& operator=(map& m) {
    tree_ = m.tree_;
    return *this;
  };

  // assignment operator overload for moving an object
  map& operator=(map&& m) {
    tree_ = std::move(m.tree_);
    return *this;
  };

  // access a specified element with bounds checking
  T& at(const Key& key) {
    // value_type value = {key, mapped_type{}};
    iterator it = map_find(key);
    if (it == tree_.end()) throw std::out_of_range("map::at");
    return (*it).second;
  };

  // access a specified element with bounds checking for const map
  const T& at(const Key& key) const {
    // value_type value = {key, mapped_type{}};
    const_iterator it = map_find(key);
    if (it == tree_.end()) throw std::out_of_range("map::at");
    return (*it).second;
  };

  // access or insert specified element
  T& operator[](const Key& key) {
    value_type value = {key, mapped_type{}};
    iterator it = map_find(key);
    if (it == tree_.end()) {
      auto res = tree_.insert(value);
      return (*res.first).second;
    }
    return (*it).second;
  }

  // returns an iterator to the beginning
  iterator begin() noexcept { return tree_.begin(); };

  // returns an iterator to the end
  iterator end() noexcept { return tree_.end(); };

  // returns an iterator to the beginning for const map
  const_iterator begin() const noexcept { return tree_.begin(); };

  // returns an iterator to the end for const map
  const_iterator end() const noexcept { return tree_.end(); };

  // checks whether the container is empty
  bool empty() const noexcept { return tree_.empty(); };

  // returns the number of elements
  size_type size() const noexcept { return tree_.size(); };

  // returns the maximum possible number of elements
  size_type max_size() const noexcept { return tree_.max_size(); };

  // clears the contents
  void clear() { tree_.clear(); };

  // inserts a node and returns an iterator to where the element is in
  // the container and bool denoting whether the insertion took place
  std::pair<iterator, bool> insert(const value_type& value) {
    iterator it = map_find(value.first);
    if (it == end()) {
      auto res = tree_.insert(value);
      return res;
    }
    return {it, false};
  };

  // inserts a value by key and returns an iterator to where the
  // element is in the container and bool denoting whether the insertion took
  // place
  std::pair<iterator, bool> insert(const Key& key, const T& obj) {
    value_type value = {key, obj};
    iterator it = map_find(value.first);
    if (it == end()) {
      auto res = tree_.insert(value);
      return res;
    }
    return {it, false};
  };

  // inserts an element or assigns to the current element if the key already
  // exists
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj) {
    value_type value = {key, obj};
    iterator it = map_find(key);
    if (it == tree_.end())
      return tree_.insert(value);
    else {
      (*it).second = obj;
      return {it, false};
    }
  };

  // erases an element at pos
  void erase(iterator pos) {
    auto it = map_find((*pos).first);
    if (it != end()) tree_.erase(pos);
  };

  // swaps the contents
  void swap(map& other) { tree_.swap(other.tree_); };

  // splices nodes from another container
  void merge(map& other) { tree_.merge(other.tree_); };

  // checks if there is an element with key equivalent to key in the container
  bool contains(const Key& key) const noexcept {
    const_iterator it = map_find(key);
    return it == end() ? 0 : 1;
  };

  // inserts new elements into the container
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> emplace(Args&&... args) {
    return tree_.emplace(std::forward<Args>(args)...);
  };

 private:
  // finds element with param key
  iterator map_find(const Key& key) noexcept {
    iterator it = tree_.begin();
    if (it == tree_.end() || it == nullptr) return end();
    while (it != tree_.end()) {
      if ((*it).first == key) return it;
      it++;
    }
    return end();
  }

  // finds element with param key for const map
  const_iterator map_find(const Key& key) const noexcept {
    const_iterator it = tree_.begin();
    if (it == tree_.end()) return end();
    while (it != tree_.end()) {
      if ((*it).first == key) return it;
      it++;
    }
    return end();
  }

  // red black tree variable
  tree tree_;
};
}  // namespace s21

#endif  // SRC_S21_MAP_H_