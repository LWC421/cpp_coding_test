#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#define vi vector<int>

class SegTree {
public:
	vi nodes;
	vi lazies;
	int leafStart;
	int end;
	int nodeSize;

	SegTree(int size);

	void init(vi inputs);

	void update(int left, int right, int value);
	void updateQuery(int index, int start, int end, int left, int right, int value);

	void updateLazy(int index, int start, int end);

	int select(int left, int right);
	int select(int index, int start, int end, int left, int right);

	void print();

};

const int UPDATE = 1;
const int SELECT = 2;

int main(void) {
	//freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int numNumber;
	cin >> numNumber;

	vi inputs(numNumber);

	for (int i = 0; i < numNumber; i++) {
		cin >> inputs[i];
	}

	SegTree tree(numNumber);
	tree.init(inputs);
	//tree.print();

	int numQuery;
	cin >> numQuery;

	for (int q = 0; q < numQuery; q++) {
		int command;
		cin >> command;
		if (command == UPDATE) {
			int left, right, value;
			cin >> left >> right >> value;
			tree.update(left, right, value);
			//tree.print();
		}
		else {
			int left, right;
			cin >> left >> right;
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
	lazies.resize(nodeSize, 0);
}

void SegTree::init(vi inputs) {
	for (int i = 0, length= inputs.size(); i < length; i++) {
		int index = leafStart + i;
		nodes[index] = inputs[i];
	}

	for (int i = leafStart - 1; i > 0; i--) {
		nodes[i] = nodes[i * 2] ^ nodes[i * 2 + 1];
	}
}

void SegTree::update(int left, int right, int value){
	updateQuery(1, 0, end, left, right, value);
}

void SegTree::updateQuery(int index, int start, int end, int left, int right, int value){
	updateLazy(index, start, end);

	int lIndex = index * 2;
	int rIndex = index * 2 + 1;

	if (right < start || end < left) return;
	if (left <= start && end <= right) {
		if (start != end) {
			lazies[lIndex] = lazies[lIndex] ^ value;
			lazies[rIndex] = lazies[rIndex] ^ value;
		}
		else {
			nodes[index] = nodes[index] ^ value;
		}
		return;
	}

	int mid = start + (end - start) / 2;
	updateQuery(lIndex, start, mid, left, right, value);
	updateQuery(rIndex, mid+1, end, left, right, value);
	nodes[index] = nodes[lIndex] ^ nodes[rIndex];
}

// just nodes updated when leaf node
void SegTree::updateLazy(int index, int start, int end) {
	if (lazies[index]) {
		if (start == end) nodes[index] = nodes[index] ^ lazies[index];
		else {
			lazies[index * 2] = lazies[index * 2] ^ lazies[index];
			lazies[index * 2+1] = lazies[index * 2+1] ^ lazies[index];
		}
		lazies[index] = 0;
	}
}

int SegTree::select(int left, int right){
	return select(1, 0, end, left, right);
}
int SegTree::select(int index, int start, int end, int left, int right){
	updateLazy(index, start, end);

	int lIndex = index * 2;
	int rIndex = index * 2 + 1;

	if (right < start || end < left) return 0;
	if (left <= start && end <= right) {
		return nodes[index];
	}

	int mid = start + (end - start) / 2;
	int lXOR = select(lIndex, start, mid, left, right);
	int rXOR = select(rIndex, mid + 1, end, left, right);

	return lXOR ^ rXOR;
}

void SegTree::print() {
	int length = 1;
	int index = 1;
	while (index < nodeSize) {
		for (int i = 0; i < length; i++) {
			printf("%d ", nodes[index++]);
		}
		printf("\n");

		length = length << 1;
	}
}