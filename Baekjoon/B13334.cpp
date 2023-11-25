#include <iostream>
#include <vector>
#include <algorithm>
#include <map>;

using namespace std;

struct Line {
	int left, right;
};

bool compare(Line a, Line b) {
	return a.right < b.right;
}


void printLine(vector<Line> lines) {
	for (Line l : lines) {
		printf("%d, %d\n", l.left, l.right);
	}
}

int main(void) {
	//freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int numLine;
	cin >> numLine;

	vector<Line> inputs;
	vector<Line> lines;

	for (int i = 0; i < numLine; i++) {
		int left, right;
		cin >> left >> right;
		if (left > right) swap(left, right);
		inputs.push_back({ left, right });
	}
	vector<int> rights;
	map<int, int> leftCount;

	int maxLength;
	cin >> maxLength;

	for (Line l: inputs) {
		int length = l.right - l.left;
		if (length <= maxLength) {
			lines.push_back(l);
			leftCount.insert({ l.left, 0 });
		}
	}

	numLine = lines.size();

	sort(lines.begin(), lines.end(), compare);

	for (Line l : lines) {
		rights.push_back(l.right);
		leftCount.find(l.left)->second++;
	}

	int result = 0;
	int leftIndex = 0;
	int rightIndex = 0;
	for (auto target = leftCount.begin(); target != leftCount.end(); target++) {
		int left = target->first;
		int right = left + maxLength;

		while (rightIndex < numLine && rights[rightIndex] <= right) rightIndex++;
		int length = rightIndex - leftIndex;
		result = max(length, result);

		leftIndex += target->second;
	}
	printf("%d", result);

	return 0;
}
