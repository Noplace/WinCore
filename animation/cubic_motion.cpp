#include "easing_functions.h"
#include "cubic_motion.h"

namespace core {
namespace animation {

void CubicMotion::Process(DefaultTimeType delta) {
  *value_ptr_ = easing::in_out_cubic((float)current_play_time_,from_,to_,(float)max_time_);
//current_time_ += delta;
}

}
}