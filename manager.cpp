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
  if (list == "free") {
    cout << endl << "######### FREE #########" << endl;
    for (allocation* chunk : free) {
      cout << "Address: " << chunk->space << endl;
      cout << "Space used: " << chunk->size << endl;
      cout << "Partition size: " << chunk->partitionSize << endl;
      cout << "--------------------------" << endl;
    }
  } else {
    cout << endl << "######### OCCUPIED #########" << endl;
    for (allocation* chunk : occupied) {
      cout << "Address: " << chunk->space << endl;
      cout << "Space used: " << chunk->size << endl;
      cout << "Partition size: " << chunk->partitionSize << endl;
      cout << "--------------------------" << endl;
    }
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
    ++totalFreeListAccesses;
    // if chunk of right size found, remove from free and add to occupied
    if (chunk_size <= chunk->partitionSize) {
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
  // this odd bit of code means any valid chunk found in 'free' first will be replaced as best
  // because it will always be better than the starting chunk with size LARGEST_SIZE + 1.
  allocation starter;
  starter.partitionSize = LARGEST_SIZE + 1;
  allocation* best = &starter;

  // search through free list for best fit
  for (allocation* chunk : free) {
    ++totalFreeListAccesses;
    cout << chunk_size << endl;
    cout << (chunk_size <= chunk->partitionSize) << endl;
    cout << (chunk->partitionSize < best->partitionSize) << endl;
    // find the smallest partition that fits the chunk to be allocated
    if (chunk_size <= chunk->partitionSize && chunk->partitionSize < best->partitionSize) {
      fitFound = true;
      best = chunk;
    }
  }

  // only allocate if a valid chunk in free list is found
  if (fitFound) {
    free.remove(best);
    best->size = chunk_size;
    occupied.push_back(best);
    return best->space;
  } else {
    // or else, grow the heap and allocate more memory
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

void manager::printStats() {
  // total space allocated
  int total_pSpace = 0;
  for (auto i : free) {
    total_pSpace += i->partitionSize;
  }
  for (auto i : occupied) {
    total_pSpace += i->partitionSize;
  }

  // total space used
  int totalUsed = 0;
  for (auto i : occupied) {
    totalUsed += i->size;
  }

  // total space unused
  int unused = total_pSpace - totalUsed;

  cout << endl << endl << "===== STATS =====" << endl;
  cout << "Total partition space: " << total_pSpace << endl;
  cout << "Total space used: " << totalUsed << endl;
  cout << "Total unused: " << unused << endl;
  cout << "Free list access count: " << totalFreeListAccesses << endl;
}