#include "../allocation.h"
#include "../manager.h"

int main(int argc, char **argv) {
  manager myManager = manager("best");
  myManager.alloc(28);
  myManager.alloc(288);
  myManager.alloc(400);
  myManager.printOccu();
  
  return EXIT_SUCCESS;
}