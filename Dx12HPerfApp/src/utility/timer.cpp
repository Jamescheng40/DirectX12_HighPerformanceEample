#include "..\..\inc\utility\timer.h"

timer::timer()
	:DeltaTime(0)
	,TotalTime(0)

{
	Tp0 = std::chrono::high_resolution_clock::now();
}

timer::~timer()
{
}

void timer::ClkTik()
{
	//update the deltatime since lst
	auto tn = std::chrono::high_resolution_clock::now();

	DeltaTime = tn - Tp0;

	TotalTime += DeltaTime;

	Tp0 = tn;
}

void timer::ClkReset()
{
	Tp0 = std::chrono::high_resolution_clock::now();
	DeltaTime = std::chrono::high_resolution_clock::duration();

	TotalTime = std::chrono::high_resolution_clock::duration();



}

double timer::GetDeltaTimeInSec()
{
	return DeltaTime.count() * 1e-9;
}

double timer::GetTotalTimeInSec()
{
	return TotalTime.count() * 1e-9;
}
