#include "KeyboardApp.h"

using namespace param;

const string KeyboardApp::dir_path = "D:/of_v0.9.2_vs_release/apps/myApps/KeyboardOptimization/texture/";

const double KeyboardApp::evaluate_key(const int& type_count, const int& type_count_sum, const double& distance) const {
	return type_count * distance / type_count_sum;;
}

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
#define ADD_KEY(key, num) this->##key_index_table.emplace(make_pair(key, num))
	ADD_KEY('0', 9);
	ADD_KEY('-', 10);
	ADD_KEY('^', 11);
	ADD_KEY('\\', 12);
	ADD_KEY('q', 13);
	ADD_KEY('w', 14);
	ADD_KEY('e', 15);
	ADD_KEY('r', 16);
	ADD_KEY('t', 17);
	ADD_KEY('y', 18);
	ADD_KEY('u', 19);
	ADD_KEY('i', 20);
	ADD_KEY('o', 21);
	ADD_KEY('p', 22);
	ADD_KEY('@', 23);
	ADD_KEY('[', 24);
	ADD_KEY('a', 25);
	ADD_KEY('s', 26);
	ADD_KEY('d', 27);
	ADD_KEY('f', 28);
	ADD_KEY('g', 29);
	ADD_KEY('h', 30);
	ADD_KEY('j', 31);
	ADD_KEY('k', 32);
	ADD_KEY('l', 33);
	ADD_KEY(';', 34);
	ADD_KEY(':', 35);
	ADD_KEY(']', 36);
	ADD_KEY('z', 37);
	ADD_KEY('x', 38);
	ADD_KEY('c', 39);
	ADD_KEY('v', 40);
	ADD_KEY('b', 41);
	ADD_KEY('n', 42);
	ADD_KEY('m', 43);
	ADD_KEY(',', 44);
	ADD_KEY('.', 45);
	ADD_KEY('/', 46);
	ADD_KEY('\\', 47);
#undef ADD_KEY

	ofAddListener(this->opt->exchange_event, this, &KeyboardApp::exchange);
	ofAddListener(this->opt->start_event, this, &KeyboardApp::start);
	ofAddListener(this->opt->visualize_event, this, &KeyboardApp::switch_visual);

	this->home_position_group.reserve(this->key_num);
	this->home_position_group.emplace(make_pair("llf", set<int>{ 0, 13, 25, 37 }));
	this->home_position_group.emplace(make_pair("lrf", set<int>{ 1, 14, 26, 38 }));
	this->home_position_group.emplace(make_pair("lmf", set<int>{ 2, 15, 27, 39 }));
	this->home_position_group.emplace(make_pair("lif", set<int>{ 3, 16, 28, 40, 4, 17, 29, 41 }));
	this->home_position_group.emplace(make_pair("rif", set<int>{ 5, 18, 30, 42, 6, 19, 31, 43 }));
	this->home_position_group.emplace(make_pair("rmf", set<int>{ 7, 20, 32, 44 }));
	this->home_position_group.emplace(make_pair("rrf", set<int>{ 8, 21, 33, 45 }));
	this->home_position_group.emplace(make_pair("rlf", set<int>{ 9, 22, 34, 46, 10, 23, 35, 47, 11, 24, 36, 12 }));

	fill(begin(this->nearest_key_distance), end(this->nearest_key_distance), DBL_MAX);
	double d;
	for (int i = 0; i < this->key_num; ++i) {
		for (const auto& g : this->home_position_group) {
			if (g.second.find(i) != end(g.second)) {
				for (const auto& k : g.second) {
					if (i == k) {
						continue;
					}
					d = ofDist(this->keyboard[i].rect.getCenter().x, this->keyboard[i].rect.getCenter().y, this->keyboard[k].rect.getCenter().x, this->keyboard[k].rect.getCenter().y);
					if (d < this->nearest_key_distance[i]) {
						this->nearest_key_distance[i] = d;
					}
				}
				break;
			}
		}
	}

	this->visualize_flag = true;
}

void KeyboardApp::update() {
}

void KeyboardApp::draw() {
	for (int i = 0; i < this->key_num; ++i) {
		this->keyboard[i].draw();
	}

	if (this->visualize_flag) {
		for (int i = 0; i < this->key_num; ++i) {
			int alpha = 150;
			double r = 5;
			ofPoint& p = this->keyboard[i].rect.getCenter();
			for (int j = 0; j < this->keyboard[i].type_count; ++j) {
				r += 3;
				alpha -= exp(j / 3);
				ofSetColor(ofColor::red, alpha);
				ofDrawCircle(p, r);
			}
		}
	}
}

void KeyboardApp::exit() {
	ofRemoveListener(this->opt->exchange_event, this, &KeyboardApp::exchange);
	ofRemoveListener(this->opt->start_event, this, &KeyboardApp::start);
}

void KeyboardApp::keyPressed(int key) {
	try {
		this->keyboard[this->key_index_table.at(key)].set_state(static_cast<int>(KeyItem::STATE::PRESSED));
	}
	catch (std::out_of_range&) {}
}

void KeyboardApp::keyReleased(int key) {
	try {
		this->keyboard[this->key_index_table.at(key)].set_state(static_cast<int>(KeyItem::STATE::NO_PRESSED));
		++this->keyboard[this->key_index_table.at(key)].type_count;
	}
	catch (std::out_of_range&) {}
}

void KeyboardApp::start() {
	this->type_count_sum = 0;
	for (int i = 0; i < this->key_num; ++i) {
		this->type_count_sum += this->keyboard[i].type_count;
	}

	if (this->type_count_sum == 0) {
		puts("error : Type some keys");
		return;
	}

	for (int i = 0; i < this->key_num; ++i) {
		this->key_eval[i] = this->evaluate_key(this->keyboard[i].type_count, this->nearest_key_distance[i], this->type_count_sum);
	}

	this->plt->plot->update(accumulate(begin(this->key_eval), end(this->key_eval), 0.0));
}

void KeyboardApp::exchange() {
	pair<int, int> exchange_pair;
	double best_eval = DBL_MAX, eval_tmp;
	for (int i = 0; i < this->key_num - 1; ++i) {
		for (int j = i + 1; j < this->key_num; ++j) {
			eval_tmp = this->evaluate_key(this->keyboard[j].type_count, this->nearest_key_distance[i], this->type_count_sum) + this->evaluate_key(this->keyboard[i].type_count, this->nearest_key_distance[j], this->type_count_sum) - this->key_eval[i] - this->key_eval[j];
			if (eval_tmp < best_eval) {
				best_eval = eval_tmp;
				exchange_pair = make_pair(i, j);
			}
		}
	}

	swap(this->keyboard[exchange_pair.first].texture, this->keyboard[exchange_pair.second].texture);
	swap(this->keyboard[exchange_pair.first].type_count, this->keyboard[exchange_pair.second].type_count);

	for (int i = 0; i < this->key_num; ++i) {
		this->key_eval[i] = this->evaluate_key(this->keyboard[i].type_count, this->nearest_key_distance[i], this->type_count_sum);
	}

	this->plt->plot->update(accumulate(begin(this->key_eval), end(this->key_eval), 0.0));
}

void KeyboardApp::switch_visual() {
	this->visualize_flag = !this->visualize_flag;
}