#include "Profile.h"

#if PROFILING_ON
#include "Profiler.h"

Profile::Profile(const char* category) 
	: category(category)
{
	timer.initialize();
	timer.start();
}


Profile::~Profile()
{
	timer.stop();
	profiler.addEntry(category, timer.lastLapTime());
}

#endif