#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class SegTree {
public:	
	vector<int> *nodes;
	int leafStart;
	int end;
	int nodeSize;

	SegTree(int size) {
		int h = (int)ceil(log2(size));
		leafStart = (int)pow(2, h);
		end = leafStart - 1;
		nodeSize = leafStart * 2;

		nodes = new vector<int>[nodeSize];
	}

	void insert(int index, int value) {
		int curr = leafStart + index;

		while (curr > 0) {
			nodes[curr].push_back(value);
			curr /= 2;
		}
	}

	void sort() {
		for (int i = 0; i < leafStart; i++) {
			std::sort(nodes[i].begin(), nodes[i].end());
		}
	}

	int query(int index, int start, int end,
		int left, int right,
		int value) {

		if (end < left || right < start) return 0;
		if (left <= start && end <= right) {
			vector<int> *node = &nodes[index];
			int result = (*node).end() - upper_bound((*node).begin(), (*node).end(), value);
			return result;
		}

		int mid = start + (end - start) / 2;
		int leftSum = query(index * 2, start, mid, left, right, value);
		int rightSum = query(index * 2+1, mid+1, end, left, right, value);

		return leftSum + rightSum;
	}
};

int main(void) {
	//freopen("input.txt", "r", stdin);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int numNumber;
	cin >> numNumber;

	SegTree tree(numNumber);

	for (int i = 0; i < numNumber; i++) {
		int value;
		cin >> value;
		tree.insert(i, value);
	}

	tree.sort();

	int numQuery;
	cin >> numQuery;

	for (int i = 0; i < numQuery; i++) {
		int left, right, value;

		cin >> left >> right >> value;
		printf("%d\n", tree.query(1, 0, tree.end, left - 1, right - 1, value));
	}


	return 0;
}