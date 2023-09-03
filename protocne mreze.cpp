#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define nl '\n'
#define sp ' '

using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;

// Edmonds–Karp algorithm (?)

ll R[500][500];
vector<int> G[500];
int p[500];
int n,m,s,t;

bool bfs() {
	queue<int> q;
	vector<bool> vis(n);
	q.push(s);
	vis[s] = 1;
	while(!q.empty()) {
		int x = q.front();
		q.pop();
		if(x == t)
			return 1;
		for(int y : G[x])
			if(!vis[y] && R[x][y] > 0) {
				vis[y] = 1;
				q.push(y);
				p[y] = x;
			}
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); 
	#ifdef DBG
	freopen("in.txt", "r", stdin); 
	#endif

	cin>>n>>m;
	s = 0, t = n-1;
	for(int i = 0; i < m; i++) {
		int a,b;
		ll c;
		cin>>a>>b>>c;
		--a; --b;
		G[a].push_back(b);
		G[b].push_back(a);
		R[a][b] += c;
	}

	ll sol = 0;
	while(bfs()) {
		ll aug = 1e9;
		// trazimo rezidualni kapacitet puta
		for(int x = t; x != s; x = p[x])
			aug = min(aug, R[p[x]][x]);
		// uvecavamo tok
		for(int x = t; x != s; x = p[x]) {
			R[p[x]][x] -= aug;
			R[x][p[x]] += aug;
		}
		sol += aug;
	}
	cout<<sol<<nl;

	return 0;
}