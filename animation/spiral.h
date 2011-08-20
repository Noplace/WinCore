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
  void set_value_ptrs(float** value_ptrs) { value_ptrs_[0] = value_ptrs[0]; value_ptrs_[1] = value_ptrs[1];  }
  void set_amplitude(float amplitude) { amplitude_ = amplitude; }
  void set_max_theta(float max_theta) { max_theta_ = max_theta; }
  void set_start_theta(float start_theta) { start_theta_ = start_theta; }
 private:
  float* value_ptr() { return 0; }
  void set_value_ptr(float* value_ptr) {  }
  float amplitude_;
  float max_theta_;
  float start_theta_;
  float* value_ptrs_[2];
};

}
}

#endif