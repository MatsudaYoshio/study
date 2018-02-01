#pragma once
#ifndef ___Class_UnionFind
#define ___Class_UnionFind

#include <vector>

class UnionFind {
private:
	std::vector<int> data;
public:
	UnionFind(const int& size);
	void union_set(int x, int y);
	const bool is_same(const int& x, const int& y);
	const int get_root(const int& x);
	const int get_size(const int& x);
};

#endif