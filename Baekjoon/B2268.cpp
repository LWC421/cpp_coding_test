#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

using ll = long long;

class SegTree {
public:
	vector<ll> nodes;
	int leafStart;
	int end;
	int nodeSize;

	SegTree(int size) {
		int h = (int)ceil(log2(size));
		leafStart = (int)pow(2, h);
		end = leafStart - 1;
		nodeSize = leafStart * 2;

		nodes.resize(nodeSize, 0);
	}

	void update(int index, ll value) {
		int curr = leafStart + index;
		nodes[curr] = value;
		curr /= 2;
		while (curr > 0) {
			nodes[curr] = nodes[curr*2] + nodes[curr*2+1];
			curr /= 2;
		}
	}

	ll select(int left, int right) {
		return selectQuery(1, 0, end, left, right);
	}

	ll selectQuery(int index, int start, int end, int left, int right) {
		if (right < start || end < left) return 0;
		if (left <= start && end <= right) return nodes[index];

		int mid = start + (end - start) / 2;
		ll lSum = selectQuery(index * 2,   start, mid, left, right);
		ll rSum = selectQuery(index * 2+1, mid+1, end, left, right);
		return lSum + rSum;
	}
};

int main(void) {
	//freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int numNumber, numQuery;
	cin >> numNumber >> numQuery;

	SegTree tree(numNumber);

	for (int q = 0; q < numQuery; q++) {
		int command;
		cin >> command;
		if (command == 0) {
			// select query
			int left, right;
			cin >> left >> right;
			if (left > right) swap(left, right);
			printf("%lld\n", tree.select(left-1, right-1));
		}
		else {
			// update query
			int index;
			ll value;
			cin >> index >> value;
			tree.update(index - 1, value);
		}
	}

	return 0;
}