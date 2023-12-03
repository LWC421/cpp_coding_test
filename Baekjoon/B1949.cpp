#include <iostream>
#include <vector>

using namespace std;

#define V vector

int numNode;
V<int> weights;
V<V<int>> edgess;
V<bool> visited;
V<V<int>> dp;


void dfs(int node) {
	visited[node] = true;

	dp[node][0] = 0;
	dp[node][1] = weights[node];

	for (int conn : edgess[node]) {
		if (visited[conn]) continue;
		dfs(conn);
		dp[node][0] += std::max(dp[conn][0], dp[conn][1]);
		dp[node][1] += dp[conn][0];
	}
}

int main(void) {
	//freopen("input.txt", "r", stdin);
	
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> numNode;
	weights.resize(numNode + 1);
	edgess.resize(numNode + 1);
	visited.resize(numNode + 1, false);
	dp.resize(numNode + 1, V<int>(2, 0));

	for (int i = 1; i <= numNode; i++) {
		cin >> weights[i];
	}

	for (int i = 1; i < numNode; i++) {
		int node1, node2;
		cin >> node1 >> node2;
		edgess[node1].push_back(node2);
		edgess[node2].push_back(node1);
	}

	dfs(1);

	printf("%d", std::max(dp[1][0], dp[1][1]));

	return 0;
}