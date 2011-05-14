#ifndef UISYSTEM_UTILITIES_TIMER2_H
#define UISYSTEM_UTILITIES_TIMER2_H

#include <windows.h>
#include "../types.h"

namespace utilities {

template<typename T>
inline T clamp(T x, T a, T b)   {   
  return x < a ? a : (x > b ? b : x);
}

class Timer {
 public:
  Timer():time_slice_(0) {
    Calibrate();
  }
  void Calibrate() {
    start_cycles_ = GetCurrentCycles();
    QueryPerformanceFrequency((LARGE_INTEGER*)&frequency_);
    resolution_ = 1.0f / frequency_;
  }

  float time_slice() { return time_slice_; }
  uint64_t elapsed_ticks() { return elapsed_ticks_; }

  void Tick() {
    uint64_t elapsed_cycles = GetCurrentCycles() - start_cycles_;
    start_cycles_ = GetCurrentCycles();
    elapsed_ticks_ = elapsed_cycles;
    time_slice_ = (1.f / 1000.f) * (float) elapsed_ticks_;
  }

  bool isTimeForUpdate(int framerate)
  {
      uint64_t actual_ticks = GetCurrentCycles() - start_cycles_;
      actual_ticks = clamp<uint64_t>(actual_ticks,(uint64_t)0,(uint64_t)(frequency_ / 20.0f));
      if (actual_ticks >= (uint64_t)(frequency_ / framerate   )) /// (1000.f / (float)framerate)
      {
        Tick();
        return true;
      }
      else
      {
        return false;
      }
  }
 private:
  float time_slice_;
  uint64_t elapsed_ticks_;
  uint64_t frequency_;
  float resolution_;
  uint64_t current_cycles_;
  uint64_t start_cycles_;

  uint64_t GetCurrentCycles() {
    QueryPerformanceCounter((LARGE_INTEGER*)&current_cycles_);
    return current_cycles_; 
  }

};

}

#endif