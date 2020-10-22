#pragma once
#include<Windows.h>
class Timer
{
	int start, end;
public:
	Timer(int end);
	void Start();
	void Stop();
	bool IsTimeUp();

	int GetTimeStart() { return start; }
	int GetTimeEnd() { return end; }
	~Timer();
};

