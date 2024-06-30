#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define nl '\n'
#define sp ' '

using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;

int val[200005], byval[200005], depth[500005], mapping[200005];
pii edges[300005], interval[500005];
vector<pii> queries;
vector<int> G[500005];
bool removed[200005];

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
    UF(int n) : r(n+1, 0), p(n+1, 0), node(n+1)
    {
        iota(p.begin(), p.end(), 0);
        iota(node.begin(), node.end(), 0);
    }
    
    int f(int x)
    {
        return (p[x] == x ? x : p[x] = f(p[x]));
    }
    
    void u(int i, int j)
    {
        int x = f(i), y = f(j);
        if (x == y)
            return;

        if (r[x] >= r[y])
        {
            p[y] = x;
            if (r[x] == r[y])
                r[x]++;
        }
        else
            p[x] = y;
    }

    bool s(int i, int j)
    {
        return f(i) == f(j);
    }
};

int tick = 0;
void dfs(int u, int p, int d) {
	depth[u] = d;
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
			dfs(v, u, d+1);
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

		G[nodecnt].push_back(c);
		if(c != d)
			G[nodecnt].push_back(d);
	}
	/*
	for(int i = m; i > 0; i--) {
		++nodecnt;
		auto [a, b] = edges[i];
		int c = uf.node[uf.f(a)];
		int d = uf.node[uf.f(b)];
		uf.u(a,b);
		uf.node[uf.f(a)] = nodecnt;

		G[nodecnt].push_back(c);
		if(c != d)
			G[nodecnt].push_back(d);
	}
	*/

	unordered_set<int> snodes;
	for(int i = 1; i <= n; i++)
		snodes.insert(uf.node[uf.f(i)]);

	vector<int> nodes(all(snodes));

	int maxdepth = 0;
	for(int u : nodes) {
		dfs(u, -1, 1);
		maxdepth = max(maxdepth, depth[u]);
	}

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
	for(auto [t, x] : queries) {
		if(t == 1) {
			x = mapping[x];
			for(auto u : nodes) {
				auto [l, r] = interval[u];
				if(x >= l && x <= r) {
					int ans = st.query(l, r);
					st.update(mapping[byval[ans]], 0);
					cout<<ans<<nl;
					break;
				}
			}
		} else {
			vector<int> newnodes;
			for(int u : nodes) {
				if(depth[u] < maxdepth)
					for(int v : G[u])
						newnodes.push_back(v);
			}
			if(newnodes.empty()) {
				for(int u : nodes) {
					for(int v : G[u])
						newnodes.push_back(v);
				}
			}
			nodes = newnodes;
			for(int u : nodes)
				maxdepth = max(maxdepth, depth[u]);
		}
	}
	return 0;
}
