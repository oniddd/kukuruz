#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define nl '\n'
#define sp ' '

using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;

vector<int> G[100005], GT[100005], topo;
int comp[100005];
bool vis[100005];

/*
	1. topoloski sortirati raf
	2. pokreni dfs na transponiranom grafu tim slijedom
*/

void dfs1(int u) {
	vis[u] = 1;
	for(int v : G[u])
		if(!vis[v])
			dfs1(v);
	topo.push_back(u);
}

void dfs2(int u, int c) {
	vis[u] = 1;
	comp[u] = c;
	for(int v : GT[u])
		if(!vis[v])
			dfs2(v, c);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); 
	#ifdef DBG
	freopen("in.txt", "r", stdin); 
	#endif

	int n,m;
	cin>>n>>m;

	for(int i = 0; i < m; i++) {
		int a,b;
		cin>>a>>b;
		G[a].push_back(b);
		GT[b].push_back(a);
	}

	for(int i = 1; i <= n; i++)
		if(!vis[i])
			dfs1(i);
	reverse(all(topo));

	memset(vis, 0, sizeof vis);
	int cnt = 0;
	for(int u : topo)
		if(!vis[u]) {
			++cnt;
			dfs2(u, cnt);
		}

	cout<<cnt<<nl;
	for(int i = 1; i <= n; i++)
		cout<<comp[i]<<sp;

	return 0;
}
