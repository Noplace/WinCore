/*****************************************************************************************************************
* Copyright (c) 2012 Khalid Ali Al-Kooheji                                                                       *
*                                                                                                                *
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software and              *
* associated documentation files (the "Software"), to deal in the Software without restriction, including        *
* without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell        *
* copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the       *
* following conditions:                                                                                          *
*                                                                                                                *
* The above copyright notice and this permission notice shall be included in all copies or substantial           *
* portions of the Software.                                                                                      *
*                                                                                                                *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT          *
* LIMITED TO THE WARRANTIES OF MERCHANTABILITY, * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.          *
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, * DAMAGES OR OTHER LIABILITY,      *
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE            *
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                                         *
*****************************************************************************************************************/
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