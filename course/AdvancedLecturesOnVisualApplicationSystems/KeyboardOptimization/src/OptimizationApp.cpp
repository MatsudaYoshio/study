#include "OptimizationApp.h"

void OptimizationApp::setup() {
	ofEnableAlphaBlending();
	ofBackground(ofColor::white);
	this->start_button.setup(ofRectangle(50, 50, 140, 40), "Start");
	this->exchange_button.setup(ofRectangle(200, 50, 140, 40), "Exchange");
	this->visualize_button.setup(ofRectangle(350, 50, 140, 40), "Visualize");
}

void OptimizationApp::update() {
	this->start_button.update();
	this->exchange_button.update();
	this->visualize_button.update();
}

void OptimizationApp::draw() {
	this->start_button.draw();
	this->exchange_button.draw();
	this->visualize_button.draw();
}

void OptimizationApp::mousePressed(int x, int y, int button) {
	if (this->exchange_button.rect.inside(x, y)) {
		this->exchange_button.set_state(static_cast<int>(Button::STATE::PRESSED));
	}
	else if (this->start_button.rect.inside(x, y)) {
		this->start_button.set_state(static_cast<int>(Button::STATE::PRESSED));
	}
	else if (this->visualize_button.rect.inside(x,y)) {
		this->visualize_button.set_state(static_cast<int>(Button::STATE::PRESSED));
	}
}

void OptimizationApp::mouseReleased(int x, int y, int button) {
	this->start_button.set_state(static_cast<int>(Button::STATE::NO_PRESSED));
	this->exchange_button.set_state(static_cast<int>(Button::STATE::NO_PRESSED));
	this->visualize_button.set_state(static_cast<int>(Button::STATE::NO_PRESSED));
	if (this->exchange_button.rect.inside(x, y)) {
		ofNotifyEvent(this->exchange_event);
	}
	else if (this->start_button.rect.inside(x, y)) {
		ofNotifyEvent(this->start_event);
	}
	else if (this->visualize_button.rect.inside(x, y)) {
		ofNotifyEvent(this->visualize_event);
	}
}