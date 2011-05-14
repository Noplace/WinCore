#ifndef CORE_PROCESS_H
#define CORE_PROCESS_H

#include <vector>
#include "types.h"

namespace core {

class Process {
 public:
  Process();
  ~Process();
 protected:



};

std::vector<Process*> ProcessList;

class ProcessManager {
 public:
  ProcessManager() {
  }
  virtual ~ProcessManager() {
  }
  void Update(uint64_t delta_time) {
    ProcessList::iterator i;
    while ( i != process_list_.end() ) {
    
    }
  }
 protected:
  ProcessList process_list_;
};

}

#endif