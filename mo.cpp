#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define nl '\n'
#define sp ' '

using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;

// max
int n;

struct Query {
	int l, r, idx;
	bool operator<(Query q) const {
		return pair{l / sqrt(MAX), r} < pair{q.l / sqrt(MAX), q.r};
	}
};

void add(int idx) {};
void remove(int idx) {};
ll get_answer() {
	return 0;
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); 
	#ifdef DBG
	freopen("in.txt", "r", stdin); 
	#endif

	vector<Query> queries;
	// ucitamo
	sort(all(queries));
	vector<ll> answers(queries.size());
	int l = 0, r = -1;
	for(auto q : queries) {
		while(l > q.l) {
			l--;
			add(l);
		}
		while(r < q.r) {
			r++;
			add(r);
		}
		while(l < q.l) {
			remove(l);
			l++;
		}
		while(r > q.r) {
			remove(r);
			r--;
		}
		answers[q.idx] = get_answer();
	}

	return 0;
}
