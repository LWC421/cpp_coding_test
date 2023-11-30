#include <iostream>
#include <vector>
#include <queue>

#define V vector
#define PQ priority_queue

using namespace std;

struct Node { int index, value, version; };

struct Compare {
	bool operator()(Node a, Node b) {
		if (a.value != b.value) return a.value > b.value;
		return a.index > b.index;
	}
};

PQ<Node, vector<Node>, Compare> pq;
V<int> versions;


int main(void) {
	//freopen("input.txt", "r", stdin);
	
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int numNumber;
	cin >> numNumber;

	versions.resize(numNumber + 1, 0);
	for (int i = 1; i <= numNumber; i++) {
		int value;
		cin >> value;
		pq.push({ i, value, 0 });
	}

	int numQuery;
	cin >> numQuery;
	while (numQuery-- > 0) {
		int command;
		cin >> command;

		if (command == 1) {
			int index, value;
			cin >> index >> value;
			pq.push({ index, value, ++versions[index] });
		}
		else if (command == 2) {
			while (versions[pq.top().index] != pq.top().version) pq.pop();

			printf("%d\n", pq.top().index);
		}
	}

	return 0;
}
