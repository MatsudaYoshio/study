#include "TimerBaseClock.h"

TimerBaseClock::TimerBaseClock() {
	this->m_start = -1;
}

void TimerBaseClock::Clear() {
	this->m_start = -1;
}

bool TimerBaseClock::IsStarted() const {
	return (this->m_start != -1);
}

void TimerBaseClock::Start() {
	this->m_start = clock();
}

unsigned long TimerBaseClock::GetMs() {
	clock_t now;
	if (this->IsStarted()) {
		now = clock();
		clock_t dt = (now - this->m_start);
		return (unsigned long)(dt * 1000 / CLOCKS_PER_SEC);
	}
	return 0;
}