#include <iostream>
#include <vector>

#define V vector

using namespace std;

struct Query {
	int N;
	int X;
};

int main(void) {
	//freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int numNumber;
	cin >> numNumber;

	V<int> numbers(numNumber + 1);
	for (int i = 1; i <= numNumber; i++) {
		cin >> numbers[i];
	}

	int numQuery;
	cin >> numQuery;

	V<Query> queries(numQuery);
	for (int i = 0; i < numQuery; i++) {
		int n, x;
		cin >> n >> x;
		queries[i] = { n, x };
	}
	//input finished
	V<V<int>> table(numNumber + 1, V<int>(20));
	for (int i = 1; i <= numNumber; i++) {
		table[i][0] = numbers[i];
	}
	for (int d = 1; d < 20; d++) {
		for (int i = 1; i <= numNumber; i++) {
			table[i][d] = table[table[i][d - 1]][d - 1];
		}
	}
	
	for (Query q : queries) {
		int n = q.N;
		int x = q.X;
		for (int d = 19; d >= 0; d--) {
			if ( (n & (1 << d)) != 0) {
				x = table[x][d];
			}
		}
		printf("%d\n", x);
	}
	
		
	return 0;
}