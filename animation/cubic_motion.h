#ifndef CORE_ANIMATION_CUBIC_MOTION_H
#define CORE_ANIMATION_CUBIC_MOTION_H

#include "tween.h"

namespace core {
namespace animation {

class Context;

class CubicMotion : public Tween {
 public:
  void Process(DefaultTimeType delta);
  void set_from(float from) { from_ = from; }
  void set_to(float to) { to_ = to; }
 private:
  float from_;
  float to_;
};

}
}

#endif