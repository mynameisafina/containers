#ifndef SRC_S21_TREE_H_
#define SRC_S21_TREE_H_

#include <initializer_list>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

/* Implementation of the Red Black Tree
    A red-black tree is a binary search tree having following five additional
   properties (invariants).

    1. Every node in T is either red or black.
    2. The root node of T is black.
    3. Every NULL node is black. (NULL nodes are the leaf nodes. They do not
   contain any keys. When we search for a key that is not present in the tree,
   we reach the NULL node.)
    4. If a node is red, both of its children are black. This means no two nodes
   on a path can be red nodes.
    5. Every path from a root node to a NULL node has the same number of black
   nodes. (black height)
*/

namespace s21 {
template <typename Key>
class RBTree {
  class RBNode;
  class RBIterator;
  class RBConstIterator;
  using reference = Key&;
  using const_reference = const Key&;
  using size_type = std::size_t;
  using comparator = std::less<Key>;
  using NodePtr = RBNode*;

  enum NodeColor { BLACK, RED };

  //      =============== PUBLIC ===============
 public:
  using iterator = RBIterator;
  using const_iterator = RBConstIterator;
  using value_type = Key;

  // default constructor. creates root node
  RBTree() : root_(new RBNode), size_(0){};

  // copy constructor
  RBTree(const RBTree& other) : RBTree() { *this = other; };

  // move constructor
  RBTree(RBTree&& other) : RBTree() { *this = std::move(other); };

  // destructor
  ~RBTree() {
    clear();
    delete_node(root_);
  };

  // assignment copy overload
  RBTree& operator=(const RBTree& other) {
    if (this != &other) {
      if (other.size_ == 0) {
        clear();
      } else {
        if (root_->parent_) clear();
        NodePtr root = copy(other.root_->parent_, nullptr);
        root_->parent_ = root;
        root_->parent_->parent_ = root;
        root_->left_ = other.root_->left_;
        root_->right_ = other.root_->right_;
        size_ = other.size_;
      }
    }
    return *this;
  };

  // move overload
  RBTree& operator=(RBTree&& other) {
    if (this != &other) {
      clear();
      std::swap(this->root_, other.root_);
      std::swap(this->size_, other.size_);
    } else {
      other.clear();
      delete_node(other.root_);
    }
    return *this;
  };

  // returns iterator of the min element
  iterator begin() noexcept { return iterator(root_->left_); };

  // same for const obj
  const_iterator begin() const noexcept {
    return const_iterator(root_->left_);
  };

  // returns iterator to root (end element)
  iterator end() noexcept { return iterator(root_); };

  // same for const obj
  const_iterator end() const noexcept { return const_iterator(root_); };

  // checks if obj is empty
  bool empty() const noexcept { return size_ ? 0 : 1; };

  // returns number of elements
  size_type size() const noexcept { return size_; };

  // returns max possible number of elements
  size_type max_size() const noexcept {
    return (std::numeric_limits<size_type>::max() / 2 - sizeof(RBNode) -
            sizeof(RBTree)) /
           sizeof(RBNode);
  };

  // clears content of obj
  void clear() {
    delete_all(root_->parent_);
    root_->parent_ = nullptr;
    root_->left_ = nullptr;
    root_->right_ = nullptr;
    size_ = 0;
  };

  // inserts new element to obj
  // only unique elements are inserted
  std::pair<iterator, bool> insert(const value_type& value) {
    NodePtr new_node = new RBNode(value);
    std::pair<iterator, bool> res = insert_node(new_node, true);
    if (!res.second) delete_node(new_node);
    return res;
  };

  // inserts new element to obj
  // dduplicates can be inserted too
  iterator insert_duplicate(const value_type& value) {
    NodePtr new_node = new RBNode(value);
    return insert_node(new_node, false).first;
  };

  // erases element at pos
  void erase(iterator pos) { delete_node(pos); };

  // swaps the contents
  void swap(RBTree& other) {
    using std::swap;
    swap(root_, other.root_);
    swap(size_, other.size_);
  };

