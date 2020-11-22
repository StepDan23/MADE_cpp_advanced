#pragma once
#include <iterator>
#include <iostream>

namespace task {

template<class T, class Alloc = std::allocator<T>>
class list {
  struct Node;

 public:
  class iterator {
   public:
    using difference_type = ptrdiff_t;
    using value_type = T;
    using pointer = T *;
    using reference = T &;
    using iterator_category = std::bidirectional_iterator_tag;

    iterator();
    iterator(const iterator &);
    iterator(Node *);
    iterator &operator=(const iterator &other);
    iterator &operator++();
    iterator operator++(int);
    reference operator*() const;
    pointer operator->() const;
    iterator &operator--();
    iterator operator--(int);
    bool operator==(iterator other) const;
    bool operator!=(iterator other) const;

    friend class list;
   private:
    Node *ptr_;
  };

  class const_iterator {
   public:
    using difference_type = ptrdiff_t;
    using value_type = T;
    using pointer = T *;
    using reference = T &;
    using iterator_category = std::bidirectional_iterator_tag;

    const_iterator();
    const_iterator(const const_iterator &);
    const_iterator(const iterator &);
    const_iterator(Node *);
    const_iterator &operator=(const const_iterator &other);
    const_iterator &operator++();
    const_iterator operator++(int);
    reference operator*() const;
    pointer operator->() const;
    const_iterator &operator--();
    const_iterator operator--(int);
    bool operator==(const_iterator other) const;
    bool operator!=(const_iterator other) const;

    friend class list;
   private:
    Node *ptr_;
  };

  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  list();
  explicit list(const Alloc &alloc);
  list(size_t count, const T &value, const Alloc &alloc = Alloc());
  explicit list(size_t count, const Alloc &alloc = Alloc());

  ~list();

  list(const list &other);
  list(list &&other);
  list &operator=(const list &other);
  list &operator=(list &&other);

  Alloc get_allocator() const;

  T &front();
  const T &front() const;

  T &back();
  const T &back() const;

  iterator begin();
  iterator end();

  const_iterator cbegin() const;
  const_iterator cend() const;

  reverse_iterator rbegin();
  reverse_iterator rend();

  const_reverse_iterator crbegin() const;
  const_reverse_iterator crend() const;

  bool empty() const;
  size_t size() const;
  size_t max_size() const;
  void clear();

  iterator insert(const_iterator pos, const T &value);
  iterator insert(const_iterator pos, T &&value);
  iterator insert(const_iterator pos, size_t count, const T &value);

  iterator erase(const_iterator pos);
  iterator erase(const_iterator first, const_iterator last);

  void push_back(const T &value);
  void push_back(T &&value);
  void pop_back();

  void push_front(const T &value);
  void push_front(T &&value);
  void pop_front();

  template<class... Args>
  iterator emplace(const_iterator pos, Args &&... args);

  template<class... Args>
  void emplace_back(Args &&... args);

  template<class... Args>
  void emplace_front(Args &&... args);

  void resize(size_t count);
  void swap(list &other);

  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void remove(const T &value);
  void reverse();
  void unique();
  void sort();

  // Your code goes here?..

 private:
  struct Node {
    T data;
    Node *prev;
    Node *next;

    Node(const T &data_) : data(data_), prev(nullptr), next(nullptr) {}

    Node(Node *prev_, Node *next_) : prev(prev_), next(next_) {}

    Node(const T &data_, Node *prev_, Node *next_) : data(data_),
                                                     prev(prev_),
                                                     next(next_) {}

    Node(T &&data_, Node *prev_, Node *next_) : data(std::move(data_)),
                                                prev(prev_),
                                                next(next_) {};
    Node(const Node &other) : data(other.data_),
                              prev(other.prev_),
                              next(other.next_) {}
  };

