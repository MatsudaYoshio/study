#pragma once
#ifndef ___Class_TimerBaseClock
#define ___Class_TimerBaseClock

#include <chrono>

class TimerBaseClock {
public:
	TimerBaseClock(); // �^�C�}���N���A
	void Clear(); // �^�C�}���N���A
	bool IsStarted() const; // �^�C�}���s���Ȃ�true��Ԃ�
	void Start(); // �^�C�}�J�n
	unsigned long GetMs(); // �^�C�}�J�n��̃~���b����
private:
	clock_t m_start;
};

#endif