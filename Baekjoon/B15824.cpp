#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;
#define vl vector<ll>

const ll MOD = 1000000007;

int main(void) {
	//freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int numNumber;
	cin >> numNumber;

	vl inputs(numNumber);
	for (int i = 0; i < numNumber; i++) {
		cin >> inputs[i];
		inputs[i] = inputs[i];
	}

	vl mults(numNumber);
	mults[0] = 1;
	for (int i = 1; i < numNumber; i++) {
		mults[i] = (mults[i - 1] * 2) % MOD;
	}

	sort(inputs.begin(), inputs.end());

	ll result = 0;

	vl lValues(numNumber, 0);
	vl rValues(numNumber, 0);
	
	for (int i = 0; i < numNumber; i++) {
		int left = i;
		int right = numNumber - i - 1;
		ll lValue = inputs[i] * (mults[left] - 1);
		ll rValue = inputs[i] * (mults[right] - 1);
		lValues[i] = lValue;
		rValues[i] = rValue;
	}

	ll lValueSum = 0;
	for(ll value: lValues){
		lValueSum = (lValueSum + value) % MOD;
	}
	ll rValueSum = 0;
	for (ll value : rValues) {
		rValueSum = (rValueSum + value) % MOD;
	}

	printf("%lld\n", (MOD + lValueSum - rValueSum) % MOD);


	return 0;
}