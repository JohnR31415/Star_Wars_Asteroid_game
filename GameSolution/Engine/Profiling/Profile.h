#pragma once
#ifndef PROFILE_H
#define PROFILE_H
#include "..\Timing\Timer.h"


class __declspec(dllexport) Profile
{
#if PROFILING_ON
	const char* category;
	Timer timer;
#endif
public:
#if PROFILING_ON
	Profile(const char* category);
	~Profile();
#else
	Profile(const char* category){category;}
	~Profile(){}
#endif
};

//#define PROFILE(category) Profiling::Profile p(category)
#define PROFILE(category) Profile p(category)

#endif