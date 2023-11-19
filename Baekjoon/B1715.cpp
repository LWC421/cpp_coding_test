#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct compare {
	bool operator()(int l, int r) {
		return l > r;
	}
};

int main(void) {
	//freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);


	auto comparator = [](int l, int r) {
		return l > r;
		};

	priority_queue<int, vector<int>, compare> pq;
	int numNumber;
	cin >> numNumber;
	for (int i = 0; i < numNumber; i++) {
		int value;
		cin >> value;
		pq.push(value);
	}

	int result = 0;
	while ( pq.size() > 1) {
		int l = pq.top();  pq.pop();
		int r = pq.top(); pq.pop();
		pq.push(l + r);
		result += l + r;
	}

	printf("%d", result);

	return 0;
}
