#include <chrono>
#include "Timer.h"

using namespace std;
using namespace chrono;
using namespace sdds;

void sdds::Timer::start()
{
	//set start to the time at call
	m_start = std::chrono::steady_clock::now();
}

long long int sdds::Timer::stop()
{
	//get time now
	time_point <std::chrono::steady_clock>end = std::chrono::steady_clock::now();
	//calculate and store difference between start and stop
	auto chrono_duration = duration_cast<nanoseconds>(end - m_start);

	long long int duration = chrono_duration.count();
	
	return duration;
}
