#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int dy[] = { 0, -1, 0, 1 };
const int dx[] = { 1, 0, -1, 0 };


int main(void) {
	//freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int top, left, bottom, right;

	cin >> top >> left >> bottom >> right;


	int yLength = bottom - top + 1;
	int xLength = right - left + 1;
	
	int mapLength = 0;
	
	mapLength = max(abs(top), abs(bottom));
	mapLength = max(mapLength, abs(left));
	mapLength = max(mapLength, abs(right));

	mapLength = mapLength * 2 + 1;

	int** map = new int*[yLength];
	for (int i = 0; i < yLength; i++) {
		map[i] = new int[xLength];
	}


	int center = mapLength / 2;

	top += center;
	bottom += center;
	left += center;
	right += center;


	int y = center, x = center;

	int nY, nX;
	int value = 1;
	int dir = 0;
	int length = 1;
	bool stop = false;
	while (!stop) {

		// repeat twice per length
		for (int re = 0; re < 2 && !stop; re++) {
			for (int l = 0; l < length && !stop; l++) {
				if (top <= y && y <= bottom) {
					if (left <= x && x <= right) {
						map[y-top][x-left] = value;
					}
				}
				value++;
				y += dy[dir];
				x += dx[dir];
				if (y < 0 || y >= mapLength) stop = true;
				if (x < 0 || x >= mapLength) stop = true;
			}
			dir = (dir + 1) % 4;
		}
		length++;
	}

	// map create complete


	//calculate max length of number
	int maxNumberLength = 0;

	for (int y = 0; y < yLength; y++) {
		for (int x = 0; x < xLength; x++) {
			maxNumberLength = max(maxNumberLength, (int)ceil(log10(map[y][x] + 0.1)));
		}
	}


	for (int y = 0; y < yLength; y++) {
		for (int x = 0; x < xLength; x++) {
			for (int i = 0, length = maxNumberLength - (int)ceil(log10(map[y][x]+0.1)); i < length; i++) {
				printf(" ");
			}
			printf("%d ", map[y][x]);
		}
		printf("\n");
	}

	return 0;
}