#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Coord {
	int number, x, y;
};

bool xyCompare(Coord a, Coord b) {
	if (a.y != b.y) return a.y < b.y;
	return a.x < b.x;
}


int CCW(Coord a, Coord b, Coord c) {
	int forward = a.x * b.y + b.x * c.y + c.x * a.y;
	int backward = b.x * a.y + c.x * b.y + a.x * c.y;
	return forward - backward;
}

Coord base;

int distance(Coord from, Coord to) {
	int diffX = from.x - to.x;
	int diffY = from.y - to.y;

	return diffX * diffX + diffY * diffY;
}

bool ccwCompare(Coord a, Coord b) {
	int ccw = CCW(base, a, b);
	if (ccw == 0) {
		int aDistance = distance(base, a);
		int bDistance = distance(base, b);
		return aDistance < bDistance;
	}
	return ccw > 0;
}

int main(void) {
	//freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	
	int numCase;
	cin >> numCase;
	while (numCase-- > 0) {
		// start each test case

		int numCoord;
		cin >> numCoord;
		vector<Coord> coords;
		for (int i = 0; i < numCoord; i++) {
			int x, y;
			cin >> x >> y;
			coords.push_back({ i, x, y });
		}

		sort(coords.begin(), coords.end(), xyCompare);

		base = coords[0];
		sort(coords.begin() + 1, coords.end(), ccwCompare);

		int last = numCoord - 1;
		int prev = numCoord - 1;
		
		int count = 0;
		while (CCW(base, coords[last], coords[prev]) == 0) {
			count++;
			last--;
		}

		reverse(coords.end() - count, coords.end());


		for (Coord c : coords) {
			printf("%d ", c.number);
		}
		printf("\n");
	}
}