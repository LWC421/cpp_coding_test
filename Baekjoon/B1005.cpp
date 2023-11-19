#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Data{
	int node, weight;
};

#define vi vector<int>
#define vD vector<Data>
#define vvD vector<vector<Data>>

bool compare(Data a, Data b) {
	return a.weight < b.weight;
}

struct comparator {
	bool operator()(Data a, Data b) {
		return a.weight > b.weight;
	}
};

int main(void) {
	//freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int TEST_CASE;
	cin >> TEST_CASE;
	while (TEST_CASE-- > 0) {
		int numNode;
		int numEdge;
		cin >> numNode >> numEdge;
		vi times(numNode+1);
		for (int i = 1; i <= numNode; i++) {
			cin >> times[i];
		}
		
		vi indegrees(numNode + 1, 0);
		vvD edges(numNode+1, vD(0));
		while (numEdge-- > 0) {
			int from, to;
			cin >> from >> to;
			indegrees[to]++;
			edges[from].push_back({ to, times[to] });

		}

		// each connection edge sort by weight asc (biggest weight is last index);
		for (vD v : edges) {
			sort(v.begin(), v.end(), compare);
		}
		int dest;
		cin >> dest;

		vD starts;
		for (int i = 1; i <= numNode; i++) {
			if (indegrees[i] == 0) {
				//if target node is start node;
				starts.push_back({ i, times[i] });
			}
		}
		sort(starts.begin(), starts.end(), compare);

		priority_queue<Data, vector<Data>, comparator> pq;
		for (Data d : starts) {
			pq.push(d);
		}

		bool isContinue = true;
		while (!pq.empty() && isContinue) {
			Data current = pq.top(); pq.pop();
			if (current.node == dest) {
				//if finished
				printf("%d\n", current.weight);
				isContinue = false;
			}
			for (Data d : edges[current.node]) {
				// connected edge
				indegrees[d.node]--;
				if (indegrees[d.node] == 0) {
					// if target node is creatable
					pq.push({ d.node, current.weight + d.weight });
				}
			}
		}
	}


	return 0;
}