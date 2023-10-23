#pragma once
#include "allocation.h"
#include <iostream>
#include <list>

class manager {
public:
  manager();
  ~manager();
  // Pass in the strategy, either 'best' or 'first' at constructor
  manager(std::string strategy);
  // Allocate memory. calls either firstfit() or bestfit()
  void * alloc(std::size_t chunk_size);
  // Deallocate memory
  void dealloc(void * chunk);
  // print information. pass in either 'free' or 'occu' to specify for which list
  void print(std::string list);
  // in case there are two deallocate commands in a row, specify to remove in LIFO order
  void * getNextToDeallocate();
  // output stats
  void printStats();
private:
  // either best or first
  std::string strategy;
  void * firstfit(std::size_t chunk_size);
  void * bestfit(std::size_t chunk_size);
  // for when there are no valid free blocks, use sbrk() to grow the heap
  void * growHeap(std::size_t chunk_size);
  // calculate the smallest partition that fits a given chunk size
  int smallestValidChunk(int inputChunk);
  // reset heap frontier to inital position and does memory clean up
  void reset();
  // the amount of times the allocation strategy needs to access the free list
  int totalFreeListAccesses;

  std::list<allocation*> occupied;
  std::list<allocation*> free;
  void* initialProgramBreak;
};