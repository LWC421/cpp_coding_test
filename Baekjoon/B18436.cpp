#include <iostream>
#include <vector>
#include <cmath>

#define V vector

using namespace std;

struct EvenOdd { int even, odd; };

class SegTree {
public:
	V<EvenOdd> nodes;
	int leafStart;
	int end;
	int nodeSize;

	SegTree(int size);
	void update(int index, int value);
	EvenOdd query(int left, int right);
	EvenOdd query(int index, int start, int end, int left, int right);
};

int main(void) {
	//freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int numNumber;
	cin >> numNumber;

	V<int> inputs(numNumber);
	for (int i = 0; i < numNumber; i++) {
		cin >> inputs[i];
	}
	SegTree tree(numNumber);

	for (int i = 0; i < numNumber; i++) {
		tree.update(i, inputs[i]);
	}

	int numQuery;
	cin >> numQuery;
	while (numQuery-- > 0) {
		int command;
		cin >> command;
		if (command == 1) {
			int index, value;
			cin >> index >> value;
			tree.update(index - 1, value);
		}
		else {
			int left, right;
			cin >> left >> right;
			EvenOdd result = tree.query(left - 1, right - 1);
			if (command == 2) {
				printf("%d\n", result.even);
			}
			else {
				printf("%d\n", result.odd);
			}
		}
	}

	return 0;
}

SegTree::SegTree(int size) {
	int h = (int)ceil(log2(size));
	leafStart = (1 << h);
	end = leafStart - 1;
	nodeSize = leafStart << 1;

	nodes.resize(nodeSize, { 0, 0 });
}
void SegTree::update(int index, int value){
	int curr = leafStart + index;
	EvenOdd origin = { nodes[curr].even, nodes[curr].odd };
	EvenOdd changed = { ~value & 1, value & 1};

	while (curr > 0) {
		nodes[curr].even += changed.even - origin.even;
		nodes[curr].odd += changed.odd - origin.odd;
		curr /= 2;
	}
}

EvenOdd SegTree::query(int left, int right){
	return query(1, 0, end, left, right);
}

EvenOdd SegTree::query(int index, int start, int end, int left, int right){
	if (right < start || end < left) return { 0, 0 };
	if (left <= start && end <= right) return nodes[index];

	int mid = start + (end - start) / 2;
	EvenOdd lValue = query(index * 2, start, mid, left, right);
	EvenOdd rValue = query(index * 2+1, mid+1, end, left, right);
	return { lValue.even + rValue.even, lValue.odd + rValue.odd };
}