#include "manager.h"

#define SMALLEST_SIZE 32

manager::manager() {
  occupied = std::list<allocation*>();
  free = std::list<allocation*>();

  // populate free list
  int size = SMALLEST_SIZE;
  
  for (int i = size; i <= 512; i *= 2) {
    allocation* currAlloc = new allocation;
    currAlloc->size = i;
    currAlloc->space = nullptr;
    free.push_back(currAlloc);
  }

  for (auto i : free) {
    std::cout << i->size << ' ';
  }
}