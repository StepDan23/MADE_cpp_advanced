#include "chuck_allocator.h"

using namespace task;

size_t CHUNK_SIZE = 16;

template<typename T>
Chunk<T>::Chunk(const size_t &capacity_)
    : capacity(capacity_),
      space_available(capacity_),
      data((T *) malloc(capacity_ * sizeof(T))) {}

template<typename T>
Chunk<T>::~Chunk() { free(this->data); }

template<class T>
ChuckAllocator<T>::ChuckAllocator()
    : n_watches(new size_t(1)) { *this->n_watches = 1; }

template<class T>
ChuckAllocator<T>::ChuckAllocator(ChuckAllocator &copy)
    : n_watches(copy.n_watches),
      chuck_list(copy.chuck_list) { *copy.n_watches += 1; };

template<class T>
ChuckAllocator<T>::~ChuckAllocator() {
  *(this->n_watches) -= 1;
  if (*this->n_watches == 0) {
    for (auto &chunk : this->chuck_list)
      delete chunk;
    delete this->n_watches;
  }
};

template<class T>
ChuckAllocator<T> &ChuckAllocator<T>::operator=(const ChuckAllocator<T> &copy) {
  if (this != &copy) {
    this->~ChuckAllocator();
    this->chuck_list = copy.chuck_list;
    this->n_watches = copy.n_watches;
    *copy.n_watches += 1;
  }
  return *this;
}

template<class T>
T *ChuckAllocator<T>::allocate(size_t n) {
  for (auto &chunk : this->chuck_list)
    if (chunk->space_available >= n) {
      size_t end_ptr = chunk->capacity - chunk->space_available;
      chunk->space_available -= n;
      return chunk->data + end_ptr;
    }
  size_t chunk_size = (CHUNK_SIZE >= n) ? CHUNK_SIZE : n;
  this->chuck_list.emplace_back(new Chunk<T>(chunk_size));
  this->chuck_list.back()->space_available -= n;
  return this->chuck_list.back()->data;
}

template<class T>
void ChuckAllocator<T>::deallocate(T *p, size_t n) {}

template<class T>
template<class U, class... Args>
void ChuckAllocator<T>::construct(U *p, Args &&... args) {
  new(p) U(args...);
};

template<class T>
template<class U>
void ChuckAllocator<T>::destroy(U *p) {
  p->~U();
};

int main() {
  ChuckAllocator<int> alloc;

  alloc.allocate(10);
  size_t size = 20;
  int *ptr = alloc.allocate(size);
  for (size_t i = 0; i < size; ++i)
    ptr[i] = i;
  ChuckAllocator<int> subs_alloc(alloc);
  subs_alloc.allocate(5);

  return 0;
}
