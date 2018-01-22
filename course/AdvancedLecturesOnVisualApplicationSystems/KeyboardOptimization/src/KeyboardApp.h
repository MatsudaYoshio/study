#pragma once
#ifndef ___Class_KeyboardApp
#define ___Class_KeyboardApp

#include "ofMain.h"
#include "AppParameters.h"
#include "KeyItem.h"
#include "OptimizationApp.h"
#include "PlotApp.h"
#include "ofxHistoryPlot.h"

class KeyboardApp : public ofBaseApp {
private:
	static const string dir_path; // キーのテクスチャがあるディレクトリのパス
	static constexpr int key_num = 48;
	static constexpr int w_space = 5;
	static constexpr int h_space = 5;
	static constexpr int key_size = 60;
	static constexpr int tl_x = param::W*0.15, tl_y = param::H*0.3;

	array<KeyItem, key_num> keyboard;
	array<double, key_num> nearest_key_distance;
	unordered_map<char, int> key_index_table;
	unordered_map<string, set<int>> home_position_group;
	array<double, key_num> key_eval;
	int type_count_sum;
	bool visualize_flag;

	const double evaluate_key(const int& type_count, const int& type_count_sum, const double& distance) const;
public:
	shared_ptr<OptimizationApp> opt;
	shared_ptr<PlotApp> plt;

	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed(int key);
	void keyReleased(int key);
	void start();
	void exchange();
	void switch_visual();
};

#endif