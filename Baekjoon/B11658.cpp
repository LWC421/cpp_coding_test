#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

using ll = long long;

class SegTree {
public:
	vector<vector<ll>>* nodes;
	int leafStart;
	int end;
	int nodeSize;


	SegTree(int size) {
		int h = (int)ceil(log2(size));
		leafStart = (int)pow(2, h);
		end = leafStart - 1;
		nodeSize = leafStart * 2;
		nodes = new vector<vector<ll>>(nodeSize, vector<ll>(nodeSize, 0));
	}


	void update(long value, int y, int x) {
		y = leafStart + y;
		x = leafStart + x;

		ll diff = value - (*nodes)[y][x];

		while ( y > 0) {
			int currX = x;
			while ( currX > 0) {
				(*nodes)[y][currX] += diff;
				currX /= 2;
			}
			y /= 2;
		}
	}


	ll query(int left, int top, int right, int bottom) {
		int yIndex = 1;
		int yStart = 0;
		int yEnd = end;

		return yQuery(yIndex, yStart, yEnd, top, bottom, left, right);
	}

	ll yQuery(int yIndex, int yStart, int yEnd,
		int top, int bottom,
		int left, int right) {

		if (yEnd < top || bottom < yStart) return 0;
		if (top <= yStart && yEnd <= bottom) {
			return xQuery(yIndex, 1, 0, end, left, right);
		}

		int mid = yStart + (yEnd - yStart) / 2;
		ll topSum = yQuery(yIndex * 2, yStart, mid, top, bottom, left, right);
		ll bottomSum = yQuery(yIndex * 2 + 1, mid + 1, yEnd, top, bottom, left, right);
		return topSum + bottomSum;
	}

	ll xQuery(int yIndex, int xIndex,
		int xStart, int xEnd,
		int left, int right) {

		if (xEnd < left || right < xStart) return 0;
		if (left <= xStart && xEnd <= right) return (*nodes)[yIndex][xIndex];

		int mid = xStart + (xEnd - xStart) / 2;
		ll leftSum = xQuery(yIndex, xIndex * 2, xStart, mid, left, right);
		ll rightSum = xQuery(yIndex, xIndex * 2 + 1, mid + 1, xEnd, left, right);

		return leftSum + rightSum;
	}

	void print() {
		for (vector<ll> row :*nodes) {
			for (ll v : row) {
				cout << v << " ";
			}
			printf("\n");
		}
	}
};





int main(void) {
	//freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int mapLength, numQuery;

	cin >> mapLength >> numQuery;


	SegTree tree(mapLength);

	for (int y = 0; y < mapLength; y++) {
		for (int x = 0; x < mapLength; x++) {
			long value;
			cin >> value;
			tree.update(value, y, x);
		}
	}

	//tree.print();

	while (numQuery-- > 0) {
		int command;
		cin >> command;
		if (command == 0) {
			//change
			int x, y;
			ll value;
			cin >> y >> x >> value;
			tree.update(value, y - 1, x - 1);
		}
		else {
			//query
			int left, top, right, bottom;
			//cin >> left >> top >> right >> bottom;
			cin >>  top >> left >> bottom >> right;
			cout << tree.query(left - 1, top - 1, right - 1, bottom - 1) << "\n";
		}
	}

	return 0;
}
