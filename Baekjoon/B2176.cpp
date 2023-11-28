#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define V vector
#define PQ priority_queue

int numNode, numEdge;

const int INF = 1000 * 10000 + 1;
const int INIT = -1;

struct Edge { int node, weight; };
struct Data { int node, weight; };

struct Compare {
	bool operator()(Data a, Data b) {
		return a.weight < b.weight;
	}
};

V<V<Edge>> edgess;
V<int> distances;
V<int> dp;

int search(int curr) {
	if (dp[curr] != INIT) return dp[curr];
	if (curr == 2) return 1;	//if finished

	int currDist = distances[curr];
	int result = 0;
	for (Edge conn : edgess[curr]) {
		if (currDist > distances[conn.node]) {
			result += search(conn.node);
		}
	}
	dp[curr] = result;

	return result;
}

int main(void) {
	//freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> numNode >> numEdge;

	edgess.resize(numNode + 1, V<Edge>(numNode + 1));
	distances.resize(numNode + 1, INF);
	dp.resize(numNode + 1, INIT);

	for (int i = 0; i < numEdge; i++) {
		int node1, node2, weight;
		cin >> node1 >> node2 >> weight;
		edgess[node1].push_back({ node2, weight });
		edgess[node2].push_back({ node1, weight });
	}
	// input finished

	// do dijkstra start with 2
	distances[2] = 0;
	PQ<Data, V<Data>, Compare> pq;
	pq.push({ 2, 0 });
	int nWeight;
	Data curr;
	while (!pq.empty()) {
		curr = pq.top(); pq.pop();
		if (curr.weight < distances[curr.node]) continue;

		for (Edge conn : edgess[curr.node]) {
			nWeight = curr.weight + conn.weight;
			if (nWeight < distances[conn.node]) {
				distances[conn.node] = nWeight;
				pq.push({ conn.node, nWeight });
			}
		}
	}
	

	//dijkstra finished

	printf("%d", search(1));

	return 0;
}
