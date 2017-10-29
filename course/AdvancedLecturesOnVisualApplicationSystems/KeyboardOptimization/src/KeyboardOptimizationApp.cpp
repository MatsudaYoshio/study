#include "KeyboardOptimizationApp.h"

using namespace param;

const string KeyboardOptimizationApp::dir_path = "D:/of_v0.9.2_vs_release/apps/myApps/KeyboardOptimization/texture/";

void KeyboardOptimizationApp::setup(){
	ofSetBackgroundAuto(true);

	for (int i = 0; i < 13; ++i) {
		this->keyboard[i].setup(ofRectangle(this->tl_x + i*(this->key_size + this->w_space) + this->w_space, this->tl_y, this->key_size, this->key_size), this->dir_path + "key" + to_string(i+1) + ".jpg");
	}
}

void KeyboardOptimizationApp::update(){

}

void KeyboardOptimizationApp::draw(){
	for (int i = 0; i < 13; ++i) {
		this->keyboard[i].draw();
	}
}

void KeyboardOptimizationApp::keyPressed(int key){

}

void KeyboardOptimizationApp::keyReleased(int key){

}