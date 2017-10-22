#pragma once
#ifndef ___Class_TimerBaseClock
#define ___Class_TimerBaseClock

#include <chrono>

class TimerBaseClock {
public:
	TimerBaseClock(); // タイマをクリア
	void Clear(); // タイマをクリア
	bool IsStarted() const; // タイマ実行中ならtrueを返す
	void Start(); // タイマ開始
	unsigned long GetMs(); // タイマ開始後のミリ秒時間
private:
	clock_t m_start;
};

#endif