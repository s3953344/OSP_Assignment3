#pragma once
#include "allocation.h"
#include <iostream>
#include <list>

class manager {
public:
  manager();
  ~manager();
  manager(std::string strategy);
  // manager(std::list<allocation*> occupied, std::list<allocation*> free);
  // void setup();
  void * alloc(std::size_t chunk_size);
  void dealloc(void * chunk);
  // void printFree();
  // void printOccu();
  void print(std::string list);
  void * getNextToDeallocate();
private:
  std::string strategy;
  // basically simpler malloc()
  // dealloc does not return the chunk to OS. It simply makes the chunk free/available to new requests
  // trying to dealloc memory that has not been allocated should terminate program (critical error)
  void * firstfit(std::size_t chunk_size);
  void * bestfit(std::size_t chunk_size);
  // for when there are no valid free blocks
  void * growHeap(std::size_t chunk_size);
  int smallestValidChunk(int inputChunk);
  void reset();


  std::list<allocation*> occupied;
  std::list<allocation*> free;
  void* initialProgramBreak;
};