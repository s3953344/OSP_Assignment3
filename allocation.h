#pragma once
#include <iostream>
// where space will have been allocated with sbrk() initially
struct allocation {
  std::size_t partitionSize;
  std::size_t size;
  // the start of the program break. 
  void *space;
  
};