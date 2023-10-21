#include "manager.h"
#include <unistd.h>
#include <exception>

// smallest chunk size as specified in assignment spec
#define SMALLEST_SIZE 32
#define LARGEST_SIZE 512

// brk(void * addr);
// This function sets the program break to be the value passed in by addr. If the setting of this values is 
// successful, brk() will return 0. You will use this function at the end of your program to reset the heap 
// frontier back to where it was at the start of your program, and it will free all memory you have 
// allocated. 

manager::manager() { 
}

manager::manager(std::string strategy) { 
  this->strategy = strategy;
  initialProgramBreak = sbrk(0);
}

// manager::manager(std::list<allocation*> occupied, std::list<allocation*> free) { 
//   this->occupied = occupied;
//   this->free = free;
//   initialProgramBreak = sbrk(0);
// }

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

}

// void manager::setup() {
//   std::list<allocation*> _occupied = std::list<allocation*>();
//   std::list<allocation*> _free = std::list<allocation*>();

//   // populate free list
//   int size = SMALLEST_SIZE;
  
//   for (int i = size; i <= LARGEST_SIZE; i *= 2) {
//     // if successful, returns original program break
//     void* programBreak = sbrk(i);
//     // if unsuccessful, returns (void*) -1
//     if (programBreak != (void*) -1) {
//       allocation* currAlloc = new allocation;
//       currAlloc->space = programBreak;
//       currAlloc->size = i;
//       _free.push_back(currAlloc);
//     } else {
//       // fatal error, sbrk() failed (this should never happen)
//       exit(1);
//     } 
//   }

//   occupied = _occupied;
//   free = _free;

  // PRINTING TO SEE IF EVERYTHING IS CORRECT
  // for (auto i : free) {
  //   std::cout << i->size << ' ';
  //   std::cout << i->space << ' ' << std::endl;
  // }
// }

// the chunk and its metadata will be added to the allocated list before returning the 
// pointer to the memory chunk itself back to the caller that requested the memory allocation. 
void * manager::firstfit(std::size_t chunk_size) {
  // bool fitFound = false;
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
  // if (!fitFound) {
    int partitionSize = smallestValidChunk(chunk_size);
    void* ptr = sbrk(partitionSize);
    allocation* newChunk = new allocation;
    newChunk->size = chunk_size;
    newChunk->space = ptr;
    newChunk->partitionSize = partitionSize;
    occupied.push_back(newChunk);
    return newChunk->space;
  // }

  // return nullptr;
}

void * manager::bestfit(std::size_t chunk_size) {
  return nullptr;
}

void manager::reset() {
  if (!(brk(initialProgramBreak) == 0)) {
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