#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define nl '\n'
#define sp ' '

using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;

const int P = 500005;
const int N = 1000000;
const int B = 10000;

bool block[B+5];
int lo = 1;
int hi = B;

ll pw[P];
vector<ll> prime;

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0); 
	#ifdef DBG
	freopen("in.txt", "r", stdin); 
	#endif

	for(int i = 2; i <= B; i++) {
		if(block[i])
			continue;
		prime.push_back(i);
		pw[prime.size()-1] = 1;

		for(int j = 2*i; j <= B; j += i) {
			++pw[prime.size()-1];
			block[j] = 1;
		}
	}
	
	while(hi < N) {
		lo += B;
		hi += B;
		memset(block, 0, sizeof block);

		for(int i = 0; i < prime.size(); i++) {
			while(prime[i] * (pw[i] + 1) <= hi) {
				++pw[i];
				block[prime[i] * pw[i] - lo + 1] = 1;
			}
		}

		for(int i = 1; i <= B; i++)
			if(!block[i]) {
				prime.push_back(lo + i - 1);
				pw[prime.size()-1] = 1;
			}
	}

	cout<<prime.back()<<nl;

	return 0;
}
