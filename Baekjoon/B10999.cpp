#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

using ll = long long;

class SegTree {
public:
	vector<ll>* nodes;
	vector<ll>* lazies;

	int leafStart;
	int end;
	int nodeSize;

	SegTree(int size) {
		int h = (int)ceil(log2(size));
		leafStart = (int)pow(2, h);
		end = leafStart - 1;
		nodeSize = leafStart * 2;

		nodes = new vector<ll>(nodeSize, 0);
		lazies = new vector<ll>(nodeSize, 0);
	}

	void insert(int index, ll value) {
		int curr = leafStart + index;
		while (curr > 0) {
			(*nodes)[curr] += value;
			curr /= 2;
		}
	}

	void update(int left, int right, ll value) {
		update(1, 0, end,
			left, right, value);
	}

	void update(int index, int start, int end,
		int left, int right, ll value) {

		lazyUpdate(index, start, end);

		if (right < start || end < left) return;
		if (left <= start && end <= right) {
			ll diff = (end - start + 1) * value;
			(*nodes)[index] += diff;
			if (start != end) {
				(*lazies)[index * 2] += value;
				(*lazies)[index * 2 + 1] += value;
			}
			return;
		}

		int mid = start + (end - start) / 2;
		update(index * 2,	  start,   mid, left, right, value);
		update(index * 2 + 1, mid + 1, end, left, right, value);
		(*nodes)[index] = (*nodes)[index * 2] + (*nodes)[index * 2 + 1];
	}

	void lazyUpdate(int index, int start, int end) {
		if ((*lazies)[index]) {
			ll lazy = (*lazies)[index];
			(*nodes)[index] += (end - start + 1) * lazy;
			if (start != end) {
				(*lazies)[index * 2] += lazy;
				(*lazies)[index * 2 + 1] += lazy;
			}
			(*lazies)[index] = 0;
		}
	}


	ll select(int left, int right) {
		return select(1, 0, end,
			left, right);
	}

	ll select(int index, int start, int end,
		int left, int right) {

		lazyUpdate(index, start, end);

		if (right < start || end < left) return 0;
		if (left <= start && end <= right) {
			return (*nodes)[index];
		}

		int mid = start + (end - start) / 2;
		ll lSum = select(index * 2, start, mid, left, right);
		ll rSum = select(index * 2 + 1, mid + 1, end, left, right);

		return lSum + rSum;
	}

};

int main(void) {
	//freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int numNumber, numQuery, _;

	cin >> numNumber >> numQuery >> _;
	numQuery += _;

	SegTree tree(numNumber);

	for (int i = 0; i < numNumber; i++) {
		ll value;
		cin >> value;
		tree.insert(i, value);
	}

	for (int q = 0; q < numQuery; q++) {
		int command;
		cin >> command;

		if (command == 1) {
			// update query
			int left, right;
			ll value;
			cin >> left >> right >> value;
			tree.update(left - 1, right - 1, value);
		}
		else {
			//select query
			int left, right;
			cin >> left >> right;
			printf("%lld\n", tree.select(left - 1, right - 1));
		}
	}

	return 0;
}
