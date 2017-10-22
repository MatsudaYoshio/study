#pragma once
#ifndef ___Class_TimerBase
#define ___Class_TimerBase

#include <chrono>

class TimerBase {
public:
	TimerBase(); // �^�C�}���N���A
	void Clear(); // �^�C�}���N���A
	bool IsStarted() const; // �^�C�}���s���Ȃ�true��Ԃ�
	void Start(); // �^�C�}�J�n
	unsigned long GetMs(); // �^�C�}�J�n��̃~���b����
private:
	std::chrono::system_clock::time_point m_start;
};

#endif