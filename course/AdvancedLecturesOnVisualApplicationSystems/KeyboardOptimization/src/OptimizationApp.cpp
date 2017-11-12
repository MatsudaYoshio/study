#include "OptimizationApp.h"

void OptimizationApp::setup() {
	ofEnableAlphaBlending();
	ofBackground(ofColor::white);
	this->b.setup(ofRectangle(200, 50, 140, 40), "Exchange");
}

void OptimizationApp::update() {
	this->b.update();
}

void OptimizationApp::draw() {
	this->b.draw();
}

void OptimizationApp::mousePressed(int x, int y, int button) {
	if (this->b.rect.inside(x, y)) {
		this->b.set_state(true);
	}	
}

void OptimizationApp::mouseReleased(int x, int y, int button) {
	this->b.set_state(false);
	if (this->b.rect.inside(x, y)) {
		ofNotifyEvent(this->exchange_event);
	}
}