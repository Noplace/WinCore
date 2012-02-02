#include "process_manager.h"

namespace core {

ProcessManager::ProcessManager() {

}

ProcessManager::~ProcessManager() {

}

void ProcessManager::AddProcess(Process* process) {
  process_list_.push_back(process);
}

void ProcessManager::Update(float dt) {

  for (auto i = process_list_.begin(); i != process_list_.end();) {
    auto process = *i;
    if (process->active() == false) {
      process->set_active(true);
      process->Initialize();
    }
    if (process->kill() == false && process->pause() == false)
      process->Update(dt);
    if (process->kill() == true) {
      process->Uninitialize();
      i = process_list_.erase(i);
    } else {
      ++i;
    }

  }

}

bool ProcessManager::HasProcesses() {
  return !process_list_.empty();
}

}