  // returns iterator to element with key value
  iterator find(const_reference key) noexcept {
    iterator res = iterator(find_node(key));
    if (res == end() || comparator{}(*res, key)) return end();
    return res;
  };

  // same for const obj
  const_iterator find(const_reference key) const noexcept {
    const_iterator res = lower_bound(key);
    if (res == end() || comparator{}(*res, key)) return end();
    return res;
  };

  // checks if obj contains such element
  bool contains(const_reference key) const noexcept {
    NodePtr node = find_node(key);
    return (node != root_);
  };

  // returns iterator to the greater element
  iterator upper_bound(const_reference value) noexcept {
    iterator result = end();
    NodePtr begin = root_->parent_;
    while (begin != nullptr) {
      if (comparator{}(value, begin->data_)) {
        result = iterator(begin);
        begin = begin->left_;
      } else
        begin = begin->right_;
    }
    return result;
  };

  // same for const obj
  const_iterator upper_bound(const_reference value) const noexcept {
    const_iterator result = end();
    NodePtr begin = root_->parent_;
    while (begin != nullptr) {
      if (comparator{}(value, begin->data_)) {
        result = const_iterator(begin);
        begin = begin->left_;
      } else
        begin = begin->right_;
    }
    return result;
  };

  // returns an iterator pointing to the first element in the range [first,last)
  // which does not compare less than key
  iterator lower_bound(const_reference value) noexcept {
    iterator result = end();
    NodePtr begin = root_->parent_;
    while (begin != nullptr) {
      if (comparator{}(begin->data_, value)) {
        begin = begin->right_;
      } else {
        result = iterator(begin);
        begin = begin->left_;
      }
    }
    return result;
  };

  // same for const obj
  const_iterator lower_bound(const_reference value) const noexcept {
    const_iterator result = end();
    NodePtr begin = root_->parent_;
    while (begin != nullptr) {
      if (comparator{}(begin->data_, value)) {
        begin = begin->right_;
      } else {
        result = const_iterator(begin);
        begin = begin->left_;
      }
    }
    return result;
  };

  // returns number of elements which equal to key
  size_type count(const_reference key) const noexcept {
    const_iterator it = begin();
    size_type c = 0;
    for (size_type i = 0; i < size(); i++) {
      if (*it == key) c++;
      it++;
    }
    return c;
  };

  // pair object whose member pair::first is an iterator to the lower bound of
  // the subrange of equivalent values and pair::second its upper bound
  std::pair<iterator, iterator> equal_range(const_reference key) noexcept {
    iterator start = lower_bound(key), end = upper_bound(key);
    return {start, end};
  };

  // same for const obj
  std::pair<const_iterator, const_iterator> equal_range(
      const_reference key) const noexcept {
    const_iterator start = lower_bound(key), end = upper_bound(key);
    return {start, end};
  };

  // move content of one obj to another
  void merge_duplicates(RBTree& other) noexcept {
    if (this != &other) {
      iterator it = other.begin();
      while (other.size_ > 0) {
        NodePtr node = it.node_;
        it++;
        if (node->parent_->left_ == node) node->parent_->left_ = nullptr;
        if (node->parent_->right_ == node) node->parent_->right_ = nullptr;
        if (node->right_) node->right_->parent_ = node->parent_;
        if (node->left_) node->left_->parent_ = node->parent_;
        node->left_ = nullptr;
        node->right_ = nullptr;
        node->parent_ = nullptr;
        node->color_ = RED;
        insert_node(node, false);
        other.size_--;
      }
    }
    other.root_->parent_ = nullptr;
    other.size_ = 0;
  };

  // move contents of one obj to another
  // with no duplicates
  // all the duplicates stay in the other tree
  void merge(RBTree& other) noexcept {
    if (this != &other) {
      iterator it = other.begin();
      while (it != other.end()) {
        if (find(it.node_->data_) == end()) {
          NodePtr node = it.node_;
          it++;
          node = other.merge_node(node);
          insert_node(node, true);
        } else
          it++;
      }
    }
  };

