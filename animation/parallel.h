#ifndef CORE_ANIMATION_PARALLEL_TWEEN_H
#define CORE_ANIMATION_PARALLEL_TWEEN_H

#include "tween.h"

namespace core {
namespace animation {

class Parallel : public Tween {
 public:
  
  void Play() { 
    Tween::Play();
    TweenVector::iterator i;
    Tween* tween_ptr;
    for (i = tween_list.begin(); i != tween_list.end(); ++i) {
      tween_ptr =  (*i);
      tween_ptr->Play();
    }
  }
  void Pause() { 
    Tween::Pause();
    TweenVector::iterator i;
    Tween* tween_ptr;
    for (i = tween_list.begin(); i != tween_list.end(); ++i) {
      tween_ptr =  (*i);
      tween_ptr->Pause();
    }
  }
  void Resume() { 
    Tween::Resume();
    TweenVector::iterator i;
    Tween* tween_ptr;
    for (i = tween_list.begin(); i != tween_list.end(); ++i) {
      tween_ptr =  (*i);
      tween_ptr->Resume();
    }
  }
  void Stop() {
    Tween::Stop();
    TweenVector::iterator i;
    Tween* tween_ptr;
    for (i = tween_list.begin(); i != tween_list.end(); ++i) {
      tween_ptr =  (*i);
      tween_ptr->Stop();
    }
  }

  void Process(DefaultTimeType delta) {
    TweenVector::iterator i;
    Tween* tween_ptr;
    for (i = tween_list.begin(); i != tween_list.end(); ++i) {
      tween_ptr =  (*i);
      tween_ptr->EncapsulatedProcess(delta);
    }
  }

  DefaultTimeType max_time() { return max_time_; }
  void set_max_time(DefaultTimeType max_time) {  }
  bool running() { return running_; }

  void AddTween(Tween* tween) {
    if (max_time_ < tween->total_time())
      max_time_ = tween->total_time();
    tween_list.push_back(tween);
  }
 private:
  TweenVector tween_list;
};

}
}

#endif