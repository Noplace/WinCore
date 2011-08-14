#ifndef CORE_ANIMATION_SERIES_TWEEN_H
#define CORE_ANIMATION_SERIES_TWEEN_H

#include "tween.h"

namespace core {
namespace animation {

class Series : public Tween {
 public:
  
  Series() : Tween() {
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

  void Process(DefaultTimeType delta) {

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
  DefaultTimeType max_time() { return max_time_; }
  void  set_max_time(DefaultTimeType max_time) {  }
  bool  running() { return running_; }

  void AddTween(Tween* tween) {
    max_time_ += tween->total_time();
    tween_list.push_back(tween);
  }
 private:
  TweenVector tween_list;
  int current_index;
  DefaultTimeType total_max;
};

}
}

#endif