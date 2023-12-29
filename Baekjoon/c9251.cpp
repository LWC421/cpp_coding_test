#include <iostream>
#include <vector>

#define V vector

using namespace std;

int main(void) {
	//freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	V<char> str1;
	V<char> str2;
	str1.push_back('\n');
	str2.push_back('\n');
	
	string str;
	cin >> str;

	for (char c : str) {
		str1.push_back(c);
	}
	cin >> str;
	for (char c : str) {
		str2.push_back(c);
	}
	//input finished

	V<V<int>> dp(str1.size(), V<int>(str2.size()));

	for (int y = 1; y < str1.size(); y++) {
		for (int x = 1; x < str2.size(); x++) {
			if (str1[y] == str2[x]) {
				dp[y][x] = dp[y - 1][x - 1] + 1;
			}
			else {
				dp[y][x] = std::max(dp[y - 1][x], dp[y][x - 1]);
			}
		}
	}

	printf("%d", dp[str1.size()-1][str2.size()-1]);


	return 0;
}