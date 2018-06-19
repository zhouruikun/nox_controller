#include "stm32f10x.h"
#include "timer.h"

/*start a timer with the set timer number and time interval*/
TIMERITEMDEF TimerTable[TIMERAMOUNT];
void IRQ_Handle(void)
{u8 i=0;
	for(i=0;i<TIMERAMOUNT;i++)
	 {
		 
		 if(TimerTable[i].runningstate==SYSON)
		 {
			 if(TimerTable[i].overflag==SYSOFF)
			 {
				 if(TimerTable[i].interval>=1)
				  TimerTable[i].interval--;
				 else
				 {
					 TimerTable[i].overflag=SYSON;
					 TimerTable[i].interval=0;
				 }
			 }
		 }
	 }

}


/*the maximum timers should be less than TIMERAMOUNT*/
void StartTimer(u8 timernum, u32 interval)
{
  //  NVIC_SETPRIMASK();
    TimerTable[timernum].runningstate=SYSOFF;
    TimerTable[timernum].interval=interval;
    TimerTable[timernum].overflag=SYSOFF;
    TimerTable[timernum].runningstate=SYSON;
  //  NVIC_RESETPRIMASK();
}

/*stop a timer with the set timer number */
void StopTimer(u8 timernum)
{
  //  NVIC_SETPRIMASK();
    TimerTable[timernum].runningstate=SYSOFF;
    TimerTable[timernum].overflag=SYSOFF;
  //  NVIC_RESETPRIMASK();
}

/*read a timer with the set timer number.it will return 1 if it is over,
otherwise it will return 0 
also stop the timer*/
u8 ReadTimer(u8 timernum)
{
  //  NVIC_SETPRIMASK();
    if(TimerTable[timernum].runningstate==SYSON)
    {
        if(TimerTable[timernum].overflag==SYSON)
        {  //after overflag,operate ReadTimer function,timer will stop itself
            TimerTable[timernum].runningstate=SYSOFF;
            TimerTable[timernum].overflag=SYSOFF;
	//      	NVIC_RESETPRIMASK();
	      	return(OK);
			
        }
	    else
	    {
	 //       NVIC_RESETPRIMASK();
	        return(WAIT);
	    }
	 
    }
    else
    {
    //     NVIC_RESETPRIMASK();
         return(NOTSTART);
    }
}
/*read the time remainded*/
u32 ReadTimerValue(u8 timernum)
{
 return(TimerTable[timernum].interval);

}

/*to realize the delay time rated in the parameter interval*/
void DelayTimer(u16 interval)
{
    StartTimer(TIMERDELAY, interval);
    while(ReadTimer(TIMERDELAY)!=OK);
    
}	


