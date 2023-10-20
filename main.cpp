#include <iostream>
#include <unistd.h>
#include "allocation.h"

/**
 * PURELY TESTING
*/

using std::cout;
using std::endl;

int main(void) {
  allocation* allo = new allocation;
  // intptr_t 

  
  // sbrk();
  cout << sbrk(0) << endl;
  int i = brk(allo);
  if (i == 0) {
    cout << sbrk(0) << endl;
    return EXIT_SUCCESS;
  } else {
    return EXIT_FAILURE;
  }
}