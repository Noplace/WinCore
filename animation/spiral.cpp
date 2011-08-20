#define _USE_MATH_DEFINES
#include <math.h>
#include "spiral.h"

namespace core {
namespace animation {

Spiral::Spiral() : amplitude_(1) ,start_theta_(0), max_theta_(M_PI * 6) {

}

void Spiral::Process(DefaultTimeType delta) {
  float t = (current_play_time_ / max_time_) * (max_theta_-start_theta_) ;
  *(value_ptrs_[0]) = amplitude_*t*cos(t+start_theta_);
  *(value_ptrs_[1]) = amplitude_*t*sin(t+start_theta_);
}

}
}