#ifndef CORE_ANIMATION_SPIRAL_H
#define CORE_ANIMATION_SPIRAL_H

#include "tween.h"

namespace core {
namespace animation {

class Context;

class Spiral : public Tween {
 public:
  Spiral();
  void Process(DefaultTimeType delta);
  void set_from(float from) { from_ = from; }
  void set_to(float to) { to_ = to; }
  void set_value_ptrs(float** value_ptrs) { value_ptrs_[0] = value_ptrs[0]; value_ptrs_[1] = value_ptrs[1];  }
  void set_amplitude(float amplitude) { amplitude_ = amplitude; }
 private:
  float* value_ptr() { return 0; }
  void set_value_ptr(float* value_ptr) {  }
  float from_;
  float to_;
  float amplitude_;
  float* value_ptrs_[2];
};

}
}

#endif