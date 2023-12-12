#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define V vector
#define PQ priority_queue

using ll = long long;

struct Target {
	int weight;
	ll value;
};

struct WeightCompare {
	bool operator()(const Target& a, const Target& b) const {
		return a.weight > b.weight;
	}
};

struct ValueCompare {
	bool operator()(const ll a, const ll b) const {
		return a < b;
	}
};

bool Compare(const int a, const int b) {
	return a < b;
}

int main(void) {
	//freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int numTarget, numBag;
	cin >> numTarget >> numBag;

	PQ<Target, V<Target>, WeightCompare> inputs;

	for (int i = 0; i < numTarget; i++) {
		int weight;
		ll value;
		cin >> weight >> value;
		inputs.push({ weight, value });
	}

	V<int> weights(numBag);
	for (int i = 0; i < numBag; i++) {
		cin >> weights[i];
	}
	//input finished

	// sort weights asc
	sort(weights.begin(), weights.end(), Compare);

	PQ<ll, V<ll>, ValueCompare> values;
	
	ll result = 0;
	for (int weight : weights) {
		while (!inputs.empty() && inputs.top().weight <= weight) {
			values.push(inputs.top().value); inputs.pop();
		}

		if (values.empty()) continue;
		
		result += values.top(); values.pop();
	}

	printf("%lld", result);


	return 0;
}