// #pragma once
// #include "../manager.h"

// class FirstFit : public manager {
//   // This function will first look in the free list for a chunk big enough to meet the allocation request (based 
//   // on the previously set strategy). If a chunk large enough cannot be found, a new request will be sent 
//   // to the operating system using sbrk() system call to grow the heap. 
//   // In either case, the chunk and its metadata will be added to the allocated list before returning the 
//   // pointer to the memory chunk itself back to the caller that requested the memory allocation.
//   void * alloc(std::size_t chunk_size) override {
    
//     // for (auto chunk : free) {

//     // }
//   }
// };