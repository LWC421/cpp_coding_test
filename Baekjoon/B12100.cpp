#include <iostream>
#include <vector>
#include <deque>

#define V vector

using namespace std;

struct Node {
	int value;
	bool combined;
};

int mapLength;
int maxValue;

void left(int count, V<V<int>> map);
void right(int count, V<V<int>> map);
void top(int count, V<V<int>> map);
void bottom(int count, V<V<int>> map);

void printMap(V<V<int>> map) {
	for (V<int> row : map) {
		for (int i : row) {
			printf("%d ", i);
		}
		printf("\n");
	}
	printf("---------------------\n\n");
}


void left(int count, V<V<int>> map) {
	if (count == 5) return;

	for (int y = 0; y < mapLength; y++) {
		deque<Node> dq;
		for (int x = 0; x < mapLength; x++) {
			if (map[y][x] == 0) continue;

			if (dq.empty()) {
				dq.push_back({ map[y][x], false });
				continue;
			}

			if (dq.back().combined) {
				dq.push_back({ map[y][x], false });
				continue;
			}

			if (dq.back().value == map[y][x]) {
				dq.pop_back();
				dq.push_back({ map[y][x] * 2, true });
			}
			else {
				dq.push_back({ map[y][x], false });
			}
		}

		int index = 0;
		for (auto &n : dq) {
			map[y][index] = n.value;
			maxValue = std::max(map[y][index], maxValue);
			index++;
		}
		for(; index < mapLength; index++){ 
			map[y][index] = 0;
		}
	}

	left(count+1, map);
	right(count + 1, map);
	top(count + 1, map);
	bottom(count + 1, map);
}

void right(int count, V<V<int>> map) {
	if (count == 5) return;

	for (int y = 0; y < mapLength; y++) {
		deque<Node> dq;
		for (int x = mapLength-1; x >= 0; x--) {
			if (map[y][x] == 0) continue;

			if (dq.empty()) {
				dq.push_back({ map[y][x], false });
				continue;
			}

			if (dq.back().combined) {
				dq.push_back({ map[y][x], false });
				continue;
			}

			if (dq.back().value == map[y][x]) {
				dq.pop_back();
				dq.push_back({ map[y][x] * 2, true });
			}
			else {
				dq.push_back({ map[y][x], false });
			}
		}

		int index = mapLength - 1;
		for (auto& n : dq) {
			map[y][index] = n.value;
			maxValue = std::max(map[y][index], maxValue);
			index--;
		}
		for (; index >= 0; index--) {
			map[y][index] = 0;
		}
	}

	left(count + 1, map);
	right(count + 1, map);
	top(count + 1, map);
	bottom(count + 1, map);
}

void top(int count, V<V<int>> map) {
	if (count == 5) return;

	for (int x = 0; x < mapLength; x++) {
		deque<Node> dq;
		for (int y = 0; y < mapLength; y++) {
			if (map[y][x] == 0) continue;

			if (dq.empty()) {
				dq.push_back({ map[y][x], false });
				continue;
			}

			if (dq.back().combined) {
				dq.push_back({ map[y][x], false });
				continue;
			}

			if (dq.back().value == map[y][x]) {
				dq.pop_back();
				dq.push_back({ map[y][x] * 2, true });
			}
			else {
				dq.push_back({ map[y][x], false });
			}
		}

		int index = 0;
		for (auto& n : dq) {
			map[index][x] = n.value;
			maxValue = std::max(map[index][x], maxValue);
			index++;
		}
		for (; index < mapLength; index++) {
			map[index][x] = 0;
		}
	}

	left(count + 1, map);
	right(count + 1, map);
	top(count + 1, map);
	bottom(count + 1, map);
}
void bottom(int count, V<V<int>> map) {
	if (count == 5) return;

	for (int x = 0; x < mapLength; x++) {
		deque<Node> dq;
		for (int y = mapLength - 1; y >= 0; y--) {
			if (map[y][x] == 0) continue;

			if (dq.empty()) {
				dq.push_back({ map[y][x], false });
				continue;
			}

			if (dq.back().combined) {
				dq.push_back({ map[y][x], false });
				continue;
			}

			if (dq.back().value == map[y][x]) {
				dq.pop_back();
				dq.push_back({ map[y][x] * 2, true });
			}
			else {
				dq.push_back({ map[y][x], false });
			}
		}

		int index = mapLength - 1;
		for (auto& n : dq) {
			map[index][x] = n.value;
			maxValue = std::max(map[index][x], maxValue);
			index--;
		}
		for (; index >= 0; index--) {
			map[index][x] = 0;
		}
	}

	left(count + 1, map);
	right(count + 1, map);
	top(count + 1, map);
	bottom(count + 1, map);
}

int main(void) {
	//freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> mapLength;
	maxValue = 0;

	V<V<int>> init(mapLength, V<int>(mapLength));
	for (int y = 0; y < mapLength; y++) {
		for (int x = 0; x < mapLength; x++) {
			cin >> init[y][x];
		}
	}

	left(0, init);
	right(0, init);
	top(0, init);
	bottom(0, init);

	printf("%d", maxValue);

	return 0;
}