#include "Button.h"

Button::Button() :state(static_cast<int>(STATE::NO_PRESSED)), alpha(255) {
	font.loadFont("arial.ttf", 20);
}

void Button::setup(const ofRectangle& rect, const string& text) {
	this->rect = rect;
	this->text = text;
}

void Button::update() {
	this->alpha = this->state ? 128 : 255;
}

void Button::draw() {
	ofSetColor(ofColor::grey, this->alpha);
	ofDrawRectangle(this->rect);
	ofSetColor(ofColor::black, this->alpha);
	this->font.drawString(this->text, this->rect.getX() + 10, this->rect.getY() + 30);
}

void Button::set_state(const int& state) {
	this->state = state;
}