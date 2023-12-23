#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

#define V vector

using namespace std;

struct Edge {
	int node1;
	int node2;
	
	bool operator==(const Edge &a) const {
		return this->node1 == a.node1 && this->node2 == a.node2;
	}
};

int find(int x, V<int> &parents) {
	if (x == parents[x]) return x;

	return parents[x] = find(parents[x], parents);
}

int unionSet(int x, int y, V<int> &parents, V<int> &connects) {
	int n1, n2;
	n1 = find(x, parents);
	n2 = find(y, parents);

	if (n1 > n2) {
		swap(n1, n2);
	}
	
	// n1 is always samller or equal then n2;
	if (n1 == n2) {
		//already same set
		return connects[n1];
	}


	connects[n1] += connects[n2];
	parents[n2] = n1;

	return connects[n1];
}

int main(void) {
	//freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int TEST_CASE;
	cin >> TEST_CASE;

	for (int test_case = 0; test_case < TEST_CASE; test_case++) {
		// start test case
		int numEdge;
		cin >> numEdge;
		unordered_map<string, int> nameToIndex;
		V<Edge> edges(numEdge);

		int index = 0;

		for (int i = 0; i < numEdge; i++) {
			string node1, node2;
			cin >> node1 >> node2;

			if (nameToIndex.find(node1) == nameToIndex.end()) {
				//if do not inserted
				nameToIndex.insert({ node1, index++ });
			}
			if (nameToIndex.find(node2) == nameToIndex.end()) {
				//if do not inserted
				nameToIndex.insert({ node2, index++ });
			}

			int n1, n2;
			n1 = nameToIndex.find(node1)->second;
			n2 = nameToIndex.find(node2)->second;

			edges[i] = { n1, n2 };
		}
		//input finished

		V<int> parents(index);
		V<int> connects(index);

		for (int i = 0; i < index; i++) {
			parents[i] = i;
			connects[i] = 1;
		}

		for (Edge e : edges) {
			int result = unionSet(e.node1, e.node2, parents, connects);
			printf("%d\n", result);
		}
	}
		
	return 0;
}