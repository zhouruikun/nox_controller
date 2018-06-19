#ifndef __TimerFunc_H
#define __TimerFunc_H
  
#ifdef   TimerFunc_globals
#define  TimerFunc_ext
#else
#define  TimerFunc_ext  extern
#endif 

TimerFunc_ext uint16 brightness_count,cousor_count;
TimerFunc_ext uint8 timer_b;

TimerFunc_ext void key_timer(void);
TimerFunc_ext void timer_rev1(void);
TimerFunc_ext void timer_1s_cousor(void);
TimerFunc_ext void timer_30s_brightness(void);
#endif

