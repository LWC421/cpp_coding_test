#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>
#include <map>;

using namespace std;

using ll = long long;

class SegTree {
public:
	vector<int> nodes;
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

	void insert(int index) {
		int curr = leafStart + index;
		while (curr > 0) {
			nodes[curr] += 1;
			curr /= 2;
		}
	}

	int select(int left, int right) {
		return selectQuery(1, 0, end, left, right);
	}

	int selectQuery(int index, int start, int end, int left, int right) {
		if (right < start || end < left) return 0;
		if (left <= start && end <= right) return nodes[index];

		int mid = start + (end - start) / 2;
		int lSum = selectQuery(index * 2,   start, mid, left, right);
		int rSum = selectQuery(index * 2+1, mid+1, end, left, right);
		return lSum + rSum;
	}
};

int main(void) {
	//freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	set<int> valueSet;
	
	int numNumber;
	cin >> numNumber;


	vector<int> inputs(numNumber);
	for (int i = 0; i < numNumber; i++) {
		int value;
		cin >> value;
		valueSet.insert(value);
		inputs[i] = value;
	}

	// Value Compress
	map<int, int> valueToIndex;
	int index = 0;
	for (auto v = valueSet.begin(); v != valueSet.end(); v++) {
		valueToIndex.insert({*v, index++});
	}
	for (int i = 0; i < numNumber; i++) {
		inputs[i] = (*valueToIndex.find(inputs[i])).second;
	}

	int size = valueSet.size();
	SegTree tree(size);

	for (int i = 0; i < numNumber; i++) {
		printf("%d\n", tree.select(inputs[i], size-1) + 1);
		tree.insert(inputs[i]);
	}
	

	return 0;
}