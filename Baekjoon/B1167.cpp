#include <iostream>
#include <vector>
#include <algorithm>
#define V vector

using namespace std;

struct Edge { int node, weight; };

int numNode;
V<V<Edge>> edgess;
V<bool> visited;

int maxDist;
int maxNode;

void dfs(int currNode, int dist) {
	visited[currNode] = true;

	if (dist > maxDist) {
		maxDist = dist;
		maxNode = currNode;
	}

	for (Edge e : edgess[currNode]) {
		if (visited[e.node]) continue;
		dfs(e.node, dist + e.weight);
	}
}

int main(void) {
	//freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> numNode;
	edgess.resize(numNode+1);
	visited.resize(numNode + 1, false);
	maxDist = -1;
	maxNode = 0;

	for (int i = 1; i <= numNode; i++) {
		int nodeNum;
		cin >> nodeNum;
		
		int node, weight;
		while (true) {
			cin >> node;
			if (node == -1) {
				break;
			}
			cin >> weight;
			edgess[nodeNum].push_back({ node, weight });
		}
	}
	//input finished

	//for (V<Edge> edges : edgess) {
	//	for (Edge e : edges) {
	//		printf("(%d, %d), ", e.node, e.weight);
	//	}
	//	printf("\n");
	//}

	dfs(1, 0);

	fill(visited.begin(), visited.end(), false);
	maxDist = -1;
	dfs(maxNode, 0);

	printf("%d", maxDist);

	return 0;
}