  // inserts new elements into the container
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> emplace(Args&&... args) {
    std::vector<std::pair<iterator, bool>> vect;
    vect.reserve(sizeof...(args));
    for (auto element : {std::forward<Args>(args)...}) {
      NodePtr new_node = new RBNode(std::move(element));
      std::pair<iterator, bool> result = insert_node(new_node, true);
      if (result.second == false) {
        delete new_node;
      }
      vect.push_back(result);
    }
    return vect;
  }

  // inserts new elements into the container with duplicates
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> emplace_duplicate(Args&&... args) {
    std::vector<std::pair<iterator, bool>> vect;
    vect.reserve(sizeof...(args));
    for (auto element : {std::forward<Args>(args)...}) {
      NodePtr new_node = new RBNode(std::move(element));
      vect.push_back(insert_node(new_node, false));
    }
    return vect;
  }

  //      =============== PRINT FUNCS ===============

  void print() noexcept {
    if (root_->parent_ != nullptr) {
      print(root_->parent_, "", true);
    }
  };

  //      =============== PRIVATE ===============

 private:
  // print function
  // i used it to check if my tree is correct red black tree
  void print(NodePtr node, std::string indent, bool right) noexcept {
    if (node != nullptr) {
      std::cout << indent;
      if (right) {
        std::cout << "R----";
        indent += "     ";
      } else {
        std::cout << "L----";
        indent += "|    ";
      }
      std::string color = (node->color_ == RED) ? "RED" : "BLACK";
      std::cout << node->data_ << "(" << color << ")" << std::endl;
      print(node->left_, indent, false);
      print(node->right_, indent, true);
    }
  };

  //      =============== TREE FUNCS ===============

  // inserts node in Red Black Tree
  // if unique is true, elements with no duplicates are inserted
  // else: duplicates can be iserted too
  std::pair<iterator, bool> insert_node(NodePtr new_node, bool unique) {
    // searching place to insert the node
    NodePtr node = root_->parent_;
    NodePtr parent = nullptr;
    while (node != nullptr) {
      parent = node;
      if (comparator{}(new_node->data_, node->data_))
        node = node->left_;
      else if (comparator{}(node->data_, new_node->data_))
        node = node->right_;
      else if (unique == false)
        node = node->right_;  // case when none-unique element can be inserted
      else
        return {
            iterator(node),
            false};  // return element if our tree does not contain duplicates
    }
    // since insertion is happening size is increasing
    size_++;
    // insertion
    if (parent == nullptr) {  // case when inserting 1st element (root)
      new_node->parent_ = root_;
      root_->parent_ = new_node;
      new_node->color_ = BLACK;
    } else {
      new_node->parent_ = parent;
      comparator{}(new_node->data_, parent->data_) ? parent->left_ = new_node
                                                   : parent->right_ = new_node;
    }
    // put ptr of the max element to root node
    if (!root_->right_ || root_->right_->right_) {
      root_->right_ = new_node;
      // root_->data_ = new_node->data_; // this is for tests. sometimes on mac
      // PC std containers put max value in the end node
    }
    // put ptr of the min element to root node
    if (!root_->left_ || root_->left_->left_) root_->left_ = new_node;
    // balancing after insertion
    balance_insert(new_node);
    return {iterator(new_node), true};
  };

  // frees node and nulls all the ptrs
  void delete_node(NodePtr node) {
    if (node != nullptr) {
      node->left_ = nullptr;
      node->right_ = nullptr;
      node->parent_ = nullptr;
      delete node;
      node = nullptr;
    }
  };

  // left rotations for red black tree balancing
  void left_rotate(NodePtr node) noexcept {
    NodePtr help_node = node->right_;
    // change node's right subtree to the help_node's left subtree
    node->right_ = help_node->left_;
    // if not empty change its parent ptr
    if (help_node->left_ != nullptr) {
      help_node->left_->parent_ = node;
    }
    // change help_node parent to node parent
    help_node->parent_ = node->parent_;
    // change node parent's child
    // 1st case if node is the 1st element
    if (node->parent_ == root_) {
      root_->parent_ = help_node;
      // if node is a left child
    } else if (node == node->parent_->left_) {
      node->parent_->left_ = help_node;
      // if node is a right child
    } else {
      node->parent_->right_ = help_node;
    }
    help_node->left_ = node;
    node->parent_ = help_node;
  };

