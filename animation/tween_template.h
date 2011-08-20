#ifndef CORE_ANIMATION_TWEEN_TEMPLATE_H
#define CORE_ANIMATION_TWEEN_TEMPLATE_H

namespace core {
namespace animation {

class Context;

template <typename ValueType=float,typename TimeType=float>
class TweenTemplate {
 public:
  TweenTemplate() : repeat_count_(0),running_(false),current_play_time_((TimeType)0),
                                 max_time_((TimeType)0),value_ptr_(NULL),delay_time_((TimeType)0) {  
    context_ = NULL;
    ran_once = false;
  }
  virtual ~TweenTemplate() {

  }
  virtual void Play() { running_ = true; ran_once = false; set_current_time(0); }
  virtual void Pause() { running_ = false; }
  virtual void Resume() { running_ = true; }
  virtual void Stop() { running_ = false; set_current_time(0); }
  virtual void Process(TimeType delta) = 0;
  virtual void EncapsulatedProcess(TimeType delta) {
    if ( running() == true ) {
        if (delay_counter_ < delay_time_) {
          delay_counter_ += delta;
          if (delay_counter_ > delay_time_)
            delay_counter_ = delay_time_;
        } else {
          Process(delta);
          current_play_time_ += delta;
        }
        if ( current_time() > total_time() ) {
          ran_once = true;
          if (repeat_count_ == 0) {
            Stop();
          } else {
            Play();
            if (repeat_count_ != -1) 
              --repeat_count_;
          }
        }
    }
  }
  virtual ValueType* value_ptr() { return value_ptr_; }
  virtual void set_value_ptr(ValueType* value_ptr) { value_ptr_ = value_ptr; }
  virtual TimeType current_time() { return current_play_time_+delay_counter_; }
  virtual void set_current_time(TimeType current_time) { delay_counter_ = 0; current_play_time_ = 0; }
  virtual TimeType total_time() { return max_time_+delay_time_; }
  virtual void set_max_time(TimeType max_time) { max_time_ = max_time; }
  virtual TimeType delay_time() { return delay_time_; }
  virtual void set_delay_time(TimeType delay_time) { delay_time_ = delay_time; }
  virtual TimeType delay_counter() { return delay_counter_; }
  virtual bool running() { return running_; }
  virtual int repeat_count() { return repeat_count_; }
  virtual void set_repeat_count(int repeat_count) { repeat_count_ = repeat_count; }

  Context* context() { context_; }
  void set_context(Context* context) { context_ = context; }
  bool ran_once;
 protected:
  ValueType* value_ptr_;
  TimeType current_play_time_;
  TimeType max_time_;
  TimeType delay_time_;
  TimeType delay_counter_;
  Context* context_;
  int repeat_count_;
  bool running_;
};

}
}

#endif