#include <iostream>
#include <vector>
#define V vector

using namespace std;

const int EARLY = 0;
const int NORMAL = 1;
const int INF = 1000000 + 1;

int numNode;
V<V<int>> edgess;
V<bool> visited;
V<V<int>> dp;

void dfs(int node) {
	visited[node] = true;
	dp[node][EARLY] = 1;
	dp[node][NORMAL] = 0;
	
	for (int conn : edgess[node]) {
		if (visited[conn]) continue;
		dfs(conn);
		dp[node][NORMAL] += dp[conn][EARLY];
		dp[node][EARLY] += std::min(dp[conn][EARLY], dp[conn][NORMAL]);
	}
}

int main(void) {
	//freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> numNode;
	edgess.resize(numNode + 1);
	visited.resize(numNode + 1, false);
	dp.resize(numNode + 1, V<int>(2, INF));

	for (int i = 1; i < numNode; i++) {
		int node1, node2;
		cin >> node1 >> node2;
		edgess[node1].push_back(node2);
		edgess[node2].push_back(node1);
	}
	//input finished

	dfs(1);

	printf("%d", std::min(dp[1][EARLY], dp[1][NORMAL]));

	return 0;
}