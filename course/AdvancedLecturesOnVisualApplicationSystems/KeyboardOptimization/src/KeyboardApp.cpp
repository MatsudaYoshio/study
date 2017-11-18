#include "KeyboardApp.h"

using namespace param;

const string KeyboardApp::dir_path = "D:/of_v0.9.2_vs_release/apps/myApps/KeyboardOptimization/texture/";

const double KeyboardApp::euclid_distance(const ofPoint &p1, const ofPoint &p2) const {
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

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
	ofAddListener(this->opt->start_event, this, &KeyboardApp::start);

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
					d = this->euclid_distance(this->keyboard[i].rect.getCenter(), this->keyboard[k].rect.getCenter());
					if (d < this->nearest_key_distance[i]) {
						this->nearest_key_distance[i] = d;
					}
				}
				break;
			}
		}
	}
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
			alpha -= exp(j / 3);
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

	this->all_eval = accumulate(begin(this->key_eval), end(this->key_eval), 0.0);
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

	this->all_eval = accumulate(begin(this->key_eval), end(this->key_eval), 0.0);
}