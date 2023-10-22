#include "../allocation.h"
#include "../manager.h"
#include <fstream>

#define DATAFILE 1

using std::cout;
using std::endl;
using std::string;

int main(int argc, char **argv) {
  bool isValid = true;
  string datafile;
  std::ifstream file;  

  if (argc != 2) { 
    cout << "Incorrect number of args. Command args should be of form: " << endl;
    cout << "./bestfit {datafile}" << endl;
    isValid = false; 
  }

  // check for valid data filepath
  if (isValid) {
    datafile = argv[DATAFILE];
    file.open(datafile);
      if (!file) {
        isValid = false;
        cout << "Input filepath does not exist." << endl;
      }
  }

  // exit program if invalid args
  if (!isValid) {
    exit(EXIT_FAILURE);
  }

  // If the program reaches this point, then we can run everything like normal

  manager myManager = manager("first");
  // string datafile = argv[DATAFILE];

  /**
   * CONTRACT:
   * The datafile must be formatted correctly for this code to work
  */
  string line;
  string cmd;
  void * lastAllocated = nullptr;
  while (getline(file, line)) {
    // cout << line << endl;
    // detect which command from the file
    cmd = line.substr(0, 5);
    if (cmd == "alloc") {
      std::size_t pos = line.find(" ");
      int allocSize = std::stoi(line.substr(pos, line.length() - pos));
      lastAllocated = myManager.alloc(allocSize);
    } else if (cmd == "deall") {
      // the occupied chunks list is empty so there is nothing to deallocate.
      if (lastAllocated == nullptr) {
        cout << "FATAL ERROR: Cannot deallocate memory that has not been allocated" << endl;
        exit(EXIT_FAILURE);  
      } 
      // if not failed, deallocate.
      myManager.dealloc(lastAllocated);
      // if two deallocates in a row, follow LIFO order
      lastAllocated = myManager.getNextToDeallocate();
    } else {
      cout << "Invalid command in data file. Should either be 'alloc' or 'dealloc'." << endl;
      exit(EXIT_FAILURE);
    }
  }
  
  myManager.print("occu");
  myManager.print("free");
  myManager.printStats();
  
  return EXIT_SUCCESS;
}