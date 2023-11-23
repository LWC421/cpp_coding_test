#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge {
	int node, weight;
};

struct MinMax {
	int min, max;
};

int numNode;

vector<int> depths;
vector<vector<Edge>> edgess;
vector<vector<int>> parentss;
vector<vector<int>> minss;
vector<vector<int>> maxss;

void process();
MinMax query(int node1, int node2);

const int INF = 1e+6 + 1;

int main(void) {
	//freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	
	numNode;
	cin >> numNode;

	edgess.resize(numNode + 1);
	depths.resize(numNode + 1);
	parentss.resize(numNode + 1, vector<int>(18, 0));
	minss.resize(numNode + 1, vector<int>(18, INF));
	maxss.resize(numNode + 1, vector<int>(18, 0));

	for (int i = 1; i < numNode; i++) {
		int node1, node2, weight;
		cin >> node1 >> node2 >> weight;
		edgess[node1].push_back({ node2, weight });
		edgess[node2].push_back({ node1, weight });
	}


	process();

	int numQuery;
	cin >> numQuery;
	for (int i = 0; i < numQuery; i++) {
		int from, to;
		cin >> from >> to;
		MinMax result = query(from, to);
		printf("%d %d\n", result.min, result.max);
	}

	
	
	return 0;
}

void process() {
	vector<bool> visited(numNode + 1, false);
	visited[1] = true;
	int depth = 1;
	queue<int> q;
	q.push(1);

	while (!q.empty()) {
		int size = q.size();
		for (int i = 0; i < size; i++) {
			int curr = q.front(); q.pop();
			depths[curr] = depth;

			for (Edge e : edgess[curr]) {
				if (visited[e.node]) continue;
				visited[e.node] = true;
				q.push(e.node);
				parentss[e.node][0] = curr;
				maxss[e.node][0] = e.weight;
				minss[e.node][0] = e.weight;
			}
		}
		depth++;
	}
	for (int p = 1; p < 18; p++) {
		for (int n = 1; n <= numNode; n++) {
			int parent = parentss[n][p - 1];
			parentss[n][p] = parentss[parent][p - 1];
			maxss[n][p] = max(maxss[parent][p - 1], maxss[n][p - 1]);
			minss[n][p] = min(minss[parent][p - 1], minss[n][p - 1]);
		}
	}

	//for (vector<int> row : parentss) {
	//	for (int v : row) {
	//		printf("%d, ", v);
	//	}
	//	printf("\n");
	//}
}

MinMax query(int node1, int node2) {
	if (depths[node1] > depths[node2]) {
		int tmp = node1;
		node1 = node2;
		node2 = tmp;
	}

	// node1's depths is always smaller then node2's depth


	MinMax result = { INF, 0 };
	int i = 17;
	int diff = 0;
	while ( (diff = depths[node2] - depths[node1]) > 0) {
		if ( (1 << i) & diff ) {
			result.min = min(minss[node2][i], result.min);
			result.max = max(maxss[node2][i], result.max);
			node2 = parentss[node2][i];
		}
		i--;
	}


	if (node1 == node2) return result;

	i = 17;
	while (parentss[node1][0] != parentss[node2][0]) {
		if (parentss[node1][i] != parentss[node2][i]) {
			result.min = min(minss[node1][i], result.min);
			result.max = max(maxss[node1][i], result.max);
			node1 = parentss[node1][i];

			result.min = min(minss[node2][i], result.min);
			result.max = max(maxss[node2][i], result.max);
			node2 = parentss[node2][i];
		}
		i--;
	}

	result.min = min(minss[node1][0], result.min);
	result.max = max(maxss[node1][0], result.max);

	result.min = min(minss[node2][0], result.min);
	result.max = max(maxss[node2][0], result.max);

	return result;
}