#pragma once
#ifndef ___Class_Button
#define ___Class_Button

#include "ofMain.h"

class Button {
private:
	ofTrueTypeFont font;
	string text;
	int state;
	int alpha;
public:
	ofRectangle rect;
	const enum class STATE {
		NO_PRESSED, PRESSED
	};
	Button();

	void setup(const ofRectangle& rect, const string& text);
	void update();
	void draw();

	void set_state(const int& state);
};

#endif