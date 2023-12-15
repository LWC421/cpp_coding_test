#include <iostream>
#include <vector>
#include <algorithm>
#define V vector

using namespace std;


int main(void) {
	//freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int TEST_CASE;
	cin >> TEST_CASE;
	
	for (int test_case = 0; test_case < TEST_CASE; test_case++) {
		string commands;
		cin >> commands;

		int numNumber;
		cin >> numNumber;

		V<int> numbers(numNumber);
		char tmp;
		cin >> tmp;
		for (int i = 0; i < numNumber; i++) {
			cin >> numbers[i];
			cin >> tmp;
		}
		if (numNumber == 0) {
			cin >> tmp;
		}

		//input finished

		int left = 0;
		int right = numNumber - 1;
		bool reversed = false;
		bool error = false;
		for (char command : commands) {
			if (command == 'R') {
				// Reverse
				reversed = !reversed;
			}
			else {
				// Delete
				if (left > right) {
					error = true;
					printf("error\n");
					break;
				}
				if (reversed) {
					right--;
				}
				else {
					left++;
				}
			}
		}

		if (error) continue;
		
		printf("[");
		if (left <= right) {
			if (!reversed) {
				for (int i = left; i < right; i++) {
					printf("%d,", numbers[i]);
				}
				printf("%d", numbers[right]);
			}
			else {
				for (int i = right; i > left; i--) {
					printf("%d,", numbers[i]);
				}
				printf("%d", numbers[left]);
			}
		}
		printf("]\n");

	}

	return 0;
}