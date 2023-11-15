#include <iostream>
#include <stack>

using namespace std;

struct Data {
	int value;
	int index;
};

int main(void) {
	//freopen("input.txt", "r", stdin);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int numNumber;

	cin >> numNumber;

	int* numbers = new int[numNumber];
	int* result = new int[numNumber];
	for (int i = 0; i < numNumber; i++) {
		cin >> numbers[i];
	}

	stack<Data> stack;

	for (int i = 0; i < numNumber; i++) {
		int target = numbers[i];
		if (stack.empty()) {
			stack.push({ target, i });
			continue;
		}
		while (!stack.empty() && stack.top().value < target) {
			Data d = stack.top();
			stack.pop();
			result[d.index] = target;
		}
		stack.push({ target, i });
	}

	while (!stack.empty()) {
		result[stack.top().index] = -1;
		stack.pop();
	}

	for (int i = 0; i < numNumber; i++) {
		cout << result[i] << " ";
	}

	return 0;
}