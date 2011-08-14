#define _USE_MATH_DEFINES
#include <math.h>
#include "sine_wave.h"

namespace core {
namespace animation {

void SineWave::Process(DefaultTimeType delta) {
  float d = (float)current_play_time_ / (float)(max_time_);
  *value_ptr_ = amp_*sin((float)M_PI*2.0f*d);
  //current_time_ += delta;
}

}
}