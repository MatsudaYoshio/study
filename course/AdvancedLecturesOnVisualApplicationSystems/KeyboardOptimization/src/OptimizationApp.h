#pragma once
#ifndef ___Class_OptimizationApp
#define ___Class_OptimizationApp

#include "ofMain.h"
#include "Button.h"

class OptimizationApp : public ofBaseApp {
private:
	Button start_button, exchange_button;
public:
	ofEvent<void> exchange_event;
	ofEvent<void> start_event;

	void setup();
	void update();
	void draw();
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
};

#endif