#include "SimpleTimer.h"

#ifdef MAC_ENV
#include <mach/mach_time.h>
#endif

//***
//*** Public member functions
//***

//constructor
SimpleTimer::SimpleTimer() {
	isStartTimeSet = false;
	isEndTimeSet = false;
}

//destructor
SimpleTimer::~SimpleTimer() { }

//startTimer()
void SimpleTimer::startTimer() {
	startTime = getTimerTick();

	isStartTimeSet = true;
	isEndTimeSet = false;
}//end startTimer()

//stopTimer()
void SimpleTimer::stopTimer() {
	endTime = getTimerTick();

	isEndTimeSet = true;
}//end stopTimer()  

//getElapsedTime()
double SimpleTimer::getElapsedTime( int displayUnit ) {       
	frequency = getTimerFrequency();
	elapsedTime = -1;

	double unit;
	if( displayUnit == MILLI )
		unit = 1000.0;
	else if( displayUnit == MICRO )
		unit = 1000000.0; 

	if( frequency != 0 && isStartTimeSet ) {
		if ( ! isEndTimeSet ) {
			stopTimer();
		}
		elapsedTime = (unit/(double)frequency) * ( endTime - startTime );
	}

	return elapsedTime;
}//end getElapsedTime()


//***
//*** private member functions
//***
//getTimerFrequency()

frequency_t SimpleTimer::getTimerFrequency() {
#if   defined(WIN_ENV)
	LARGE_INTEGER frequency;
	int hiFreqTimer = QueryPerformanceFrequency( &frequency );

	if( hiFreqTimer )
		return frequency.QuadPart;
	else
		return 0;
#elif defined(MAC_ENV)
	static mach_timebase_info_data_t  sTimebaseInfo;

	if ( sTimebaseInfo.denom == 0 ) 
	{
		(void) mach_timebase_info( &sTimebaseInfo );
	}

	return ( ( sTimebaseInfo.denom * 1.0e9 ) / sTimebaseInfo.numer );

#else
	return 1000;
#endif
}//end getTimerFrequency()


//getTimerTick()
frequency_t SimpleTimer::getTimerTick() {
	frequency_t retVal = 0;

#ifdef WIN_ENV
	LARGE_INTEGER tick;
	QueryPerformanceCounter( &tick );
	retVal = tick.QuadPart;
#endif

#ifdef MAC_ENV
        retVal = mach_absolute_time();
#endif

#ifdef UNIX_ENV
	struct rusage ruse;
	getrusage( RUSAGE_SELF, &ruse );

	// We will use milli second as the unit to avoid overflow

	retVal = ( ruse.ru_utime.tv_sec * 1000 ) + ruse.ru_utime.tv_usec/1000 +
		     ( ruse.ru_stime.tv_sec * 1000 ) + ruse.ru_stime.tv_usec/1000;
#endif

	return retVal;

}//end getTimerTick(); 
