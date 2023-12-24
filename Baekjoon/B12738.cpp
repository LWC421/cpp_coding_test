#include <iostream>
#include <vector>

#define V vector

using namespace std;

int main(void) {
	//freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int numNumber;
	cin >> numNumber;
	V<int> numbers(numNumber);
	for (int i = 0; i < numNumber; i++) {
		cin >> numbers[i];
	}
	//input finished

	V<int> lis;
	for (int i = 0; i < numNumber; i++) {
		if (lis.empty() || lis.back() < numbers[i]) {
			lis.push_back(numbers[i]);
		}
		else {
			auto t = lower_bound(lis.begin(), lis.end(), numbers[i]);
			*t = numbers[i];
		}
	}

	printf("%d", lis.size());

	return 0;
}