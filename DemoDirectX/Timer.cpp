#include "Timer.h"



Timer::Timer(int end)
{
	start = 0;
	this->end = end;
}

void Timer::Start()
{
	start = GetTickCount();
}

void Timer::Stop()
{
	start = 0;
}

bool Timer::IsTimeUp()
{
	return GetTickCount() - start > end;
}

Timer::~Timer()
{
}
