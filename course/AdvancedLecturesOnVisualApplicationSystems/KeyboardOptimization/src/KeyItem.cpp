#include "KeyItem.h"

KeyItem::KeyItem() :type_count(0), state(static_cast<int>(STATE::NO_PRESSED)) {}

void KeyItem::setup(const ofRectangle &rect, const string& texture_path) {
	this->rect = rect;
	ofLoadImage(this->texture, texture_path);
}

void KeyItem::draw() const {
	ofSetColor(this->state ? ofColor::blue : ofColor::white);
	this->texture.draw(this->rect);
}

void KeyItem::set_state(const int& state) {
	this->state = state;
}