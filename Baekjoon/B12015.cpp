#include <iostream>
#include <vector>
#include <algorithm>

#define V vector

using namespace std;

int numNumber;
V<int> numbers;
V<int> lis;

int main(void) {
	//freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> numNumber;
	numbers.resize(numNumber);
	for (int i = 0; i < numNumber; i++) {
		cin >> numbers[i];
	}
	//input finished

	for (int num : numbers) {
		if (lis.empty() || lis.back() < num) {
			lis.push_back(num);
		}
		else {
			auto position = lower_bound(lis.begin(), lis.end(), num);
			*position = num;
		}
	}

	cout << lis.size();

		
	return 0;
}