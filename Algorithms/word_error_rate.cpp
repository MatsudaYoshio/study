#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
using namespace std;

double word_error_rate(const string& r, const string& h) {
	const auto m{ r.size() };
	const auto n{ h.size() };

	vector<vector<int>> d{ vector<vector<int>>(m + 1, vector<int>(n + 1)) };

	iota(begin(d[0]), end(d[0]), 0);
	for (int i = 0; i <= m; ++i) {
		d[i][0] = i;
	}

	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (r[i - 1] == h[j - 1]) {
				d[i][j] = d[i - 1][j - 1];
			}
			else {
				d[i][j] = min({ d[i - 1][j - 1] + 1, d[i][j - 1] + 1, d[i - 1][j] + 1 });
			}
		}
	}

	return static_cast<double>(d[m][n]) / m;
}

int main() {
	cout << "Word Error Rate is " << word_error_rate("Live as if you were to die tomorrow.", "Learn as if you were to live forever.") << endl;
}
