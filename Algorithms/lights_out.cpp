#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

/*
“ü—Í—á

3 4
....
.O..
....
....

o—Í—á

4

*/

constexpr char ON{ 'O' };
constexpr char OFF{ '.' };

constexpr int dx[] = { 1, 0, 0, -1 };
constexpr int dy[] = { 0, 1, -1, 0 };

void switch_light(char& l) {
	switch (l) {
	case ON:
		l = OFF;
		break;
	case OFF:
		l = ON;
	}
}

int main() {
	int N, M;
	cin >> N >> M;

	vector<vector<char>> light(N, vector<char>(M));
	for (int i = 0, x = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			cin >> light[i][j];
		}
	}

	int ans = INT_MAX;
	for (int b = 0; b < (1 << M); b++) {
		auto light_tmp = light;
		auto cnt = 0;
		for (int i = 0; i < M; ++i) {
			if (b & (1 << i)) {
				++cnt;
				switch_light(light_tmp[0][i]);
				for (int d = 0; d < 4; ++d) {
					const auto nx{ dy[d] };
					const auto ny{ i + dx[d] };
					if (nx >= 0 && nx < N && ny >= 0 && ny < M) {
						switch_light(light_tmp[nx][ny]);
					}
				}
			}
		}

		for (int j = 1; j < N; ++j) {
			for (int k = 0; k < M; ++k) {
				if (light_tmp[j - 1][k] == ON) {
					++cnt;
					switch_light(light_tmp[j][k]);
					for (int d = 0; d < 4; ++d) {
						const auto nx{ j + dy[d] };
						const auto ny{ k + dx[d] };
						if (nx >= 0 && nx < N && ny >= 0 && ny < M) {
							switch_light(light_tmp[nx][ny]);
						}
					}
				}
			}
		}

		for (int j = 0; j < N; ++j) {
			if (all_of(begin(light_tmp[j]), end(light_tmp[j]), [](const auto& x) { return x == OFF; })) {
				continue;
			}
			else {
				goto CANT_OFF;
			}
		}

		ans = min(ans, cnt);

	CANT_OFF:;
	}

	cout << ans << endl;
}