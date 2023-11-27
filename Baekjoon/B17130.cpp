#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const char EMPTY = '.';
const char WALL = '#';
const char RABBIT = 'R';
const char CARROT = 'C';
const char DOOR = 'O';

void printMap(vector<vector<int>> dp) {
	for (vector<int> row : dp) {
		for (int i : row) {
			printf("%d ", i);
		}
		printf("\n");
	}
}

const int dy[] = { 0, 1, -1 };
const int dx[] = { 1, 1, 1 };

struct Coord {
	int y, x;
};

int main(void) {
	//freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int yLength, xLength;
	cin >> yLength >> xLength;

	int numDoor = 0;
	int initY, initX;
	vector<vector<char>> map(yLength, vector<char>(xLength));
	for (int y = 0; y < yLength; y++) {
		for (int x = 0; x < xLength; x++) {
			char c;
			cin >> c;
			map[y][x] = c;

			if (c == RABBIT) {
				initY = y;
				initX = x;
			}
			else if (c == DOOR) {
				numDoor++;
			}
		}
	}

	if (numDoor == 0) {
		printf("-1");
		return 0;
	}

	vector<vector<int>> dp(yLength, vector<int>(xLength, -1));
	dp[initY][initX] = 0;

	queue<Coord> q;
	q.push({ initY, initX });

	int result = -1;

	while (!q.empty()) {
		Coord curr = q.front(); q.pop();
		int nY, nX, carrot;
		
		for (int d = 0; d < 3; d++) {
			nY = curr.y + dy[d];
			nX = curr.x + dx[d];
			carrot = dp[curr.y][curr.x];
			if (nY < 0 || nY >= yLength) continue;
			if (nX < 0 || nX >= xLength) continue;
			if (map[nY][nX] == WALL) continue;
			if (map[nY][nX] == DOOR) result = max(dp[curr.y][curr.x], result);
			if (map[nY][nX] == CARROT) carrot++;
			if (carrot <= dp[nY][nX]) continue;
			dp[nY][nX] = carrot;
			q.push({ nY, nX });
		}
	}

	printf("%d", result);

	return 0;
}
