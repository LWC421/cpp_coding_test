#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <algorithm>

#define V vector
#define Q queue
#define ALL(v) v.begin(), v.end()
#define FPop(q) q.front(); q.pop()

using namespace std;

int mapLength;
V<V<int>> map;

int dy[] = { 1, 0, -1, 0 };
int dx[] = { 0, 1, 0, -1 };

struct Coord { int y, x; };
struct Data { int y, x, weight; };

int main(void) {
	//freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> mapLength;

	map.resize(mapLength, V<int>(mapLength));

	for (int y = 0; y < mapLength; y++) {
		for (int x = 0; x < mapLength; x++) {
			cin >> map[y][x];
		}
	}
	// input finished

	Q<Coord> q;
	int groundValue = 1;
	for (int y = 0; y < mapLength; y++) {
		for (int x = 0; x < mapLength; x++) {
			if (map[y][x] != 1) continue;

			//if target is ground
			groundValue++;

			map[y][x] = groundValue;
			q.push({ y, x });
			while (!q.empty()) {
				Coord curr = FPop(q);
				int nY, nX;
				for (int d = 0; d < 4; d++) {
					nY = curr.y + dy[d];
					nX = curr.x + dx[d];
					if (nY < 0 || nY >= mapLength) continue;
					if (nX < 0 || nX >= mapLength) continue;

					if (map[nY][nX] == 1) {
						q.push({ nY, nX });
						map[nY][nX] = groundValue;
					}
				}
			}
		}
	}
	//Ground seperated

	int minDistance = 100 * 3;
	for (int y = 0; y < mapLength; y++) {
		for (int x = 0; x < mapLength; x++) {
			if (map[y][x] == 0) continue;

			V<V<bool>> visited(mapLength, V<bool>(mapLength));
			int numWater = 0;
			int nY, nX;
			for (int d = 0; d < 4; d++) {
				nY = y + dy[d];
				nX = x + dx[d];
				if (nY < 0 || nY >= mapLength) continue;
				if (nX < 0 || nX >= mapLength) continue;
				if (map[nY][nX] == 0) numWater++;
			}
			if (numWater == 0) continue;	// if target is surrounded

			int currGround = map[y][x];
			visited[y][x] = true;

			Q<Data> q;
			q.push({ y, x, 0 });
			while (!q.empty()) {
				Data curr = FPop(q);
				for (int d = 0; d < 4; d++) {
					nY = curr.y + dy[d];
					nX = curr.x + dx[d];
					if (nY < 0 || nY >= mapLength) continue;
					if (nX < 0 || nX >= mapLength) continue;
					if (map[nY][nX] != 0 && map[nY][nX] != currGround) {
						//if another ground
						minDistance = std::min(minDistance, curr.weight);
						continue;
					}
					if (visited[nY][nX]) continue;

					q.push({ nY, nX, curr.weight + 1 });
					visited[nY][nX] = true;
				}
			}
		}
	}

	printf("%d", minDistance);

	return 0;
}