#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int INF = 1000000000 + 1;

const int UPDATE = 1;
const int SELECTT = 2;

class SegTree {
public:
	vector<int> nodes;
	int leafStart;
	int end;
	int nodeSize;

	SegTree(int size);
	void update(int index, int value);
	int select(int left, int right);
	int select(int index, int start, int end, int left, int right);
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
		tree.update(i, value);
	}

	int numQuery;
	cin >> numQuery;

	for (int q = 0; q < numQuery; q++) {
		int command;
		cin >> command;
		if (command == UPDATE) {
			int index, value;
			cin >> index >> value;
			tree.update(index - 1, value);
		}
		else {
			int left, right;
			cin >> left >> right;
			printf("%d\n", tree.select(left - 1, right - 1));
		}
	}


	return 0;
}


SegTree::SegTree(int size) {
	int h = (int)ceil(log2(size));
	leafStart = (int)pow(2, h);
	end = leafStart - 1;
	nodeSize = leafStart * 2;
	nodes.resize(nodeSize, INF);
}

void SegTree::update(int index, int value) {
	int curr = leafStart + index;
	nodes[curr] = value;
	while ( (curr /=2) > 0) nodes[curr] = min(nodes[curr * 2], nodes[curr * 2 + 1]);
}

int SegTree::select(int left, int right) {
	return this->select(1, 0, this->end, left, right);
}

int SegTree::select(int index, int start, int end, int left, int right) {
	if ( right < start || end < left) return INF;
	if (left <= start && end <= right) return nodes[index];

	int mid = start + (end - start) / 2;
	int lMin = this->select(index * 2,   start, mid, left, right);
	int rMin = this->select(index * 2+1, mid+1, end, left, right);
	return min(lMin, rMin);
}
