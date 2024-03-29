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
#ifndef TIMER_HPT_H
#define TIMER_HPT_H


#include <windows.h>
#include "../types.h"

namespace core {
namespace timer {

class HPT {
 public:
  HPT() { }

  void Initialize() { Reset(); }
  void Reset() {
    last_counter_.QuadPart = -1; 
    total_time_passed_.QuadPart = 0;
    frames_ = 0;
    frequency_ = 0;
    time_elapsed_ = 0;
    fps_ = 0;
    avg_fps_ = 0;
    t1 = 0;
    t0 = 0;
    QueryPerformanceFrequency((LARGE_INTEGER*)&frequency_);
    resolution_ = 1.0f / frequency_;
    GetCurrentCycles();
    fps_cycles_elapsed = 0;
    delta_cycles_ = 0;
  }


  uint64_t GetCurrentCycles() {
    QueryPerformanceCounter((LARGE_INTEGER*)&current_cycles_);
    return current_cycles_; 
  }

  uint64_t DeltaCycles() {
    uint64_t old_cycles_ = current_cycles_;
    GetCurrentCycles();
    delta_cycles_ = current_cycles_ - old_cycles_;
    fps_cycles_elapsed += delta_cycles_;
    return delta_cycles_;
  }


  float fps() {

    frames_++;

    if (fps_cycles_elapsed >= frequency_) {
       fps_ = (float)frames_;
       frames_ = 0;
       fps_cycles_elapsed = 0;
    }

    return fps_;
  }

  float avg_fps() { 
    fps_ += 1/dt();

    if (frames_ == 60)
    {
      avg_fps_ = fps_ / 60;
      frames_ = 0;
      fps_ = 0;
    } else {
      frames_++;
    }
    return avg_fps_; 
  
  }
  float dt() { return t1-t0; }
  
  uint64_t frequency() { return frequency_; }

 private:
    
  LARGE_INTEGER last_counter_,first_frame_counter_;
  
  LARGE_INTEGER time_passed_,total_time_passed_;

  uint64_t current_cycles_;
  uint64_t frequency_;
  uint64_t fps_cycles_elapsed,delta_cycles_;
  float time_;
  float fps_;
  float avg_fps_;
  float resolution_;
  float t0,t1;
  float time_elapsed_;
  int frames_;

};

}
}

#endif