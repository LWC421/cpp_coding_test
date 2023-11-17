#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class SegTree {
public:
	vector<int> nodes;
	int leafStart;
	int end;
	int nodeSize;

	SegTree(int size);

	void insertQuery(int index);
	void deleteQuery(int index);
	int selectQuery(int target);

private:
	int selectQuery(int index, int start, int end, int left, int right);

};

int main(void) {
	//freopen("input.txt", "r", stdin);
	
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int TEST_CASE;
	cin >> TEST_CASE;

	for (int test_case = 0; test_case < TEST_CASE; test_case++) {
		// Start Test Case
		int numNumber, numQuery;
		cin >> numNumber >> numQuery;

		SegTree tree(numNumber + numQuery);
		for (int i = 0; i < numNumber; i++) {
			tree.insertQuery(i);
		}

		vector<int> targets(numNumber);
		for (int i = 0; i < numNumber; i++) {
			targets[i] = numNumber - i - 1;
		}

		int top = numNumber;
		int value;
		int target;
		for (int q = 0; q < numQuery; q++) {
			cin >> value;
			value--;
			target = targets[value];		//find position
			printf("%d ", tree.selectQuery(target + 1));	//upper query

			// Update Tree
			tree.deleteQuery(target);
			tree.insertQuery(top);
			targets[value] = top++;
		}
		printf("\n");
	}


	return 0;
}

SegTree::SegTree(int size) {
	int h = (int)ceil(log2(size));
	this->leafStart = (int)pow(2, h);
	this->end = leafStart - 1;
	this->nodeSize = leafStart * 2;
	this->nodes.resize(nodeSize, 0);
}

void SegTree::insertQuery(int index) {
	int curr = this->leafStart + index;
	while (curr > 0) {
		this->nodes[curr] += 1;
		curr /= 2;
	}
}

void SegTree::deleteQuery(int index) {
	int curr = this->leafStart + index;
	while (curr > 0) {
		this->nodes[curr] -= 1;
		curr /= 2;
	}
}

int SegTree::selectQuery(int target) {
	return this->selectQuery(1, 0, this->end, target, this->end);
}

int SegTree::selectQuery(int index, int start, int end, int left, int right) {
	if (end < left || right < start) return 0;
	if (left <= start && end <= right) return nodes[index];


	int mid = start + (end - start) / 2;
	int lSum = this->selectQuery(index * 2,   start, mid, left, right);
	int rSum = this->selectQuery(index * 2+1, mid+1, end, left, right);
	return lSum + rSum;
}