  // right rotations for red black tree balancing
  void right_rotate(NodePtr node) noexcept {
    NodePtr help_node = node->left_;
    node->left_ = help_node->right_;
    if (help_node->right_ != nullptr) {
      help_node->right_->parent_ = node;
    }
    help_node->parent_ = node->parent_;
    if (root_->parent_ == node) {
      root_->parent_ = help_node;
    } else if (node == node->parent_->right_) {
      node->parent_->right_ = help_node;
    } else if (node == node->parent_->left_) {
      node->parent_->left_ = help_node;
    }
    help_node->right_ = node;
    node->parent_ = help_node;
  };

  /*
      Balance function is needed to support red black tree properties.
      There are several cases after insertion.
      P - parent, G - grandparent, U - uncle, S - sibling, X - inserted node
      Case 1:
          Tree is empty - insert X and color it black
      Case 2:
          P is black - insert X and color it red
      Case 3:
          P is red. In this case we need to check U's color
          Case 3.1:
              U is red - push blackness from G to U and P: make P, U black; make
     G red Case 3.2: U is black. In this case we need to check if P and X are
     right or left children Case 3.2.1: P is right child of G and X is right
     child of P: left rotate at G; make G red; make P black Case 3.2.2: P is
     right child of G and X is left child of P: right rotate at P; repeat 3.2.1
     case Case 3.2.3: P is left child of G and X if left child of P: right
     rotate at G; make G red; make P black Case 3.2.4: P is left child of G and
     X is right child of P: left rotate at P; repeat 3.2.3 case

  */
  void balance_insert(NodePtr node) noexcept {
    NodePtr u;
    while (node->parent_->color_ == RED && node != root_->parent_) {
      if (node->parent_ == node->parent_->parent_->right_) {
        u = node->parent_->parent_->left_;
        // if uncle color is red too, then colorflip
        if (u != nullptr && u->color_ == RED) {  // case 3.1
          u->color_ = BLACK;
          node->parent_->color_ = BLACK;
          node->parent_->parent_->color_ = RED;
          // change ptr for the next cycle
          node = node->parent_->parent_;
          // if uncle is black and p is g's right child
        } else {
          if (node == node->parent_->left_) {  // 3.2.2
            node = node->parent_;
            right_rotate(node);
          }
          node->parent_->color_ = BLACK;  // case 3.2.1
          node->parent_->parent_->color_ = RED;
          left_rotate(node->parent_->parent_);
        }
      } else {
        u = node->parent_->parent_->right_;
        if (u != nullptr && u->color_ == RED) {  // case 3.1
          u->color_ = BLACK;
          node->parent_->color_ = BLACK;
          node->parent_->parent_->color_ = RED;
          // change ptr for the next cycle
          node = node->parent_->parent_;
        } else {
          if (node == node->parent_->right_) {  // case 3.2.4
            node = node->parent_;
            left_rotate(node);
          }
          node->parent_->color_ = BLACK;  // case 3.2.3
          node->parent_->parent_->color_ = RED;
          right_rotate(node->parent_->parent_);
        }
      }
    }
    root_->parent_->color_ = BLACK;  // make sure root node stays black
  };

  // returns min node of tree
  NodePtr search_right(NodePtr node) noexcept {
    while (node->right_) {
      node = node->right_;
    }
    return node;
  };

  // returns max node of tree
  NodePtr search_left(NodePtr node) noexcept {
    while (node->left_) {
      node = node->left_;
    }
    return node;
  };

