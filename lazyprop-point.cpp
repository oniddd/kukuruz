#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define nl '\n'
#define sp ' '

#define int ll

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
		tree[v] = 0;
	}
}

void range_update(int v, int tl, int tr, int l, int r, int delta) {
	if(l > r)
		return;
	if(tl == l && tr == r)
		tree[v] += delta;
	else {
		int tm = (tl+tr)/2;
		range_update(2*v, tl, tm, l, min(tm, r), delta);
		range_update(2*v+1, tm+1, tr, max(tm+1, l), r, delta);
	}
}

int point_query(int v, int tl, int tr, int p) {
	if(tl == tr)
		return tree[v];
	int tm = (tl+tr)/2;
	if(p <= tm)
		return tree[v] + point_query(2*v, tl, tm, p);
	else
		return tree[v] + point_query(2*v+1, tm+1, tr, p);
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
		int t;
		cin>>t;
		if(t == 1) {
			int a,b,c;
			cin>>a>>b>>c;
			range_update(1, 1, n, a, b, c);
		} else {
			int a;
			cin>>a;
			cout<<point_query(1, 1, n, a)<<nl;
		}
	}

	return 0;
}
