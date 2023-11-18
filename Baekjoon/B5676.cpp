#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class SegTree {
public:
	vector<int> nodes;
	int leafStart;
	int end;
	int nodeSize;

	SegTree(int size);
	void update(int index, int value);
	char select(int left, int right);
	int select(int index, int start, int end, int left, int right);
};

int main(void) {
	//freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	while (true) {
		int numNumber, numQuery;
		cin >> numNumber;
		if (!cin) return 0;
		cin >> numQuery;

		SegTree tree(numNumber);

		for (int i = 0; i < numNumber; i++) {
			int value;
			cin >> value;
			if (value > 0) value = 1;
			else if (value < 0) value = -1;

			tree.update(i, value);
		}

		for (int q = 0; q < numQuery; q++) {
			char command;
			cin >> command;

			if (command == 'P') {
				// select query
				int left, right;
				cin >> left >> right;
				cout << tree.select(left - 1, right - 1);
			}
			else if(command == 'C'){
				// update query
				int index, value;
				cin >> index >> value;
				if (value > 0) value = 1;
				else if (value < 0) value = -1;
				tree.update(index-1, value);
			}
		}
		cout << '\n';
	}


	return 0;
}

SegTree::SegTree(int size) {
	int h = (int)ceil(log2(size));
	leafStart = (int)pow(2, h);
	end = leafStart - 1;
	nodeSize = leafStart * 2;

	nodes.resize(nodeSize, 1);
}

void SegTree::update(int index, int value) {
	int curr = leafStart + index;
	nodes[curr] = value;
	
	while ( (curr /= 2) > 0) nodes[curr] = nodes[curr * 2] * nodes[curr * 2 + 1];
}

char SegTree::select(int left, int right) {
	int result = select(1, 0, end, left, right);
	if (result > 0) return '+';
	if (result == 0) return '0';
	return '-';
}


int SegTree::select(int index, int start, int end, int left, int right) {
	if (right < start || end < left) return 1;
	if (left <= start && end <= right) return nodes[index];

	int mid = start + (end - start) / 2;
	int lMult = select(index * 2,   start, mid, left, right);
	int rMult = select(index * 2+1, mid+1, end, left, right);

	return lMult * rMult;
}