  // swaps nodes
  void swap_nodes(NodePtr one, NodePtr two) noexcept {
    two == two->parent_->left_ ? two->parent_->left_ = one
                               : two->parent_->right_ = one;
    if (one == root_->parent_)
      root_->parent_ = two;
    else
      one == one->parent_->left_ ? one->parent_->left_ = two
                                 : one->parent_->right_ = two;
    std::swap(one->left_, two->left_);
    std::swap(one->right_, two->right_);
    std::swap(one->parent_, two->parent_);
    // swapping colors too because pointers are being swapped not values
    // we swap pointers for the iterators to stay valid
    std::swap(one->color_, two->color_);
    if (one->left_) one->left_->parent_ = one;
    if (one->right_) one->right_->parent_ = one;
    if (two->left_) two->left_->parent_ = two;
    if (two->right_) two->right_->parent_ = two;
  };

  // finds node with key value
  NodePtr find_node(const_reference key) const noexcept {
    NodePtr ptr = root_->parent_;
    while (ptr) {
      if (ptr->data_ == key) return ptr;
      if (comparator{}(ptr->data_, key))
        ptr = ptr->right_;
      else
        ptr = ptr->left_;
    }
    return root_;
  };

  NodePtr find_node(iterator pos) const noexcept {
    NodePtr res = find_node(*pos);
    return res;
  };

  // deletion of the node
  void delete_node(iterator pos) {
    if (pos == end()) return;  // cannot delete root
    NodePtr node = pos.node_;
    if (node->left_ &&
        node->right_) {  // case when node has two children. we just swap it
                         // with the max element in its left subtree
      NodePtr swap_node = search_right(node->left_);
      swap_nodes(node, swap_node);
    }
    // deleting node with one right child
    if (!node->left_ &&
        node->right_ != nullptr) {  // case when node has one right child.
                                    // we swap if with its right child
      swap_nodes(node, node->right_);
    }
    // deleting node with one left child
    if (!node->right_ && node->left_ != nullptr) {
      // swap it with its left child
      swap_nodes(node, node->left_);
    }
    // after swapping and prepairing for the delete operation
    // we need to check if the node is black
    // if so, we should balance the tree so black height will not be violated
    if (node->color_ == BLACK && (!node->left_ && !node->right_)) {
      balance_delete(node);
    }
    // if node is the first element
    if (root_->parent_ == node) {
      root_->parent_ = nullptr;
      root_->right_ = nullptr;
      root_->left_ = nullptr;
    } else {
      // else we remove pointer to the node in its parent
      node->parent_->left_ == node ? node->parent_->left_ = nullptr
                                   : node->parent_->right_ = nullptr;
      // if node is min element in tree we change it to another element
      if (root_->left_ == node) root_->left_ = search_left(root_->parent_);
      // same for case when it is the max element
      if (root_->right_ == node) root_->right_ = search_right(root_->parent_);
    }
    // deletion
    delete_node(node);
    // since one node is deleted size is decreasing
    size_--;
  };

  // extracts node from tree to put it elsewhere
  // the process is similar to deletion but it does not delete the node
  NodePtr merge_node(NodePtr node) {
    if (node != root_) {  // cannot extract root
      if (node->right_ && node->left_) {
        NodePtr swap = search_right(node->left_);
        swap_nodes(node, swap);
      }
      if (node->right_ && !node->left_) swap_nodes(node, node->right_);
      if (node->left_ && !node->right_) swap_nodes(node, node->left_);
      if (node->color_ == BLACK && (!node->right_ && !node->left_))
        balance_delete(node);
      if (root_->left_ == node) root_->left_ = node->successor();
      if (root_->right_ == node) root_->right_ = node->predecessor();
      if (root_->parent_ == node)
        root_->parent_ = nullptr;
      else
        node->parent_->left_ == node ? node->parent_->left_ = nullptr
                                     : node->parent_->right_ = nullptr;
      size_--;
      node->left_ = nullptr;
      node->right_ = nullptr;
      node->parent_ = nullptr;
      node->color_ = RED;
      return node;
    }
    return nullptr;
  }

