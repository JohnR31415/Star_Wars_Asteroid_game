#include "Profiler.h"
Profiler Profiler::theInstance;

Profiler& Profiler::getInstance()
{
	return theInstance;
}
#ifdef PROFILING_ON
#include <fstream>


static std::ofstream outStream;

void Profiler::addEntry(const char* category, float time)
{
	
	category;
	time;
	ProfileCategory& pc = categories[categoryIndex];
	if(frameIndex == 0)
	{
		pc.name = category;
		numCategories++;
	}
	categoryIndex++;
	pc.samples[frameIndex % sampleSize] = time;
	
}
void Profiler::newFrame()
{
	this->frameIndex++;
	this->categoryIndex = 0;
}
void Profiler::initialize(const char* fileName)
{
	this->fileName = fileName;
	this->frameIndex = -1;
	this->categoryIndex = 0;
}
void Profiler::shutdown()
{
	
	outStream.open(fileName, std::ios::trunc);
	for(int i = 0;i<numCategories;i++)
	{
		outStream << categories[i].name;
		outStream << getDelimeter(i);
	}

	//accounts for extra frame
	int actualFrames = frameIndex;
	if(categoryIndex == numCategories)
		actualFrames++;

	int endIndex;
	int startIndex;
	if(wrapped())
	{
		endIndex = frameIndex % sampleSize;
		startIndex = (endIndex + 1) % sampleSize;
		while(startIndex != endIndex)
		{
			writeFrame(startIndex);
			startIndex = (startIndex + 1) % sampleSize;
		}
		if(categoryIndex == numCategories)
			writeFrame(startIndex);
	}
	else
	{
		startIndex = 0;
		endIndex = actualFrames;
		while(startIndex < endIndex)
		{
			writeFrame(startIndex);
			startIndex++;
		}
			
	}
	outStream.close();
}
char Profiler::getDelimeter(int index) const
{
	return ((index + 1) < numCategories) ? ',' : '\n';
}
bool Profiler::wrapped() const
{
	return frameIndex >= sampleSize && frameIndex != -1;
}

void Profiler::writeFrame(int frameNumber) const
{
	for(int i=0;i<numCategories;i++)
	{
		outStream << categories[i].samples[frameNumber];
		outStream << getDelimeter(i);
	}
}
#endif