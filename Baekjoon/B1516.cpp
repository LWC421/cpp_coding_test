#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

vector<int> times;

bool compare(int a, int b) {
	return times[a] < times[b];
}

struct Data {
	int node, acc;
};

struct pqCompare {
	bool operator()(Data a, Data b){
		return a.acc > b.acc;
	}
};

int main(void) {
	 //freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int numNode;
	cin >> numNode;

	vector<int> indegres(numNode+1, 0);
	times.resize(numNode + 1);
	vector<vector<int>> edgess(numNode + 1, vector<int>());

	for (int i = 1; i <= numNode; i++) {
		cin >> times[i];
		int value;
		cin >> value;
		while (value != -1) {
			indegres[i]++;
			edgess[value].push_back(i);
			cin >> value;
		}
	}
	// input finished

	for (vector<int> edges : edgess) {
		sort(edges.begin(), edges.end(), compare);
	}

	priority_queue<Data, vector<Data>, pqCompare> q;
	for (int i = 1; i <= numNode; i++) {
		if (indegres[i] == 0) q.push({ i, times[i]});
	}

	vector<int> results(numNode + 1);
	while (!q.empty()) {
		Data curr = q.top(); q.pop();
		results[curr.node] = curr.acc;

		for (int connected : edgess[curr.node]) {
			indegres[connected]--;
			if (indegres[connected] == 0) {
				q.push({ connected, curr.acc + times[connected]});
			}
		}
	}

	for (int i = 1; i <= numNode; i++) {
		printf("%d\n", results[i]);
	}

	return 0;
}
