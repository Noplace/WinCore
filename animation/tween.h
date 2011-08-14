#ifndef CORE_ANIMATION_TWEEN_H
#define CORE_ANIMATION_TWEEN_H
#include <vector>
#include "tween_template.h"

namespace core {
namespace animation {

typedef float DefaultTimeType;
typedef TweenTemplate<float,DefaultTimeType> Tween;
typedef std::vector<Tween*> TweenVector;

}
}

#endif