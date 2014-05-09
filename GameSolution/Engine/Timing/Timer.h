#pragma once
#ifndef TIMER
#define TIMER
#include <Windows.h>

typedef struct
{
	LARGE_INTEGER start;
	LARGE_INTEGER stop;
} stopWatch;

class __declspec(dllexport)Timer
{
	stopWatch sw;
	LARGE_INTEGER freq;
	LARGE_INTEGER firstInterval;
	LARGE_INTEGER lastInterval;

	LARGE_INTEGER lastStartTime;
	LARGE_INTEGER deltaLastLap;
	
	double LIToSecs(LARGE_INTEGER& l);

	float deltaTime;
public:
	
	Timer();
	void start();
	float stop();
	float interval();
	void lap();

	bool initialize();
	bool shutdown();

	float lastLapTime() const;
};

#endif