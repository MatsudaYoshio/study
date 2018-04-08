#pragma once
#ifndef ___Class_UnionFind
#define ___Class_UnionFind

#include <vector>

class UnionFind {
private:
	std::vector<int> data;
public:
	UnionFind(int size);
	void union_set(int x, int y);
	const bool is_same(int x, int y);
	const int get_root(int x);
	const int get_size(int x);
};

#endif
