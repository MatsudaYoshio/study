#include "KeyboardApp.h"

using namespace param;

const string KeyboardApp::dir_path = "D:/of_v0.9.2_vs_release/apps/myApps/KeyboardOptimization/texture/";

void KeyboardApp::setup() {
	ofSetBackgroundAuto(true);

	/* 一段目 */
	for (int i = 0; i < 13; ++i) {
		this->keyboard[i].setup(ofRectangle(this->tl_x + i*(this->key_size + this->w_space) + this->w_space, this->tl_y, this->key_size, this->key_size), this->dir_path + "key" + to_string(i + 1) + ".jpg");
	}

	/* 二段目 */
	for (int i = 13; i < 25; ++i) {
		this->keyboard[i].setup(ofRectangle(this->tl_x + this->key_size / 2 + (i - 13)*(this->key_size + this->w_space) + this->w_space, this->tl_y + this->key_size + this->h_space, this->key_size, this->key_size), this->dir_path + "key" + to_string(i + 1) + ".jpg");
	}

	/* 三段目 */
	for (int i = 25; i < 37; ++i) {
		this->keyboard[i].setup(ofRectangle(this->tl_x + this->key_size + (i - 25)*(this->key_size + this->w_space) + this->w_space, this->tl_y + 2 * this->key_size + 2 * this->h_space, this->key_size, this->key_size), this->dir_path + "key" + to_string(i + 1) + ".jpg");
	}

	/* 四段目 */
	for (int i = 37; i < this->key_num; ++i) {
		this->keyboard[i].setup(ofRectangle(this->tl_x + 3 * this->key_size / 2 + (i - 37)*(this->key_size + this->w_space) + this->w_space, this->tl_y + 3 * this->key_size + 3 * this->h_space, this->key_size, this->key_size), this->dir_path + "key" + to_string(i + 1) + ".jpg");
	}

	this->key_index_table.reserve(this->key_num);
	for (int i = 1; i <= 9; ++i) {
		this->key_index_table.emplace(make_pair('0' + i, i - 1));
	}
	this->key_index_table.emplace(make_pair('0', 9));
	this->key_index_table.emplace(make_pair('-', 10));
	this->key_index_table.emplace(make_pair('^', 11));
	this->key_index_table.emplace(make_pair('\\', 12));
	this->key_index_table.emplace(make_pair('q', 13));
	this->key_index_table.emplace(make_pair('w', 14));
	this->key_index_table.emplace(make_pair('e', 15));
	this->key_index_table.emplace(make_pair('r', 16));
	this->key_index_table.emplace(make_pair('t', 17));
	this->key_index_table.emplace(make_pair('y', 18));
	this->key_index_table.emplace(make_pair('u', 19));
	this->key_index_table.emplace(make_pair('i', 20));
	this->key_index_table.emplace(make_pair('o', 21));
	this->key_index_table.emplace(make_pair('p', 22));
	this->key_index_table.emplace(make_pair('@', 23));
	this->key_index_table.emplace(make_pair('[', 24));
	this->key_index_table.emplace(make_pair('a', 25));
	this->key_index_table.emplace(make_pair('s', 26));
	this->key_index_table.emplace(make_pair('d', 27));
	this->key_index_table.emplace(make_pair('f', 28));
	this->key_index_table.emplace(make_pair('g', 29));
	this->key_index_table.emplace(make_pair('h', 30));
	this->key_index_table.emplace(make_pair('j', 31));
	this->key_index_table.emplace(make_pair('k', 32));
	this->key_index_table.emplace(make_pair('l', 33));
	this->key_index_table.emplace(make_pair(';', 34));
	this->key_index_table.emplace(make_pair(':', 35));
	this->key_index_table.emplace(make_pair(']', 36));
	this->key_index_table.emplace(make_pair('z', 37));
	this->key_index_table.emplace(make_pair('x', 38));
	this->key_index_table.emplace(make_pair('c', 39));
	this->key_index_table.emplace(make_pair('v', 40));
	this->key_index_table.emplace(make_pair('b', 41));
	this->key_index_table.emplace(make_pair('n', 42));
	this->key_index_table.emplace(make_pair('m', 43));
	this->key_index_table.emplace(make_pair(',', 44));
	this->key_index_table.emplace(make_pair('.', 45));
	this->key_index_table.emplace(make_pair('/', 46));
	this->key_index_table.emplace(make_pair('\\', 47));

	ofAddListener(this->opt->exchange_event, this, &KeyboardApp::exchange);
}

void KeyboardApp::update() {

}

void KeyboardApp::draw() {
	for (int i = 0; i < this->key_num; ++i) {
		this->keyboard[i].draw();
	}

	for (int i = 0; i < this->key_num; ++i) {
		int alpha = 150;
		double r = 5;
		ofPoint& p = this->keyboard[i].rect.getCenter();
		for (int j = 0; j < this->keyboard[i].type_count; ++j) {
			r += 3;
			alpha -= exp(j/3);
			ofSetColor(ofColor::red, alpha);
			ofDrawCircle(p, r);
		}
	}

}

void KeyboardApp::keyPressed(int key) {
	try {
		this->keyboard[this->key_index_table.at(key)].set_state(static_cast<int>(KeyItem::STATE::PRESSED));
	}
	catch (std::out_of_range&) {

	}
}

void KeyboardApp::keyReleased(int key) {
	try {
		this->keyboard[this->key_index_table.at(key)].set_state(static_cast<int>(KeyItem::STATE::NO_PRESSED));
		++this->keyboard[this->key_index_table.at(key)].type_count;
	}
	catch (std::out_of_range&) {

	}
}

void KeyboardApp::exchange() {
	cout << "exhange!!" << endl;
}