  /*
      Balance function after deletion process to support RBTree properties
      There are also several cases
      P - parent, G - grandparent, U - uncle, S - sibling, X - to be deleted
     node Case 1: S is red: switch colors of S and P; left rotate at P Case 2:
          S is black and both S's children are black:
              If P is red: change P to black
              else : make P a new X; repeat 1 case
      Case 3:
          S is black, S's left child is Red, S's right child is black:
              switch colors of S and its left child; right rotate at S, repeat
     case 4 Case 4: S is black, S's right child is red: change color of S's
     right child to red; change color of P to black; left rotate at P

  */
  void balance_delete(NodePtr node) {
    NodePtr s = nullptr;  // sibling
    while (node != root_->parent_ && node->color_ == BLACK) {
      if (node == node->parent_->left_) {
        s = node->parent_->right_;
        if (s->color_ == RED) {  // case 1
          std::swap(s->color_, node->parent_->color_);
          left_rotate(node->parent_);
          s = node->parent_->right_;  // change sibling for next cycle
        }
        if (s->color_ == BLACK && (!s->left_ || s->left_->color_ == BLACK) &&
            (!s->right_ || s->right_->color_ == BLACK)) {
          s->color_ = RED;  // case 2
          if (node->parent_->color_ == RED) {
            node->parent_->color_ = BLACK;
            break;
          }
          node = node->parent_;
        } else {  // if sibling is black and has two children
          if (!s->right_ ||
              s->right_->color_ == BLACK) {  // case when right child is black
                                             // (we need to make it red)
            s->color_ = RED;                 // case 3
            s->left_->color_ = BLACK;
            right_rotate(s);
            s = node->parent_->right_;
          }  // case 4
          s->color_ = node->parent_->color_;
          s->right_->color_ = BLACK;
          node->parent_->color_ = BLACK;
          left_rotate(node->parent_);
          break;
        }
      } else {
        s = node->parent_->left_;
        if (s->color_ == RED) {  // case 1
          std::swap(s->color_, node->parent_->color_);
          right_rotate(node->parent_);
          s = node->parent_->left_;
        }
        if (s->color_ == BLACK && (!s->left_ || s->left_->color_ == BLACK) &&
            (!s->right_ || s->right_->color_ == BLACK)) {
          s->color_ = RED;  // case 2
          if (node->parent_->color_ == RED) {
            node->parent_->color_ = BLACK;
            break;
          }
          node = node->parent_;
        } else {
          if (!s->left_ || s->left_->color_ == BLACK) {
            s->color_ = RED;  // case 3
            s->right_->color_ = BLACK;
            left_rotate(s);
            s = node->parent_->left_;
          }
          s->color_ = node->parent_->color_;  // case 4
          s->left_->color_ = BLACK;
          node->parent_->color_ = BLACK;
          right_rotate(node->parent_);
          break;
        }
      }
    }
    root_->parent_->color_ = BLACK;
  };

  // recursive deletion of tree contents
  void delete_all(NodePtr node) {
    if (node == nullptr) return;
    delete_all(node->left_);
    delete_all(node->right_);
    delete_node(node);
  };

  // recursive copy of tree contents
  NodePtr copy(NodePtr copy_node, NodePtr parent) {
    NodePtr new_node = new RBNode(copy_node);
    if (copy_node->left_) new_node->left_ = copy(copy_node->left_, new_node);
    if (copy_node->right_) new_node->right_ = copy(copy_node->right_, new_node);
    new_node->parent_ = parent;
    return new_node;
  };

  //      =============== NODE CLASS ===============

  // Node class
  class RBNode {
   public:
    // default constructor
    RBNode()
        : data_(Key{}),
          color_(RED),
          parent_(nullptr),
          left_(nullptr),
          right_(nullptr){};

    // constructor with value
    RBNode(const Key& value)
        : data_(value),
          color_(RED),
          parent_(nullptr),
          left_(nullptr),
          right_(nullptr){};

    // move contructor
    RBNode(const Key&& value)
        : data_(std::move(value)),
          color_(RED),
          parent_(nullptr),
          left_(nullptr),
          right_(nullptr){};

