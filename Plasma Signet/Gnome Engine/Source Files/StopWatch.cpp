#include "StdAfx.h"
#include "StopWatch.h"


StopWatch::StopWatch(void)
{
	LARGE_INTEGER performanceFrequency;
	QueryPerformanceFrequency(&performanceFrequency);
	ticsPerMilliSec = performanceFrequency.QuadPart / 1000;
}


StopWatch::~StopWatch(void)
{
}

void StopWatch::startCounting(void)
{
	QueryPerformanceCounter(&startTime);
}

LARGE_INTEGER StopWatch::checkCount(void)
{
	QueryPerformanceCounter(&currentTime);
	LARGE_INTEGER temp;
	temp.QuadPart = (currentTime.QuadPart - startTime.QuadPart)/ticsPerMilliSec;
	return temp;
}