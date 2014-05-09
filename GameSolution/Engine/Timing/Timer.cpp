#include "Timer.h"
#include <Windows.h>

double Timer::LIToSecs(LARGE_INTEGER& L)
{
	return ((double)L.QuadPart / (double)freq.QuadPart);
}

Timer::Timer()
{
	//sw.start.QuadPart = 0;
	//sw.stop.QuadPart = 0;
	//firstInterval.QuadPart = 0;
	//lastInterval.QuadPart = 0;
	//lastStartTime.QuadPart = 0;
	QueryPerformanceFrequency(&freq);
}

void Timer::start()
{
	QueryPerformanceCounter(&lastStartTime);
}

float Timer::stop()
{
	//QueryPerformanceCounter(&sw.stop);
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	LARGE_INTEGER delta;
	delta.QuadPart = time.QuadPart - lastStartTime.QuadPart;
	deltaTime = ((float)delta.QuadPart) / freq.QuadPart;
	deltaLastLap.QuadPart = time.QuadPart;
	return deltaTime;
}

float Timer::interval()
{
	LARGE_INTEGER thisTime;
	QueryPerformanceCounter(&thisTime);
	LARGE_INTEGER delta;
	delta.QuadPart = thisTime.QuadPart - lastInterval.QuadPart;
	deltaTime = ((float)delta.QuadPart) / freq.QuadPart;
	lastInterval.QuadPart = thisTime.QuadPart;
	return deltaTime;
}

bool Timer::initialize()
{
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&lastStartTime);
	QueryPerformanceCounter(&lastInterval);
	return true;
}

bool Timer::shutdown()
{
	return false;
}

void Timer::lap()
{
	LARGE_INTEGER thisTime;
	QueryPerformanceCounter(&thisTime);
	LARGE_INTEGER delta;
	delta.QuadPart = thisTime.QuadPart - lastStartTime.QuadPart;
	deltaTime = ((float)delta.QuadPart) / freq.QuadPart;
	lastStartTime.QuadPart = thisTime.QuadPart;
}

float Timer::lastLapTime() const
{
	return deltaTime;
}