    // copies node
    RBNode(RBNode* node)
        : data_(node->data_),
          color_(node->color_),
          parent_(nullptr),
          left_(nullptr),
          right_(nullptr){};

    Key data_;
    NodeColor color_;
    NodePtr parent_;
    NodePtr left_;
    NodePtr right_;

    // Returns ptr to the next node
    NodePtr successor() noexcept {
      NodePtr node = this;
      // if node is root
      if (node->color_ == RED &&
          (node->parent_ == nullptr || node->parent_->parent_ == node)) {
        return node->right_;  // i move ptr to the max element because std
                              // library does the same
      }
      // if node has a right child
      else if (node->right_ != nullptr) {
        node = node->right_;
        while (node->left_ != nullptr) node = node->left_;
        // if node has no right child
      } else {
        NodePtr parent = node->parent_;
        while (node == parent->right_) {  // we move pointer until we find next
                                          // left child of parent
          node = parent;
          parent = parent->parent_;
        }
        // if node is root
        if (node->right_ != parent) node = parent;
      }
      return node;
    };

    // returns ptr to previous element
    NodePtr predecessor() noexcept {
      NodePtr node = this;
      if (node->color_ == RED &&
          (node->parent_ == nullptr || node->parent_->parent_ == node))
        return node->right_;
      else if (node->left_ != nullptr) {
        node = node->left_;
        while (node->right_ != nullptr) node = node->right_;
      } else {
        NodePtr parent = node->parent_;
        while (node == parent->left_) {
          node = parent;
          parent = parent->parent_;
        }
        if (node->left_ != parent) node = parent;
      }
      return node;
    };
  };

  //      =============== ITERATOR CLASS ===============

  class RBIterator {
    friend RBTree;

   public:
    // default constructor
    RBIterator() : node_(nullptr){};

    // constructor with node param
    RBIterator(NodePtr node) : node_(node){};

    // * overload returns data
    reference operator*() noexcept { return node_->data_; };

    // overload; checks if nodes are the same
    bool operator==(const iterator& other) noexcept {
      return node_ == other.node_;
    };

    // overload !=; checks if nodes are different
    bool operator!=(const iterator& other) noexcept {
      return node_ != other.node_;
    };

    // moves iterator to the next value
    iterator& operator++() noexcept {
      node_ = node_->successor();
      return *this;
    };

    // same for postfix increment
    iterator operator++(int) noexcept {
      iterator temp(node_);
      ++(*this);
      return temp;
    };

    // moves to the previous value
    iterator& operator--() noexcept {
      node_ = node_->predecessor();
      return *this;
    };

    // same for postfix decrement
    iterator operator--(int) noexcept {
      iterator temp(node_);
      --(*this);
      return temp;
    };

   private:
    // node value
    NodePtr node_;
  };

  // Const iterators
  class RBConstIterator {
    friend RBTree;

   public:
    // default constr
    RBConstIterator() : node_(nullptr){};

    RBConstIterator(const iterator& other) { node_ = other.node_; };

    const_reference operator*() const noexcept { return node_->data_; };

    const_iterator operator++() noexcept {
      node_ = node_->successor();
      return *this;
    };

    const_iterator operator++(int) noexcept {
      const_iterator temp(*this);
      ++(*this);
      return temp;
    };

    const_iterator operator--() noexcept {
      node_ = node_->predecessor();
      return *this;
    }

    const_iterator operator--(int) noexcept {
      const_iterator temp(*this);
      --(*this);
      return temp;
    };

   private:
    NodePtr node_;
    friend bool operator==(const const_iterator& it1,
                           const const_iterator& it2) noexcept {
      return it1.node_ == it2.node_;
    };

    friend bool operator!=(const const_iterator& it1,
                           const const_iterator& it2) noexcept {
      return it1.node_ != it2.node_;
    };
  };

  //      =============== TREE VARIABLES ===============
  NodePtr root_;    // end element
  size_type size_;  // number of elements
};
}  // namespace s21

#endif  // SRC_S21_TREE_H_