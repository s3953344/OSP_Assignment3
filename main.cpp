#include <iostream>
#include <unistd.h>
#include "allocation.h"
#include "manager.h"

/**
 * PURELY TESTING
*/

using std::cout;
using std::endl;

int main(void) {
  // allocation* allo = new allocation;
  // // intptr_t 

  // cout << sbrk(0) << endl;
  // sbrk(512);
  // cout << sbrk(0) << endl;
  // int i = brk(allo);
  // cout << sbrk(0) << endl;
  // sbrk(-511);
  // cout << sbrk(0) << endl;

  // if (i == 0) {
  //   cout << sbrk(0) << endl;
  //   return EXIT_SUCCESS;
  // } else {
  //   return EXIT_FAILURE;
  // }

  manager myMan = manager("first");
  cout << myMan.alloc(28) << endl;
  cout << myMan.alloc(67) << endl;
  cout << myMan.alloc(288) << endl;


  return EXIT_SUCCESS;
}