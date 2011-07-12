#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H
#include <vector>
#include "process.h"

namespace core {

typedef std::vector<Process*> ProcessList;

class ProcessManager {
 public:
  ProcessManager();
  ~ProcessManager();
  void AddProcess(Process* process);
  void Update(uint64_t dt);
  bool HasProcesses();
 private:
  ProcessList process_list_;
};
}
#endif