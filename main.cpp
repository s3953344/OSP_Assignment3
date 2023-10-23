#include <iostream>
#include <unistd.h>
#include "allocation.h"
#include "manager.h"

/**
 * PURELY TESTING, YOU MAY IGNORE THIS FILE
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
  void* thing;
  manager myMan = manager("best");
  myMan.alloc(128);
  thing = myMan.alloc(512);
  myMan.dealloc(thing);
  thing = myMan.alloc(64);
  
  thing = myMan.alloc(512);
  myMan.dealloc(thing);
  thing = myMan.alloc(512);
  myMan.dealloc(thing);
  thing = myMan.alloc(512);
  myMan.dealloc(thing);
  myMan.alloc(32);

  myMan.print("free");
  myMan.print("occu");

  return EXIT_SUCCESS;
}