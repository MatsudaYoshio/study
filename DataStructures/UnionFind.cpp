#include "UnionFind.h"

using namespace std;

UnionFind::UnionFind(const int& size) :data(size, -1) {}

const int UnionFind::get_root(const int& x) {
	return this->data[x] < 0 ? x : this->data[x] = this->get_root(this->data[x]);
}

void UnionFind::union_set(int x, int y) {
	x = this->get_root(x);
	y = this->get_root(y);

	if (x != y) {
		if (this->data[y] < data[x]) {
			swap(x, y);
		}
		this->data[x] += this->data[y];
		this->data[y] = x;
	}
}

const bool UnionFind::is_same(const int& x, const int& y) {
	return this->get_root(x) == this->get_root(y);
}

const int UnionFind::get_size(const int& x) {
	return -this->data[this->get_root(x)];
}