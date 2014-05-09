#pragma once
#ifndef PROFILER
#define PROFILER

class __declspec(dllexport)Profiler
{
private:
	Profiler(){}
	Profiler(const Profiler&);
	Profiler& operator=(const Profiler&);
	static Profiler theInstance;
	
#if PROFILING_ON
	const char* fileName;
	static const unsigned int sampleSize = 3600;
	static const unsigned int categoryCount = 20;
	int frameIndex;
	int categoryIndex;
	int numCategories;
	struct ProfileCategory
	{
		const char* name;
		float samples[sampleSize];
	} categories[categoryCount];
	char getDelimeter(int index) const;
	bool wrapped() const;
	void writeFrame(int frameNumber) const;
#endif
public:
	static Profiler& getInstance();
#if PROFILING_ON
	void addEntry(const char* category, float time);
	void newFrame();
	void initialize(const char* fileName);
	void shutdown();
#else
	void addEntry(const char* category, float time){}
	void newFrame(){}
	void initialize(const char* fileName){}
	void shutdown(){}
#endif
};

#define profiler Profiler::getInstance()
#endif