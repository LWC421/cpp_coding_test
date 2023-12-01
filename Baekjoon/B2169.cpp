#include <iostream>
#include <vector>
#include <cmath>

#define V vector

using namespace std;

const int INIT = -100 * 1000 * 1000;

const int LEFT = 0;
const int TOP = 1;
const int RIGHT = 2;

void print(V<V<V<int>>> dp) {
	for (V<V<int>> row: dp) {
		for (V<int> numbers: row) {
			printf("[");
			for (int num : numbers) {
				printf("%10d, ", num);
			}
			printf("]");
		}
		printf("\n");
	}
}


int main(void) {
	//freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int yLength, xLength;
	cin >> yLength >> xLength;

	V<V<int>> inputs(yLength + 2, V<int>(xLength + 2, 0));
	for (int y = 1; y <= yLength; y++) {
		for (int x = 1; x <= xLength; x++) {
			cin >> inputs[y][x];
		}
	}
	//input finished
	if (xLength == 1) {
		//if xLength is 1
		// then path is only oneway
		int result = 0;
		for (int y = 1; y <= yLength; y++) {
			result += inputs[y][1];
		}

		printf("%d", result);

		return 0;
	}


	V<V<V<int>>> dp(yLength + 2, V<V<int>>(xLength + 2, V<int>(3, INIT)));

	for (int d = 0; d < 3; d++) {
		dp[1][1][d] = inputs[1][1];
	}
	for (int x = 2; x <= xLength; x++) {
		for (int d = 0; d < 3; d++) {
			dp[1][x][d] = inputs[1][x] + dp[1][x - 1][d];
		}
	}


	for (int y = 2; y <= yLength; y++) {
		// Left side coord become from top or right
		int prevY = y - 1;

		for (int d = 0; d < 3; d++) {
			dp[y][1][LEFT] = std::max(dp[y][1][LEFT], dp[prevY][1][d] + inputs[y][1]);
			dp[y][1][TOP] = std::max(dp[y][1][TOP], dp[prevY][1][d] + inputs[y][1]);
		}

		// Right side coord become from top or left
		for (int d = 0; d < 3; d++) {
			dp[y][xLength][RIGHT] = std::max(dp[y][xLength][RIGHT], dp[prevY][xLength][d] + inputs[y][xLength]);
			dp[y][xLength][TOP] = std::max(dp[y][xLength][TOP], dp[prevY][xLength][d] + inputs[y][xLength]);
		}

		for (int x = 2; x < xLength; x++) {
			int prevX = x - 1;
			int currValue = inputs[y][x];
			for (int d = 0; d < 3; d++) {
				dp[y][x][TOP] = std::max(dp[y][x][TOP], dp[prevY][x][d]+ currValue);
			}
			dp[y][x][LEFT] = std::max(dp[y][x][LEFT], dp[y][prevX][LEFT] + currValue);
			dp[y][x][LEFT] = std::max(dp[y][x][LEFT], dp[y][prevX][TOP] + currValue);
		}

		for (int x = xLength - 1; x > 1; x--) {
			int prevX = x + 1;
			int currValue = inputs[y][x];
			dp[y][x][RIGHT] = std::max(dp[y][x][RIGHT], dp[y][prevX][RIGHT] + currValue);
			dp[y][x][RIGHT] = std::max(dp[y][x][RIGHT], dp[y][prevX][TOP] + currValue);
		}

		dp[y][1][RIGHT] = std::max(dp[y][1][RIGHT], dp[y][2][RIGHT] + inputs[y][1]);
		dp[y][1][RIGHT] = std::max(dp[y][1][RIGHT], dp[y][2][TOP] + inputs[y][1]);

		dp[y][xLength][LEFT] = std::max(dp[y][xLength][LEFT], dp[y][xLength - 1][LEFT] + inputs[y][xLength]);
		dp[y][xLength][LEFT] = std::max(dp[y][xLength][LEFT], dp[y][xLength - 1][TOP] + inputs[y][xLength]);
	}

	// result
	int result = INIT;
	for (int d = 0; d < 3; d++) {
		result = std::max(result, dp[yLength][xLength][d]);
	}
	printf("%d", result);

	return 0;
}