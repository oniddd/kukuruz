#define INF 0x3f3f3f3f

vector<vector<pair<int,int>>> adj;
vector<int> dist(6, INF);
vector<int> prev(6, -1);
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

int src = 1;
dist[src] = 0;
pq.push({0,src});

while (!pq.empty()) {
	auto [d, u] = pq.top();
	pq.pop();

	if(d > dist[u])
		continue;

	for (auto [v, w] : adj[u]) {
		if (dist[v] > dist[u] + w) {
			dist[v] = dist[u] + w;
			prev[v] = u;
			pq.push({dist[v], v}); 
		}
	}
}