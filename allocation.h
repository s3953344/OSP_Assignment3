#pragma once
#include <iostream>

struct allocation {
  std::size_t size;
  void *space;
};

// class allocation {
// public:
//   allocation();
//   std::size_t size;
//   void *space;
// };