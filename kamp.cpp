#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define nl '\n'
#define sp ' '

using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;

int val[200005], byval[200005], mapping[200005], operation[500005];
pii edges[300005], interval[500005];
vector<pii> queries;
vector<int> G[500005];
bool removed[300005], additional[500005];
 
const int N = (1 << 18);
struct SegTree {
	ll T[2*N+1];
	void build() {
		for(int i = N-1; i > 0; i--)
			T[i] = max(T[i*2], T[i*2+1]);
	}
	void update(int p, int v) {
		p += N;
		T[p] = v;
		for(; p > 0; p /= 2)
			T[p/2] = max(T[p], T[p^1]);
	}
	ll query(int l, int r) {
		ll res = 0;
		l += N;
		r += N;
		while(l <= r) {
			if(l & 1)
				res = max(res, T[l++]);
			if(!(r & 1))
				res = max(res, T[r--]);
			l /= 2;
			r /= 2;
		}
		return res;
	}
};
struct UF
{
    vector<int> r, p, node;
    UF(int n) : r(n+1, 0), p(n+1, 0), node(n+1) {
        iota(p.begin(), p.end(), 0);
        iota(node.begin(), node.end(), 0);
    }
    int f(int x) {
        return (p[x] == x ? x : p[x] = f(p[x]));
    }
    void u(int i, int j) {
        int x = f(i), y = f(j);
        if (x == y)
            return;
        if (r[x] >= r[y]) {
            p[y] = x;
            if (r[x] == r[y])
                r[x]++;
        }
        else
            p[x] = y;
    }
};

int tick = 0;
void dfs(int u, int p) {
	if(G[u].empty()) {
		interval[u] = {tick, tick};
		mapping[u] = tick;
		++tick;
		return;
	}
	int l = 1e9;
	int r = -1e9;
	for(int v : G[u])
		if(v != p) {
			dfs(v, u);
			l = min(l, interval[v].first);
			r = max(r, interval[v].second);
		}
	interval[u] = {l, r};
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); 
	#ifdef DBG
	freopen("in.txt", "r", stdin); 
	#endif

	int n,m,q;
	cin>>n>>m>>q;
	int oq = q;

	for(int i = 1; i <= n; i++) {
		cin>>val[i];
		byval[val[i]] = i;
	}
	for(int i = 1; i <= m; i++) {
		int a,b;
		cin>>a>>b;
		edges[i] = {a,b};
	}
	queries.resize(q);
	for(int i = 0; i < q; i++) {
		int a,b;
		cin>>a>>b;
		queries[i] = {a,b};
		if(a == 2)
			removed[b] = 1;
	}

	for(int i = 1; i <= m; i++)
		if(!removed[i]) {
			queries.emplace_back(2, i);
			++q;
		}

	auto uf = UF(2*n+5);
	int nodecnt = n;
	for(int i = q-1; i >= 0; i--) {
		auto [t, x] = queries[i];
		if(t == 1)
			continue;
		
		++nodecnt;
		auto [a, b] = edges[x];
		int c = uf.node[uf.f(a)];
		int d = uf.node[uf.f(b)];
		uf.u(a,b);
		uf.node[uf.f(a)] = nodecnt;
		operation[i] = nodecnt;

		if(i >= oq)
			additional[nodecnt] = 1;

		G[nodecnt].push_back(c);
		if(c != d)
			G[nodecnt].push_back(d);
	}

	unordered_set<int> nodes;
	for(int i = 1; i <= n; i++)
		nodes.insert(uf.node[uf.f(i)]);

	for(int u : nodes)
		dfs(u, -1);

	auto st = SegTree();	
	for(int i = 1; i <= n; i++) {
		int j = interval[i].first;
		st.T[N+j] = val[i];
	}
	st.build();

	/*
	for(int i = 1; i <= nodecnt; i++) {
		cout<<i<<": ["<<interval[i].first<<sp<<interval[i].second<<"]"<<nl;
	}
	vector<bool> vis(n+1);
	queue<int> qu;
	for(int x : nodes)
		qu.push(x);
	while(!qu.empty()) {
		int u = qu.front();
		qu.pop();
		vis[u] = 1;
		for(int v : G[u])
			if(!vis[v]) {
				cout<<u<<sp<<v<<nl;
				qu.push(v);
			}
	}
	
	cout<<endl;
	*/

	for(int i = 0; i < oq; i++) {
		auto [t, x] = queries[i];
		if(t == 1) {
			x = mapping[x];
			for(auto u : nodes) {
				auto [l, r] = interval[u];
				if(x >= l && x <= r) {
					int ans = st.query(l, r);
					if(ans)
						st.update(mapping[byval[ans]], 0);
					cout<<ans<<nl;
					break;
				}
			}
		} else {
			int node = operation[i];
			nodes.erase(node);
			for(int v : G[node]) {
				nodes.insert(v);		
			}
			/*
			vector<int> newnodes;
			for(int u : nodes) {
				if(G[u].empty() || additional[u]) {
					newnodes.push_back(u);
					continue;
				}
				for(int v : G[u])
					newnodes.push_back(v);
			}
			nodes = newnodes;
			*/
		}
	}
	return 0;
}
