#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const int UPDATE = 0;
const int SELECT = 1;

class SegTree {
public:
	vector<int> nodes;
	vector<bool> lazies;

	int leafStart;
	int end;
	int nodeSize;

	SegTree(int size);
	void update(int left, int right);
	void update(int index, int start, int end, int left, int right);
	int select(int left, int right);
	int select(int index, int start, int end, int left, int right);
	void updateLazy(int index, int start, int end);
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
		int command, left, right;
		cin >> command >> left >> right;

		if (command == UPDATE) {
			tree.update(left, right);
		}
		else {
			printf("%d\n", tree.select(left, right));
		}
	}


	return 0;
}

SegTree::SegTree(int size) {
	int h = (int)ceil(log2(size));
	leafStart = (int)pow(2, h);
	end = leafStart - 1;
	nodeSize = leafStart * 2;

	nodes.resize(nodeSize, 0);
	lazies.resize(nodeSize, false);
}

void SegTree::update(int left, int right){
	update(1, 0, end, left, right);
}

void SegTree::update(int index, int start, int end, int left, int right) {
	updateLazy(index, start, end);

	if (end < left || right < start) return;
	if (left <= start && end <= right) {
		int length = end - start + 1;
		nodes[index] = abs(nodes[index] - length);
		if (start != end) {
			lazies[index * 2] = !lazies[index * 2];
			lazies[index * 2 + 1] = !lazies[index * 2 + 1];
		}
		return;
	}

	int mid = start + (end - start) / 2;
	update(index * 2,   start, mid, left, right);
	update(index * 2+1, mid+1, end, left, right);
	nodes[index] = nodes[index * 2] + nodes[index * 2 + 1];
}

int SegTree::select(int left, int right) {
	return select(1, 0, end, left, right);
}

int SegTree::select(int index, int start, int end, int left, int right) {
	updateLazy(index, start, end);

	if (end < left || right < start) return 0;
	if (left <= start && end <= right) {
		return nodes[index];
	}

	int mid = start + (end - start) / 2;
	int lSum = select(index * 2,     start, mid, left, right);
	int rSum = select(index * 2 + 1, mid+1, end, left, right);
	return lSum + rSum;
}

void SegTree::updateLazy(int index, int start, int end) {
	if (lazies[index]) {
		int length = end - start + 1;
		nodes[index] = abs(nodes[index] - length);
		if (start != end) {
			lazies[index * 2] = !lazies[index * 2];
			lazies[index * 2 + 1] = !lazies[index * 2 + 1];
		}
		lazies[index] = false;
	}
}