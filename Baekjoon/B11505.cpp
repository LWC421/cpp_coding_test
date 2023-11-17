#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int MOD = 1000000007;

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
			nodes[curr] = (nodes[curr * 2] * nodes[curr * 2 + 1]) % MOD;
			curr /= 2;
		}
	}

	ll select(int left, int right) {
		return selectQuery(1, 0, end, left, right);
	}

	ll selectQuery(int index, int start, int end, int left, int right) {
		if (right < start || end < left) return 1;
		if (left <= start && end <= right) return nodes[index];

		int mid = start + (end - start) / 2;
		ll lMult = selectQuery(index * 2, start, mid, left, right);
		ll rMult = selectQuery(index * 2 + 1, mid + 1, end, left, right);
		return (lMult * rMult) % MOD;
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
		tree.update(i, value);
	}

	for (int q = 0; q < numQuery; q++) {
		int command;
		cin >> command;
		if (command == 1) {
			int index;
			ll value;
			cin >> index >> value;
			tree.update(index-1, value);
		}
		else {
			int left, right;
			cin >> left >> right;
			printf("%d\n", tree.select(left-1, right-1));
		}
	}
	
	return 0;
}