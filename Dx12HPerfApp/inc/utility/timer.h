#pragma once

#include <chrono>

class timer 
{
public:
	timer();
	~timer();

	void ClkTik();

	void ClkReset();

	double GetDeltaTimeInSec();

	double GetTotalTimeInSec();

protected:


private:
	//initial time
	std::chrono::high_resolution_clock::time_point Tp0;

	std::chrono::high_resolution_clock::duration DeltaTime;

	std::chrono::high_resolution_clock::duration TotalTime;


};

