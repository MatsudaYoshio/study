#include "KeyItem.h"

void KeyItem::setup(const ofRectangle &rect, const string& texture_path) {
	this->rect = rect;
	ofLoadImage(this->texture, texture_path);
}

void KeyItem::draw() const {
	ofSetColor(ofColor::white);
	this->texture.draw(this->rect);
}