#pragma once
#ifndef ___Class_OptimizationApp
#define ___Class_OptimizationApp

#include "ofMain.h"
#include "Button.h"

class OptimizationApp : public ofBaseApp {
private:
	Button reset_button, start_button, exchange_button, visualize_button;
public:
	ofEvent<void> reset_event, start_event, exchange_event, visualize_event;

	void setup();
	void update();
	void draw();
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
};

#endif