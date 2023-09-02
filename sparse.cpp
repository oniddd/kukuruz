#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define nl '\n'
#define sp ' '

using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;

const int N = 2000000;
const int P = 17;

int sparse[P+1][N+1];
auto func = [](int a, int b){ return min(a, b); };

void build() {
	for(int p = 1; p <= P; p++)
		for(int i = 0; i + (1 << p) <= N; i++)
			sparse[p][i] = func(sparse[p-1][i], sparse[p-1][i+(1 << (p-1))]);
}

// for overlapping functions (min, max, gcd)
int query_ol(int a, int b) {
	int p = 31 - __builtin_clz(b-a+1);
	int k = 1 << p;
	return func(sparse[p][a], sparse[p][b-k+1]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); 
	#ifdef DBG
	freopen("in.txt", "r", stdin); 
	#endif

	int n,q;
	cin>>n>>q;

	for(int i = 0; i < n; i++)
		cin>>sparse[0][i];
	build();

	while(q--) {
		int a,b;
		cin>>a>>b;
		cout<<query_ol(--a,--b)<<nl;
	}

	return 0;
}