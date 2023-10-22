#include "../allocation.h"
#include "../manager.h"

int main(int argc, char **argv) {
  manager myManager = manager("best");
  myManager.alloc(28);
  myManager.alloc(288);
  void * thing = myManager.alloc(400);
  myManager.dealloc(thing);
  
  myManager.print("occu");


  myManager.print("free");
  
  return EXIT_SUCCESS;
}