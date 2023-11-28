#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

using ll = long long;


#define V vector


struct Data { int nerd, pos; };
struct Node { ll sum;  int count; };
bool compare(Data a, Data b) {
	return a.nerd < b.nerd;
}

class SegTree {
public:
	V<Node> nodes;
	int leafStart;
	int end;
	int nodeSize;

	SegTree(int size);

	Node query(int left, int right);
	Node query(int index, int start, int end, int left, int right);

	void insert(int pos);
};

int main(void) {
	//freopen("input.txt", "r", stdin);
	
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int numNode;
	cin >> numNode;

	V<Data> inputs;
	for (int _ = 0; _ < numNode; _++) {
		int nerd, pos;
		cin >> nerd >> pos;
		inputs.push_back({nerd, pos});
	}
	// input finished

	// sort by nerd
	sort(inputs.begin(), inputs.end(), compare);

	int maxPos = -1;
	for (Data d : inputs) {
		maxPos = std::max(maxPos, d.pos);
	}

	SegTree tree(maxPos+1);

	ll result = 0;
	for (Data input : inputs) {
		Node left = tree.query(0, input.pos - 1);
		ll lSum = ((ll)left.count * input.pos) - left.sum;

		Node right = tree.query(input.pos + 1, maxPos);
		ll rSum = right.sum - ((ll)right.count * input.pos);

		result += (lSum + rSum) * (ll)input.nerd;

		tree.insert(input.pos);
	}
	printf("%lld", result);

	return 0;
}

SegTree::SegTree(int size) {
	int h = (int)ceil(log2(size));
	leafStart = (int)pow(2, h);
	end = leafStart - 1;
	nodeSize = leafStart * 2;

	nodes.resize(nodeSize, {0, 0});
}

Node SegTree::query(int left, int right) {
	if (left > right) return {0, 0};

	return query(1, 0, end, left, right);
}
Node SegTree::query(int index, int start, int end, int left, int right) {
	if (right < start || end < left) return { 0, 0 };
	if (left <= start && end <= right) return nodes[index];

	int mid = start + (end - start) / 2;
	Node lNode = query(index * 2, start, mid, left, right);
	Node rNode = query(index * 2 + 1, mid+1, end, left, right);
	
	return { lNode.sum + rNode.sum, lNode.count + rNode.count };
}

void SegTree::insert(int pos) {
	int curr = leafStart + pos;

	while (curr > 0) {
		nodes[curr].count++;
		nodes[curr].sum += pos;

		curr /= 2;
	}
}