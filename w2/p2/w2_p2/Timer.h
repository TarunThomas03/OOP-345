#ifndef SDDS_TIMER_H
#define SDDS_TIMER_H
#include <chrono>

namespace sdds
{
	class Timer
	{
		std::chrono::time_point<std::chrono::steady_clock> m_start{};
	public:
		void start();
		long long int stop();
	};

}

#endif // !SDDS_TIMER_H



