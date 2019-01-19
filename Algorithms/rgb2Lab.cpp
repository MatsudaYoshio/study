#include <iostream>
#include <cmath>
#include <unordered_map>
#include <algorithm>
using namespace std;

unordered_map<char, int> rgb2Lab(const int r, const int g, const int b) {
	double sr = r, sg = g, sb = b;

	sr /= 255; sg /= 255; sb /= 255;

	auto f = [](double& v) { v = v > 0.04045 ? pow((v + 0.055) / 1.055, 2.4) : v / 12.92; };
	f(sr); f(sg); f(sb);

	auto x{ sr*0.4124 + sg*0.3576 + sb*0.1805 };
	auto y{ sr*0.2136 + sg*0.7152 + sb*0.0722 };
	auto z{ sr*0.0193 + sg*0.1192 + sb*0.9505 };

	x *= 1.0521;
	z *= 0.9184;

	auto h = [](double& v) { v = v > 0.008856 ? pow(v, 1.0 / 3) : 7.787*v + 0.1379; };
	h(x); h(y); h(z);

	return unordered_map<char, int>{ {'L', 116 * y - 16}, { 'a', 500 * (x - y) }, { 'b', 200 * (y - z) } };
}

int main() {
	unordered_map<char, int> Lab;
	Lab = rgb2Lab(211, 96, 21);
	cout << Lab['L'] << " " << Lab['a'] << " " << Lab['b'] << endl;
}