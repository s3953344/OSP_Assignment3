#include "manager.h"
#include <unistd.h>
#include <exception>

// smallest chunk size as specified in assignment spec
#define SMALLEST_SIZE 32
#define LARGEST_SIZE 512

using std::cout;
using std::endl;
using std::string;

// This function sets the program break to be the value passed in by addr. If the setting of this values is 
// successful, brk() will return 0. You will use this function at the end of your program to reset the heap 
// frontier back to where it was at the start of your program, and it will free all memory you have 
// allocated. 

manager::~manager() {
  for (auto i : free) {
    delete i;
  }
  for (auto i : occupied) {
    delete i;
  }
  reset();
}

void manager::print(string list) {
  void* thing = initialProgramBreak;
  std::list<allocation*> list_p;
  if (list == "free") {
    cout << "### FREE ###" << endl;
    list_p = free;
  } else {
    cout << "### OCCUPIED ###" << endl;
    list_p = occupied;
  }

  for (allocation* chunk : list_p) {
    cout << chunk->partitionSize << endl;
    cout << chunk->size << endl;
    cout << chunk->space << endl;
    cout << "---------------" << endl;
    thing = chunk->space;
  }
}

manager::manager() { }

manager::manager(std::string strategy) { 
  this->strategy = strategy;
  initialProgramBreak = sbrk(0);
}

// This function will first look in the free list for a chunk big enough to meet the allocation request (based 
// on the previously set strategy). If a chunk large enough cannot be found, a new request will be sent 
// to the operating system using sbrk() system call to grow the heap. 
// In either case, the chunk and its metadata will be added to the allocated list before returning the 
// pointer to the memory chunk itself back to the caller that requested the memory allocation.
void * manager::alloc(std::size_t chunk_size) {
  if (strategy == "first") {
    return firstfit(chunk_size);
  } else if (strategy == "best") {
    return bestfit(chunk_size);
  } else {
    throw std::invalid_argument(strategy + " is not a valid allocation strategy (use 'first' or 'best')");
  }
}

void manager::dealloc(void * chunk) {
  for (auto i : occupied) {
    if (i->space == chunk) {
      // remove the pointer from occupied
      occupied.remove(i);
      // chunk is deallocated so 0 space is used.
      i->size = 0;
      free.push_back(i);
      return;
    }
  }

  // if reached this point, then pointer was not found
  // meaning trying to deallocate memory that doesnt exist
  cout << "FATAL ERROR: trying to deallocate memory that doesnt exist at location " << chunk << "." << endl;
  exit(EXIT_FAILURE);
}

// the chunk and its metadata will be added to the allocated list before returning the 
// pointer to the memory chunk itself back to the caller that requested the memory allocation. 
void * manager::firstfit(std::size_t chunk_size) {
  for (auto chunk : free) {
    // if chunk of right size found, remove from free and add to occupied
    if (chunk_size < chunk->partitionSize) {
      // fitFound = true;
      free.remove(chunk);
      chunk->size = chunk_size;
      occupied.push_back(chunk);
      return chunk->space;
    }
  }
  // if no chunk big enough found, use sbrk to grow heap
  return growHeap(chunk_size);
}

void * manager::bestfit(std::size_t chunk_size) {
  bool fitFound = false;
  allocation* best = free.front();
  for (auto chunk : free) {
    // find the smallest partition that fits the chunk to be allocated
    if (chunk->partitionSize < best->partitionSize && chunk_size < chunk->partitionSize) {
      fitFound = true;
      best = chunk;
    }
  }

  if (fitFound) {
    free.remove(best);
    best->size = chunk_size;
    occupied.push_back(best);
    return best->space;
  } else {
    return growHeap(chunk_size);
  }
}

void * manager::growHeap(std::size_t chunk_size) {
  int partitionSize = smallestValidChunk(chunk_size);
  void* ptr = sbrk(partitionSize);
  allocation* newChunk = new allocation();
  newChunk->size = chunk_size;
  newChunk->space = ptr;
  newChunk->partitionSize = partitionSize;
  occupied.push_back(newChunk);
  return newChunk->space;
}

void manager::reset() {
  if (!(brk(initialProgramBreak) == 0)) {
    cout << "Reset failed. Could not reset heap frontier back to start to dealloc all used memory." << endl;
    exit(1);
  };
}

int manager::smallestValidChunk(int inputChunk) {
  int size = SMALLEST_SIZE;
  while (size < inputChunk) {
    size *= 2;
  }
  return size;
}

void * manager::getNextToDeallocate() {
  if (occupied.size() == 0) {
    return nullptr;
  } else {
    return occupied.back()->space;
  }
}