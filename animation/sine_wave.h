#ifndef CORE_ANIMATION_SINE_WAVE_H
#define CORE_ANIMATION_SINE_WAVE_H

#include "tween.h"


namespace core {
namespace animation {

class Context;


class SineWave : public Tween {
 public:
  void Process(DefaultTimeType delta);
  void set_amplitude(float amp) { amp_ = amp; }
  void set_frequency(float freq) { freq_ = freq; }
 private:
  float amp_;
  float freq_;
};

}
}

#endif