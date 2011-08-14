#define _USE_MATH_DEFINES
#include <math.h>
#include "spiral.h"

namespace core {
namespace animation {

Spiral::Spiral() : amplitude_(0) {

}

void Spiral::Process(DefaultTimeType delta) {
  float t = (current_play_time_ / max_time_) * M_PI * 6 ;
  *(value_ptrs_[0]) = amplitude_*t*cos(t);
  *(value_ptrs_[1]) = amplitude_*t*sin(t);
}

}
}