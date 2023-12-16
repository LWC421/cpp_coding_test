#include <iostream>
#include <vector>
#include <queue>

#define V vector

using namespace std;

using ll = long long;

const ll INF = 10000ll * 1000000ll + 1;

struct Edge {
	int node;
	ll weight;
};

struct Data {
	int node;
	ll weight;
	int zero;
};
struct DataCompare {
	bool operator()(const Data& a, const Data& b) const {
		return a.weight > b.weight;
	}
};

int main(void) {
	//freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int numNode, numEdge, numZero;
	cin >> numNode >> numEdge >> numZero;

	V<V<Edge>> edgess(numNode+1);

	while (numEdge-- > 0) {
		int node1, node2;
		ll weight;
		cin >> node1 >> node2 >> weight;
		edgess[node1].push_back({ node2, weight });
		edgess[node2].push_back({ node1, weight });
	}
	//input finished

	V<V<ll>> distancess(numNode + 1, V<ll>(numZero + 1, INF));
	priority_queue<Data, V<Data>, DataCompare> pq;
	pq.push({ 1, 0ll, numZero });
	for (int i = 0; i <= numZero; i++) {
		distancess[1][i] = 0;
	}

	while (!pq.empty()) {
		Data curr = pq.top(); pq.pop();
		bool disable = false;
		for (int i = curr.zero; i <= numZero; i++) {
			if (curr.weight > distancess[curr.node][i]) {
				disable = true;
				break;
			}
		}

		if (disable) continue;

		for (Edge e : edgess[curr.node]) {
			ll nWegith = curr.weight + e.weight;
			if (nWegith < distancess[e.node][curr.zero]) {
				distancess[e.node][curr.zero] = nWegith;
				pq.push({ e.node, nWegith, curr.zero });
			}
			int nZero = curr.zero - 1;
			if (nZero >= 0) {
				if (curr.weight < distancess[e.node][nZero]) {
					distancess[e.node][nZero] = curr.weight;
					pq.push({ e.node, curr.weight, nZero });
				}
			}
		}
	}

	ll min = INF;
	for (ll dist : distancess[numNode]) {
		min = std::min(min, dist);
	}
	printf("%lld", min);
		
	return 0;
}