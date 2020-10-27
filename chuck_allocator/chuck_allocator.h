#pragma once
#include <cstddef>
#include <list>

namespace task {

template<class T>
struct Chunk {
  size_t capacity;
  size_t space_available;
  T *data;

  Chunk(const size_t &capacity_);

  ~Chunk();

};

template<class T>
struct ChuckAllocator {
 protected:
  size_t *n_watches;
  std::list<Chunk<T> *> chuck_list;

 public:
  using value_type = T;
  using pointer = T *;
  using const_pointer = const T *;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  template<class U>
  struct rebind { typedef ChuckAllocator<U> other; };

  ChuckAllocator();

  ChuckAllocator(ChuckAllocator &copy);

  ~ChuckAllocator();

  ChuckAllocator &operator=(const ChuckAllocator &);

  T *allocate(size_t n);

  void deallocate(T *p, size_t n);

  template<class U, class... Args>
  void construct(U *p, Args &&... args);

  template<class U>
  void destroy(U *p);
};

} // namespace task