#include <iostream>
#include <cmath>
#include <unordered_map>
#include <algorithm>
using namespace std;

unordered_map<char, int> Lab2rgb(const int L, const int a, const int b) {
	double y = (L + 16.0) / 116.0;
	double x = y + a / 500.0;
	double z = y - b / 200.0;

	auto f = [](double& v, const double n) { v = v > 0.2068 ? n*pow(v, 3) : (v - 16.0 / 116.0) * 3 * pow(0.20689, 2)*n; };
	f(x, 0.9504); f(y, 1.0000); f(z, 1.0888);

	auto sr{ 3.2410 * x - 1.5374 * y - 0.4986 * z };
	auto sg{ -0.9692 * x + 1.8760 * y + 0.0416 * z };
	auto sb{ 0.0556 * x - 0.2040 * y + 1.0570 * z };

	auto h = [](double& v) { v = v <= 0.0031308 ? min(max(v*12.92, 0.0), 1.0)*255.0 + 0.5 : min(max(1.055*pow(v, 1.0 / 2.4) - 0.055, 0.0), 1.0)*255.0 + 0.5; };
	h(sr); h(sg); h(sb);

	return unordered_map<char, int>{ {'r', sr}, { 'g', sg }, { 'b', sb } };
}

int main()
{
	unordered_map<char, int> rgb;
	rgb = Lab2rgb(54, 41, 58);
	cout << rgb['r'] << " " << rgb['g'] << " " << rgb['b'] << endl;
}