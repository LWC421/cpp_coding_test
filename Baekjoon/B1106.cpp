#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int main(void) {
	 //freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	
	int target, numCity;
	cin >> target >> numCity;

	vector<int> costs(numCity + 1);
	vector<int> effects(numCity + 1);

	for (int i = 1; i <= numCity; i++) {
		cin >> costs[i] >> effects[i];
	}
	//finish input

	int limit = 100 * target + 1;
	vector<vector<int>> dp(numCity + 1, vector<int>(limit));
	for (int y = 1; y <= numCity; y++) {
		int currCost = costs[y];
		int currEffect = effects[y];
		for (int x = 0; x < limit; x++) {
			if (x < currCost) { dp[y][x] = dp[y - 1][x]; continue; }
			int max = std::max(dp[y - 1][x - currCost] + currEffect, dp[y - 1][x]);
			max = std::max(dp[y][x - currCost] + currEffect, max);
			dp[y][x] = max;
		}
	}

	for (int x = 0; x < limit; x++) {
		for (int y = 1; y <= numCity; y++) {
			if (dp[y][x] >= target) {
				printf("%d", x);
				return 0;
			}
		}
	}

	return 0;
}
