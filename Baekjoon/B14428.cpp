#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const int UPDATE = 1;
const int SELECT = 2;

const int INF = (int)1e+9 + 1;

struct Data {
	int index, value;
};

class SegTree {
public:
	SegTree(int size);
	void update(int index, int value);
	int select(int left, int right);

private:
	vector<Data> nodes;
	int leafStart;
	int end;
	int nodeSize;

	Data select(int index, int start, int end, int left, int right);
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
			printf("%d\n", tree.select(left - 1, right - 1) + 1);
		}
	}


	return 0;
}

SegTree::SegTree(int size) {
	int h = (int)ceil(log2(size));
	this->leafStart = (int)pow(2, h);
	this->end = leafStart - 1;
	this->nodeSize = leafStart * 2;

	nodes.resize(nodeSize, { -1, INF });
}

void SegTree::update(int index, int value) {
	int curr = this->leafStart + index;
	nodes[curr] = { index, value };
	while ((curr /= 2) > 0) {
		Data left = nodes[curr * 2];
		Data right = nodes[curr * 2 + 1];
		if (right.value < left.value) nodes[curr] = { right.index, right.value };
		else nodes[curr] = { left.index, left.value };
	}

}

int SegTree::select(int left, int right) {
	return this->select(1, 0, this->end, left, right).index;
}

Data SegTree::select(int index, int start, int end, int left, int right) {
	if (end < left || right < start) return {-1, INF};
	if (left <= start && end <= right) return nodes[index];

	int mid = start + (end - start) / 2;
	Data lMin = this->select(index * 2,    start, mid, left, right);
	Data rMin = this->select(index * 2+1, mid+1, end, left, right);
	
	if (rMin.value < lMin.value) return rMin;
	return lMin;
}