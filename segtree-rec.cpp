#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define nl '\n'
#define sp ' '

using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>; 

const int N = 200000;
int val[N];
int tree[4*N+5];

void build(int v, int tl, int tr) {
	if(tl == tr)
		tree[v] = val[tl];
	else {
		int tm = (tl+tr)/2;
		build(2*v, tl, tm);
		build(2*v+1, tm+1, tr);
		tree[v] = tree[2*v] + tree[2*v+1];
	}
}

void update(int v, int tl, int tr, int p, int x) {
	if(tl == tr)
		tree[v] = x;
	else {
		int tm = (tl+tr)/2;
		if(p <= tm)
			update(2*v, tl, tm, p, x);
		else
			update(2*v+1, tm+1, tr, p, x);
		tree[v] = tree[2*v] + tree[2*v+1];
	}
}

int query(int v, int tl, int tr, int l, int r) {
	if(l > r)
		return 0;
	if(tl == l && tr == r)
		return tree[v];
	int tm = (tl+tr)/2;
	return query(2*v, tl, tm, l, min(r, tm)) + query(2*v+1, tm+1, tr, max(l, tm+1), r);
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0); 
	#ifdef DBG
	freopen("in.txt", "r", stdin); 
	#endif

	int n,q;
	cin>>n>>q;
	for(int i = 1; i <= n; i++)
		cin>>val[i];
	build(1, 1, n);

	while(q--) {
		int t,a,b;
		cin>>t>>a>>b;
		if(t == 1)
			update(1, 1, n, a, b);
		else 
			cout<<query(1, 1, n, a, b)<<nl;
	}

	return 0;
}
