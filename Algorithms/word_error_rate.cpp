#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <sstream>
using namespace std;

void split_string(vector<string>& split_result, const string& str) {
	stringstream ss(str);
	string tmp;

	while (getline(ss, tmp, ' ') && !tmp.empty()) {
		split_result.emplace_back(tmp);
	}
}

double word_error_rate(const string& r, const string& h) {
	vector<string> rw, hw;

	split_string(rw, r);
	split_string(hw, h);

	const auto m{ rw.size() };
	const auto n{ hw.size() };

	vector<vector<int>> d{ vector<vector<int>>(m + 1, vector<int>(n + 1)) };

	iota(begin(d[0]), end(d[0]), 0);
	for (int i = 0; i <= m; ++i) {
		d[i][0] = i;
	}

	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (rw[i - 1] == hw[j - 1]) {
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
	const string reference_string = "Live as if you were to die tomorrow.";
	const string hypothesis_string = "Learn as if you were to live forever.";

	cout << word_error_rate(reference_string, hypothesis_string) << endl;
}