#ifndef UISYSTEM_SYSTEM_ANIMATION_ANIMATION_H
#define UISYSTEM_SYSTEM_ANIMATION_ANIMATION_H

#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

#include "easing_functions.h"

namespace core {
namespace animation {

class Context;

template <typename ValueType,typename TimeType>
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

typedef TweenTemplate<float,int> Tween;
typedef std::vector<Tween*> TweenVector;

class ParallelTween : public Tween {
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

  void Process(int delta) {
    TweenVector::iterator i;
    Tween* tween_ptr;
    for (i = tween_list.begin(); i != tween_list.end(); ++i) {
      tween_ptr =  (*i);
      tween_ptr->EncapsulatedProcess(delta);
    }
  }

  int max_time() { return max_time_; }
  void set_max_time(int max_time) {  }
  bool running() { return running_; }

  void AddTween(Tween* tween) {
    if (max_time_ < tween->total_time())
      max_time_ = tween->total_time();
    tween_list.push_back(tween);
  }
 private:
  TweenVector tween_list;
};


class SeriesTween : public Tween {
 public:
  
  SeriesTween() : Tween() {
    current_index = 0;
    total_max = 0;
  }

  void Play() { 
    Stop();
    //context_->tween_list.push_back(tween_list[current_index]);
    Tween::Play();
    tween_list[current_index]->Play();
  }

  void Pause() { 
    Tween::Pause();
    tween_list[current_index]->Pause();
  }
  void Resume() { 
    Tween::Resume();
    tween_list[current_index]->Resume();
  }

  void Stop() {
    Tween::Stop();
    running_ = false; 
    if (current_index < (int)tween_list.size())
      tween_list[current_index]->Stop();
    set_current_time(0); 
    current_index = 0;
    total_max = 0;
  }

  void Process(int delta) {

    if (current_index < (int)tween_list.size()) {
      Tween* tween_ptr = tween_list[current_index];
      
      /*if (tween_ptr->running() == false) {
          current_index++;
          if (current_index < (int)tween_list.size()) {
            context_->tween_list.push_back(tween_list[current_index]);
            tween_list[current_index]->Play();
          }
      }*/
 
      //if (tween_ptr->delay_counter() > 0)
      //  current_time_ -= delta;

      tween_ptr->EncapsulatedProcess(delta);

      if (tween_ptr->ran_once == true) {
          total_max +=  tween_ptr->total_time();
          current_play_time_ = total_max - delta; // a delta will be added after this
          current_index++;
          if (current_index < (int)tween_list.size())
            tween_list[current_index]->Play();
      }
      
    }
  }

   /*void EncapsulatedProcess(int delta) {
    if ( running() == true ) {
        Process(delta);
        current_time_ += delta;
        if ( current_index == (int)tween_list.size() )
          Stop();
    }

  }*/

  //int current_time() { return current_time_; }
  //void  set_current_time(int current_time) { current_time_ = current_time; }
  int max_time() { return max_time_; }
  void  set_max_time(float max_time) {  }
  bool  running() { return running_; }

  void AddTween(Tween* tween) {
    max_time_ += tween->total_time();
    tween_list.push_back(tween);
  }
 private:
  TweenVector tween_list;
  int current_index;
  int total_max;
};

class CubicMotion : public Tween {
 public:
  void Process(int delta) {
    *value_ptr_ = easing::in_out_cubic((float)current_play_time_,from_,to_,(float)max_time_);
    //current_time_ += delta;
  }

  void set_from(float from) { from_ = from; }
  void set_to(float to) { to_ = to; }
 private:
  float from_;
  float to_;
};

class SineWave : public Tween {
 public:
  void Process(int delta) {
    float d = (float)current_play_time_ / (float)(max_time_);
    *value_ptr_ = amp_*sin((float)M_PI*2.0f*d);
    //current_time_ += delta;
  }

  void set_amplitude(float amp) { amp_ = amp; }
  void set_frequency(float freq) { freq_ = freq; }
 private:
  float amp_;
  float freq_;
};

class Context {
 public:
   Context():delta_(1) {}
  ~Context() {}

  void Process() {
    TweenVector::iterator i;
    Tween* tween_ptr;
    for (i = tween_list.begin(); i != tween_list.end(); ++i) {
      tween_ptr =  (*i);
      tween_ptr->EncapsulatedProcess(delta_);
    }
    //std::remove_if
  }

  void set_delta(int delta) { delta_ = delta; }

// private:
  TweenVector tween_list;
  int delta_;
};

}
}

#endif