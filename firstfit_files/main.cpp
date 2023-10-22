#include "../allocation.h"
#include "../manager.h"

int main(int argc, char **argv) {
  manager myManager = manager("first");
  myManager.alloc(28);
  myManager.alloc(288);
  myManager.alloc(400);
  myManager.print("occ");
  
  return EXIT_SUCCESS;
}