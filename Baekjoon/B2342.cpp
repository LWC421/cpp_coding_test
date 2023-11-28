#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 100000 * 4 + 1;
#define V vector

int map[5][5] = { 
	{0, 2, 2, 2, 2},
	{0, 1, 3, 4, 3},
	{0, 3, 1, 3, 4},
	{0, 4, 3, 1, 3},
	{0, 3, 4, 3, 1},
};

int numCommand;
V<int> inputs;
V<V<V<int>>> dp;

int jump(int left, int right, int curr) {
	if (curr == numCommand) {
		// if all command finished
		return 0;
	}

	if (dp[left][right][curr] != INF) return dp[left][right][curr];

	int lValue = map[left][inputs[curr]] + jump(inputs[curr], right, curr + 1);
	int rValue = map[right][inputs[curr]] + jump(left, inputs[curr], curr + 1);

	int min = std::min(lValue, rValue);
	dp[left][right][curr] = min;

	return min;
}

int main(void) {
	 //freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int value;
	cin >> value;

	inputs.push_back(0);
	while (value != 0) {
		inputs.push_back(value);
		cin >> value;
	}
	
	numCommand = inputs.size();
	if (numCommand == 1) {
		printf("0");
		return 0;
	}

	dp.resize(5, V<V<int>>(5, V<int>(numCommand, INF)));

	printf("%d", jump(0, 0, 0));

	return 0;
}
