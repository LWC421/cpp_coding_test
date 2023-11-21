#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

const int INF = 1000 * 100000 + 1;

struct Edge {
	int node, weight;
};

struct Data {
	int node, weight;
};

struct compare {
	bool operator()(Data a, Data b) {
		return a.weight > b.weight;
	}
};


#define vi vector<int>
#define ve vector<Edge>
#define vve vector<vector<Edge>>


int main(void) {
	//freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int numNode;
	int numEdge;


	cin >> numNode;
	cin >> numEdge;

	vve edges(numNode + 1, ve());

	for (int i = 0; i < numEdge; i++){
		int from, to, weight;
		cin >> from >> to >> weight;
		edges[from].push_back({ to, weight });
	}

	vi distances(numNode + 1, INF);

	int start, finish;
	cin >> start >> finish;

	distances[start] = 0;

	vi prevs(numNode + 1, -1);
	prevs[start] = start;

	priority_queue<Data, vector<Data>, compare> pq;
	pq.push({ start, 0 });

	Data curr;
	while (!pq.empty()) {
		curr = pq.top(); pq.pop();
		if (curr.node == finish) break;

		for (Edge e : edges[curr.node]) {
			int nWeight = curr.weight + e.weight;
			if (distances[e.node] > nWeight) {
				distances[e.node] = nWeight;
				pq.push({ e.node, nWeight });
				prevs[e.node] = curr.node;
			}
		}
	}

	printf("%d\n", distances[finish]);
	stack<int> stack;
	stack.push(finish);
	while (prevs[stack.top()] != stack.top()) {
		stack.push(prevs[stack.top()]);
	}

	printf("%d\n", stack.size());

	while (!stack.empty()) {
		printf("%d ", stack.top()); stack.pop();
	}

	return 0;
}