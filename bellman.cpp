#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define nl '\n'
#define sp ' '

using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;

int n,m;
vector<tuple<int,int,int>> E;
vector<int> d, p; // parent

// prepoznavanje negativnog ciklusa:
// ako prodjemo n-ti put i ako se neke udaljenosti smanje (negativni ciklus)

void bellman_ford(int s) {
	fill(all(d), 1e9+7);
	d[s] = 0;
	for(int i = 0; i < n-1; i++)
		for(const auto& [u,v,w] : E)
			d[v] = min(d[u], d[v]+w);
}

void bellman_ford_faster(int s) {
	fill(all(d), 1e9+7);
	d[s] = 0;
	bool ch = 1;
	while(ch) {
		ch = 0;
		for(const auto& [u,v,w] : E) {
			if(d[u] + w < d[v]) {
				p[v] = u;
				d[v] = d[u] + w;
				ch = 1;
			}
		}
	}
}

void negative_cycle(int s) {
	fill(all(d), 1e9+7);
	d[s] = 0;

	int x = -1; // vrh u kojem smo zadnje updateali vrijednost
	for(int i = 0; i < n; i++) {
		x = -1; // zanima me samo u n-toj iteraciji
		for(const auto& [u,v,w] : E) {
			if(d[u] + w < d[v]) {
				p[v] = u;
				d[v] = d[u] + w;
				x = v;
			}
		}
	}

	if(x == -1) {
		cout<<"no negative cycle"<<nl;
		return;
	}

	// x moze biti u ciklusu ili dostupan iz ciklusa
	// ako se vracamo gore n puta zavrsit cemo u ciklusu
	for(int i = 0; i < n; i++)
		x = p[x];
	
	// x je u ciklusu... idemo unazad dok se ne vratimo u x
	vector<int> cycle {x};
	for(int cur = p[x]; cur != x; x = p[x])
		cycle.push_back(cur);
	reverse(all(cycle));
	
	// radi s ciklusom
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); 
	#ifdef DBG
	freopen("in.txt", "r", stdin); 
	#endif

	return 0;
}