  size_t size_;
  Node *head_;
  Node *tail_;
  typename Alloc::template rebind<Node>::other alloc_;
};

//class one {
// iterator
template<class T, class Alloc>
list<T, Alloc>::iterator::iterator(): ptr_(nullptr) {}

template<class T, class Alloc>
list<T, Alloc>::iterator::iterator(const iterator &other): ptr_(other.ptr_) {}

template<class T, class Alloc>
list<T, Alloc>::iterator::iterator(Node *node_): ptr_(node_) {}

template<class T, class Alloc>
typename list<T, Alloc>::iterator &
list<T, Alloc>::iterator::operator=(const list<T, Alloc>::iterator &other) {
  if (this != &other)
    ptr_ = other.ptr_;
  return *this;
}

template<class T, class Alloc>
typename list<T, Alloc>::iterator &list<T, Alloc>::iterator::operator++() {
  ptr_ = ptr_->next;
  return *this;
}

template<class T, class Alloc>
typename list<T, Alloc>::iterator list<T, Alloc>::iterator::operator++(int) {
  iterator postfix_node(*this);
  ptr_ = ptr_->next;
  return postfix_node;
}

template<class T, class Alloc>
typename list<T, Alloc>::iterator::reference
list<T, Alloc>::iterator::operator*() const {
  return ptr_->data;
}

template<class T, class Alloc>
typename list<T, Alloc>::iterator::pointer
list<T, Alloc>::iterator::operator->() const {
  return &static_cast<Node *>(ptr_)->data;
}

template<class T, class Alloc>
typename list<T, Alloc>::iterator &list<T, Alloc>::iterator::operator--() {
  ptr_ = ptr_->prev;
  return *this;
}

template<class T, class Alloc>
typename list<T, Alloc>::iterator list<T, Alloc>::iterator::operator--(int) {
  iterator postfix_node(*this);
  ptr_ = ptr_->prev;
  return postfix_node;
}

template<class T, class Alloc>
bool list<T, Alloc>::iterator::operator==(iterator other) const {
  return ptr_ == other.ptr_;
}

template<class T, class Alloc>
bool list<T, Alloc>::iterator::operator!=(iterator other) const {
  return ptr_ != other.ptr_;
}
// iterator

// cont_iterator
template<class T, class Alloc>
list<T, Alloc>::const_iterator::const_iterator(): ptr_(nullptr) {}

template<class T, class Alloc>
list<T, Alloc>::const_iterator::const_iterator(const const_iterator &other):
    ptr_(other.ptr_) {}

template<class T, class Alloc>
list<T, Alloc>::const_iterator::const_iterator(const iterator &other):
    ptr_(other.ptr_) {}

template<class T, class Alloc>
list<T, Alloc>::const_iterator::const_iterator(Node *node_): ptr_(node_) {}

template<class T, class Alloc>
typename list<T, Alloc>::const_iterator &
list<T, Alloc>::const_iterator::operator=
    (const list<T, Alloc>::const_iterator &other) {
  if (this != &other)
    ptr_ = other.ptr_;
  return *this;
}

template<class T, class Alloc>
typename list<T, Alloc>::const_iterator &
list<T, Alloc>::const_iterator::operator++() {
  ptr_ = ptr_->next;
  return *this;
}

template<class T, class Alloc>
typename list<T, Alloc>::const_iterator
list<T, Alloc>::const_iterator::operator++(int) {
  iterator postfix_node(*this);
  ptr_ = ptr_->next;
  return postfix_node;
}

template<class T, class Alloc>
typename list<T, Alloc>::const_iterator::reference
list<T, Alloc>::const_iterator::operator*() const {
  return ptr_->data;
}

template<class T, class Alloc>
typename list<T, Alloc>::const_iterator::pointer
list<T, Alloc>::const_iterator::operator->() const {
  return &static_cast<Node *>(ptr_)->data;
}

template<class T, class Alloc>
typename list<T, Alloc>::const_iterator &
list<T, Alloc>::const_iterator::operator--() {
  ptr_ = ptr_->prev;
  return *this;
}

template<class T, class Alloc>
typename list<T, Alloc>::const_iterator
list<T, Alloc>::const_iterator::operator--(int) {
  iterator postfix_node(*this);
  ptr_ = ptr_->prev;
  return postfix_node;
}

template<class T, class Alloc>
bool list<T, Alloc>::const_iterator::operator==(const_iterator other) const {
  return ptr_ == other.ptr;
}

template<class T, class Alloc>
bool list<T, Alloc>::const_iterator::operator!=(const_iterator other) const {
  return ptr_ != other.ptr_;
}
// const_iterator
//};

template<class T, class Alloc>
list<T, Alloc>::list(): size_(0) {
  head_ = alloc_.allocate(1);
  tail_ = alloc_.allocate(1);

  head_->prev = nullptr;
  head_->next = tail_;

  tail_->prev = head_;
  tail_->next = nullptr;
}

template<class T, class Alloc>
list<T, Alloc>::list(const Alloc &alloc): list<T, Alloc>() {
  alloc_ = alloc;
}

template<class T, class Alloc>
list<T, Alloc>::list(size_t count, const T &value, const Alloc &alloc):
    list<T, Alloc>(alloc) {
  size_ = 0;
  while (size_ < count)
    push_back(value);
}

template<class T, class Alloc>
list<T, Alloc>::list(size_t count, const Alloc &alloc) : list<T, Alloc>() {
  size_ = 0;
  resize(count);
}

template<class T, class Alloc>
list<T, Alloc>::~list() {
  clear();
  alloc_.deallocate(head_, 1);
  alloc_.deallocate(tail_, 1);
}

template<class T, class Alloc>
list<T, Alloc>::list(const list &other) : list<T, Alloc>() {
  for (auto it = other.cbegin(); it != other.cend(); ++it)
    push_back(*it);
}

template<class T, class Alloc>
list<T, Alloc>::list(list &&other) : list<T, Alloc>() {
  swap(other);
}

template<class T, class Alloc>
list<T, Alloc> &list<T, Alloc>::operator=(const list &other) {
  if (this != &other) {
    clear();
    for (auto it = other.cbegin(); it != other.cend(); ++it)
      push_back(*it);
  }
  return *this;
}

template<class T, class Alloc>
list<T, Alloc> &list<T, Alloc>::operator=(list &&other) {
  if (this != &other) {
    clear();
    head_->next = other.head_->next;
    head_->next->prev = head_;

    tail_->prev = other.tail_->prev;
    tail_->prev->next = tail_;
    size_ = other.size_;

    other.head_->next = other.tail_;
    other.tail_->prev = other.head_;
    other.size_ = 0;
  }
  return *this;
}

template<class T, class Alloc>
Alloc list<T, Alloc>::get_allocator() const {
  return alloc_;
}

template<class T, class Alloc>
T &list<T, Alloc>::front() {
  return head_->next->data;
}

template<class T, class Alloc>
const T &list<T, Alloc>::front() const {
  return head_->next->data;
}

template<class T, class Alloc>
T &list<T, Alloc>::back() {
  return tail_->prev->data;
}

template<class T, class Alloc>
const T &list<T, Alloc>::back() const {
  return tail_->prev->data;
}

template<class T, class Alloc>
typename list<T, Alloc>::iterator list<T, Alloc>::begin() {
  return iterator(head_->next);
}

template<class T, class Alloc>
typename list<T, Alloc>::iterator list<T, Alloc>::end() {
  return iterator(tail_);
}

template<class T, class Alloc>
typename list<T, Alloc>::const_iterator list<T, Alloc>::cbegin() const {
  return const_iterator(head_->next);
}

template<class T, class Alloc>
typename list<T, Alloc>::const_iterator list<T, Alloc>::cend() const {
  return const_iterator(tail_);
}

template<class T, class Alloc>
typename task::list<T, Alloc>::reverse_iterator list<T, Alloc>::rbegin() {
  return reverse_iterator(tail_->prev);
}

template<class T, class Alloc>
typename list<T, Alloc>::reverse_iterator list<T, Alloc>::rend() {
  return reverse_iterator(head_);
}

template<class T, class Alloc>
typename list<T, Alloc>::const_reverse_iterator
list<T, Alloc>::crbegin() const {
  return const_reverse_iterator(cend());
}

template<class T, class Alloc>
typename list<T, Alloc>::const_reverse_iterator list<T, Alloc>::crend() const {
  return const_reverse_iterator(cbegin());
}

template<class T, class Alloc>
bool list<T, Alloc>::empty() const {
  return size_ == 0;
}

template<class T, class Alloc>
size_t list<T, Alloc>::size() const {
  return size_;
}

template<class T, class Alloc>
size_t list<T, Alloc>::max_size() const {
  return alloc_.max_size();
}

template<class T, class Alloc>
void list<T, Alloc>::clear() {
  while (!empty())
    pop_back();
}

template<class T, class Alloc>
typename list<T, Alloc>::iterator
list<T, Alloc>::insert(const_iterator pos, const T &value) {
  Node *new_node = alloc_.allocate(1);
  alloc_.construct(new_node, value, pos.ptr_->prev, pos.ptr_);

  pos.ptr_->prev->next = new_node;
  pos.ptr_->prev = new_node;
  ++size_;
  return iterator(new_node);
}

template<class T, class Alloc>
typename list<T, Alloc>::iterator
list<T, Alloc>::insert(const_iterator pos, T &&value) {
  Node *new_node = alloc_.allocate(1);
  alloc_.construct(new_node, std::move(value), pos.ptr_->prev, pos.ptr_);

  pos.ptr_->prev->next = new_node;
  pos.ptr_->prev = new_node;
  ++size_;
  return iterator(new_node);
}

template<class T, class Alloc>
typename list<T, Alloc>::iterator
list<T, Alloc>::insert(const_iterator pos, size_t count, const T &value) {
  iterator it;
  for (int i = 0; i < count; ++i)
    it = insert(pos, value);
  return it;
}

template<class T, class Alloc>
typename list<T, Alloc>::iterator list<T, Alloc>::erase(const_iterator pos) {
  Node *pop_node = pos.ptr_;
  pos.ptr_->prev->next = pos.ptr_->next;
  pos.ptr_->next->prev = pos.ptr_->prev;
  --size_;
  alloc_.destroy(pop_node);
  alloc_.deallocate(pop_node, 1);

  return iterator(pos.ptr_->next);
}

template<class T, class Alloc>
typename list<T, Alloc>::iterator
list<T, Alloc>::erase(const_iterator first, const_iterator last) {
  for (auto it = first; it != last; ++it)
    erase(it);
  return iterator(last.ptr_);
}

template<class T, class Alloc>
void list<T, Alloc>::push_back(const T &value) {
  Node *new_node = alloc_.allocate(1);
  alloc_.construct(new_node, value, tail_->prev, tail_);
  tail_->prev->next = new_node;
  tail_->prev = new_node;
  ++size_;
}

template<class T, class Alloc>
void list<T, Alloc>::push_back(T &&value) {
  Node *new_node = alloc_.allocate(1);
  alloc_.construct(new_node, std::move(value), tail_->prev, tail_);
  tail_->prev->next = new_node;
  tail_->prev = new_node;
  ++size_;
}

template<class T, class Alloc>
void list<T, Alloc>::pop_back() {
  if (!empty()) {
    Node *pop_node = tail_->prev;
    pop_node->prev->next = tail_;
    tail_->prev = pop_node->prev;
    alloc_.destroy(pop_node);
    alloc_.deallocate(pop_node, 1);
    --size_;
  }
}

template<class T, class Alloc>
void list<T, Alloc>::push_front(const T &value) {
  Node *new_node = alloc_.allocate(1);
  alloc_.construct(new_node, value, head_, head_->next);
  head_->next->prev = new_node;
  head_->next = new_node;
  ++size_;
}

template<class T, class Alloc>
void list<T, Alloc>::push_front(T &&value) {
  Node *new_node = alloc_.allocate(1);
  alloc_.construct(new_node, std::move(value), head_, head_->next);
  head_->next->prev = new_node;
  head_->next = new_node;
  ++size_;
}

template<class T, class Alloc>
void list<T, Alloc>::pop_front() {
  if (!empty()) {
    Node *pop_node = head_->next;
    pop_node->next->prev = head_;
    head_->next = pop_node->next;
    alloc_.destroy(pop_node);
    alloc_.deallocate(pop_node, 1);
    --size_;
  }
}

template<class T, class Alloc>
template<class... Args>
typename list<T, Alloc>::iterator
list<T, Alloc>::emplace(typename list<T, Alloc>::const_iterator pos,
                        Args &&... args) {
  Alloc cur_aloc;
  Node *new_node = alloc_.allocate(1);
  T *data = cur_aloc.allocate(1);
  cur_aloc.construct(data, std::forward<Args>(args)...);
  alloc_.construct(new_node, std::move(*data), pos.ptr_->prev, pos.ptr_);
  cur_aloc.destroy(data);
  cur_aloc.deallocate(data, 1);
  pos.ptr_->prev->next = new_node;
  pos.ptr_->prev = new_node;
  ++size_;
  return iterator(new_node);
}

template<class T, class Alloc>
template<class... Args>
void list<T, Alloc>::emplace_back(Args &&... args) {
  emplace(end(), std::forward<Args>(args)...);
}

template<class T, class Alloc>
template<class... Args>
void list<T, Alloc>::emplace_front(Args &&... args) {
  emplace(begin(), std::forward<Args>(args)...);
}

template<class T, class Alloc>
void list<T, Alloc>::resize(size_t count) {
  while (size_ < count) {
    Node *new_node = alloc_.allocate(1);
    alloc_.construct(new_node, tail_->prev, tail_);
    tail_->prev->next = new_node;
    tail_->prev = new_node;
    ++size_;
  }
  while (size_ > count)
    pop_back();
}

template<class T, class Alloc>
void list<T, Alloc>::swap(list &other) {
  std::swap(size_, other.size_);
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
}

template<class T, class Alloc>
void list<T, Alloc>::merge(list &other) {
  for (auto it = cbegin(); it != end(); ++it) {
    while (*it > other.front()) {
      insert(it, other.front());
      other.pop_front();
    }
    if (other.empty())
      break;
  }
  while (!other.empty()) {
    push_back(other.front());
    other.pop_front();
  }
}

template<class T, class Alloc>
void list<T, Alloc>::splice(const_iterator pos, list &other) {
  if (!other.empty()) {
    pos.ptr_->prev->next = other.head_->next;
    other.head_->next->prev = pos.ptr_->prev;
    pos.ptr_->prev = other.tail_->prev;
    other.tail_->prev->next = pos.ptr_;

    size_ += other.size_;

    other.head_->next = other.tail_;
    other.tail_->prev = other.head_;
    other.size_ = 0;
  }
}

template<class T, class Alloc>
void task::list<T, Alloc>::remove(const T &value) {
  for (auto it = cbegin(); it != cend(); ++it) {
    if (*it == value)
      erase(it);
  }
}

template<class T, class Alloc>
void task::list<T, Alloc>::reverse() {
  if (size_ > 0) {
    iterator left_it = begin();
    iterator right_it = --end();
    while (left_it != right_it) {
      std::swap(*left_it, *right_it);
      if (++left_it == right_it--)
        break;
    }
  }
}

template<class T, class Alloc>
void task::list<T, Alloc>::unique() {
  for (iterator it = begin(); it != end(); ++it) {
    iterator next_it = it;
    ++next_it;
    while (*it == *(next_it))
      next_it = erase(next_it);
  }
}

template<class T, class Alloc>
void task::list<T, Alloc>::sort() {
  for (auto it = begin(); it != end(); ++it) {
    iterator min_it(it);
    for (auto it_1 = it; it_1 != end(); ++it_1)
      if (*min_it > *it_1)
        min_it = it_1;
    std::swap(*it, *min_it);
  }
}
}  // namespace task
