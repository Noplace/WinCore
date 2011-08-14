#ifndef CORE_ANIMATION_CONTEXT_H
#define CORE_ANIMATION_CONTEXT_H

namespace core {
namespace animation {

class Context {
 public:
   Context() {}
  ~Context() {}

  void Process(DefaultTimeType dt) {
    TweenVector::iterator i;
    Tween* tween_ptr;
    for (i = tween_list.begin(); i != tween_list.end(); ++i) {
      tween_ptr =  (*i);
      tween_ptr->EncapsulatedProcess(dt);
    }
    //std::remove_if
  }

// private:
  TweenVector tween_list;
};

}
}

#endif