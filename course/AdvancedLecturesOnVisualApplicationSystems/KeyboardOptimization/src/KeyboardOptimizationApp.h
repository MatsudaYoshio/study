#pragma once
#ifndef ___Class_KeyboardOptimizationApp
#define ___Class_KeyboardOptimizationApp

#include "ofMain.h"
#include "AppParameters.h"
#include "KeyItem.h"

class KeyboardOptimizationApp : public ofBaseApp {
private:
	static constexpr int key_num = 48;
	static const string dir_path;
	static constexpr int w_space = 5;
	static constexpr int key_size = 70;
	static constexpr int tl_x = param::W*0.15, tl_y = param::H*0.3;

	array<KeyItem, key_num> keyboard;
public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
};

#endif