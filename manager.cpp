#include "manager.h"
#include <unistd.h>

// smallest chunk size as specified in assignment spec
#define SMALLEST_SIZE 32

manager::manager() { }

manager::manager(std::list<allocation*> occupied, std::list<allocation*> free) { 
  this->occupied = occupied;
  this->free = free;
}

void manager::setup() {
  std::list<allocation*> _occupied = std::list<allocation*>();
  std::list<allocation*> _free = std::list<allocation*>();

  // populate free list
  int size = SMALLEST_SIZE;
  
  for (int i = size; i <= 512; i *= 2) {
    // if successful, returns original program break
    void* programBreak = sbrk(i);
    // if unsuccessful, returns (void*) -1
    if (programBreak != (void*) -1) {
      allocation* currAlloc = new allocation;
      currAlloc->space = programBreak;
      currAlloc->size = i;
      _free.push_back(currAlloc);
    } else {
      // fatal error, sbrk() failed
      exit(1);
    }
    
  }

  occupied = _occupied;
  free = _free;

  for (auto i : free) {
    std::cout << i->size << ' ';
    std::cout << i->space << ' ' << std::endl;
  }
}