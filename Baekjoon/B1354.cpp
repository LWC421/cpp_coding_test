#include <iostream>
#include <unordered_map>

using namespace std;
using ll = long long;

unordered_map<ll, ll> dp;


ll query(ll N, ll P, ll Q, ll X, ll Y) {
	if (N <= 0) return 1;

	if (dp[N]) return dp[N];

	ll leftN  = (N / P) - X;
	ll rightN = (N / Q) - Y;
	ll left = query(leftN, P, Q, X, Y);
	ll right = query(rightN, P, Q, X, Y);

	ll sum = left + right;
	dp[N] = sum;

	return sum;
}

int main(void) {
	 //freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	
	ll N, P, Q, X, Y;
	cin >> N >> P >> Q >> X >> Y;
	

	printf("%lld", query(N, P, Q, X, Y));

	return 0;
}
