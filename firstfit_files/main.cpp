#include "../allocation.h"
#include "../manager.h"

int main(int argc, char **argv) {
  manager myManager = manager("first");
  myManager.alloc(28);
  myManager.alloc(288);
  void* thing = myManager.alloc(400);
  myManager.dealloc(thing);
  myManager.print("occ");
  myManager.print("free");
  
  return EXIT_SUCCESS;
}