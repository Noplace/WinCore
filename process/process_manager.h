#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H
#include <vector>
#include "process.h"

namespace core {

class ProcessManager {
 public:
  typedef std::vector<Process*> ProcessList;
  ProcessManager();
  ~ProcessManager();
  void AddProcess(Process* process);
  void Update(float dt);
  bool HasProcesses();
 private:
  ProcessList process_list_;
};
}
#endif