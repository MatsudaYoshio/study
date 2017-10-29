#pragma once
#ifndef ___Class_KeyItem
#define ___Class_KeyItem

#include "ofMain.h"

class KeyItem {
private:
	ofRectangle rect;
	ofTexture texture;
public:
	void setup(const ofRectangle &rect, const string& texture_path);
	void draw() const;
};

#endif