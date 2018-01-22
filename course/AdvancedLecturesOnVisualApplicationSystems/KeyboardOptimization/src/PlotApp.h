#pragma once
#ifndef ___Class_PlotApp
#define ___Class_PlotApp

#include "ofMain.h"
#include "ofxHistoryPlot.h"

class PlotApp : public ofBaseApp {
	void setup();
	void update();
	void draw();
public:
	std::unique_ptr<ofxHistoryPlot> plot;
};

#endif