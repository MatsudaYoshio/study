#pragma once
#ifndef ___Class_KeyItem
#define ___Class_KeyItem

#include "ofMain.h"

class KeyItem {
private:
	int state;
public:
	ofTexture texture;
	ofRectangle rect;
	int type_count;
	const enum class STATE {
		NO_PRESSED, PRESSED
	};

	KeyItem();
	void setup(const ofRectangle &rect, const string& texture_path);
	void draw() const;
	void set_state(const int& state);
};

#endif