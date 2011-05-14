#ifndef UISYSTEM_SYSTEM_ANIMATION_EASING_FUNCTIONS_H
#define UISYSTEM_SYSTEM_ANIMATION_EASING_FUNCTIONS_H

namespace core {
namespace animation {
namespace easing {

template<int pc1,int pc2,int pc3,int pc4,int pc5>
inline float ease(float t,float b,float c,float d) {
	t/=d;
  float ts=t*t;
	float tc=ts*t;
	return b+c*(pc5*tc*ts + pc4*ts*ts + pc3*tc + pc2*ts + pc1*t);
}

inline float in_out_cubic(float t,float b,float c,float d) {
	t/=d;
  float ts=t*t;
	float tc=ts*t;
  float factor = (-2*tc + 3*ts);
	return (1-factor)*b+c*factor;
}

inline float out_quintic(float t,float b,float c,float d) {
  t/=d;
	float ts=t*t;
	float tc=ts*t;
  float factor = (tc*ts + -5*ts*ts + 10*tc + -10*ts + 5*t);
	return (1-factor)*b+c*factor;
}

}
}
}

#endif