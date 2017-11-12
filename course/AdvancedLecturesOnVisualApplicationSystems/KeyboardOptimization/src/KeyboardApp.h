#pragma once
#ifndef ___Class_KeyboardApp
#define ___Class_KeyboardApp

#include "ofMain.h"
#include "AppParameters.h"
#include "KeyItem.h"
#include "OptimizationApp.h"

class KeyboardApp : public ofBaseApp {
private:
	static const string dir_path;
	static constexpr int key_num = 48;
	static constexpr int w_space = 5;
	static constexpr int h_space = 5;
	static constexpr int key_size = 60;
	static constexpr int tl_x = param::W*0.15, tl_y = param::H*0.3;

	array<KeyItem, key_num> keyboard;
	unordered_map<char, int> key_index_table;
public:
	shared_ptr<OptimizationApp> opt;

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void exchange();
};

#endif