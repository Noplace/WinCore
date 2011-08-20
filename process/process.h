#ifndef PROCESS_H
#define PROCESS_H

#include "../types.h"

namespace core {

class Process {
 public:
  Process() : pause_(false),kill_(false),active_(false) { }
  virtual ~Process() { }
  virtual void Initialize() = 0;
  virtual void Update(float) = 0;
  virtual void Uninitialize() = 0;
  bool pause() { return pause_; }
  void set_pause(bool pause) { pause_ = pause; }
  bool kill() { return kill_; }
  void set_kill(bool kill) { kill_ = kill; }
  bool active() { return active_; }
  void set_active(bool active) { active_ = active; }
 protected:
  bool pause_;
  bool kill_;
  bool active_;

};

}

#endif