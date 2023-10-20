#pragma once
#include "allocation.h"
#include <iostream>
#include <list>

class manager {
public:
  manager();
  manager(std::list<allocation*> occupied, std::list<allocation*> free);
  void firstfit();
  void bestfit();
  void setup();
private:
  // basically simpler malloc()
  void * alloc(std::size_t chunk_size);
  // dealloc does not return the chunk to OS. It simply makes the chunk free/available to new requests
  // trying to dealloc memory that has not been allocated should terminate program (critical error)
  void dealloc(void * chunk);

  std::list<allocation*> occupied;
  std::list<allocation*> free;
};