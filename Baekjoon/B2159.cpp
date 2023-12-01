#include <iostream>
#include <vector>
#include <cmath>

#define V vector

using namespace std;
using ll = long long;

struct Coord { int x, y; };


const ll INF = 9223372036854775807;

const int dx[] = { 0, -1, 0, 1, 0 };
const int dy[] = { 1, 0, -1, 0, 0 };

int main(void) {
	//freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int numNode;
	cin >> numNode;

	int x, y;
	cin >> x >> y;
	Coord init({ x, y });

	V<V<Coord>> coordss;
	coordss.resize(numNode + 1);
	
	// start coord
	for (int d = 0; d < 5; d++) {
		coordss[0].push_back(init);
	}

	for (int i = 1; i <= numNode; i++) {
		cin >> x >> y;
		for (int d = 0; d < 5; d++) {
			// insert 5 direction coords
			coordss[i].push_back({ x + dx[d], y + dy[d] });
		}
	}
	// input finished

	V<V<ll>> dp(numNode+1, V<ll>(5, INF));
	fill(dp[0].begin(), dp[0].end(), 0);
	for (int i = 1; i <= numNode; i++) {
		for (int curr = 0; curr < 5; curr++) {
			for (int prev = 0; prev < 5; prev++) {
				int distance = abs(coordss[i][curr].x - coordss[i - 1][prev].x);
				distance += abs(coordss[i][curr].y - coordss[i - 1][prev].y);

				dp[i][curr] = min(dp[i - 1][prev] + distance, dp[i][curr]);
			}
		}
	}

	ll result = INF;

	for (int d = 0; d < 5; d++) {
		result = min(result, dp[numNode][d]);
	}
	
	printf("%lld", result);

	return 0;
}