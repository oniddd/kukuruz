// Floyd Warshall's algorithm
//
// Calculates APSP (all-pairs shortest path) on a weighted graph.
//
// Variables:
// - G is the adjecency matrix of the graph.
// - N is the number of vertices of the graph.
// - MAX is the maximum numbers of vertices (needs to be configurated).
// 
// Note: G[i][j] represents the shortest path from vertex i to vertex j.
// If G[i][j] = inf then vertex j is unreachable from vertex i.

// Ne dozvoljava negativne cikluse

#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define nl '\n'
#define sp ' '

using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;

ll G[505][505];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); 
	#ifdef DBG
	freopen("in.txt", "r", stdin); 
	#endif

	int n,m,q;
	cin>>n>>m>>q;

	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			G[i][j] = i == j ? 0 : 1e18;

	for(int i = 0; i < m; i++) {
		ll a,b,c;
		cin>>a>>b>>c;
		G[a][b] = c;
	}

	for(int k = 1; k <= n; k++)
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				if(G[i][k] < 1e18 && G[j][k] < 1e18)
					G[i][j] = min(G[i][j], G[i][k] + G[k][j]);

	return 0;
}
