#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N = 200000;
int a[2*200005];

void update(int p, int v) {
	p += N;
	a[p] = v;

	for(; p > 0; p /=2)
		a[p/2] = max(a[p], a[p^1]);
}

int query(int l, int r) {
	int res = 0;
	l += N;
	r += N;

	while(l <= r) {
		if(l & 1)
			res = max(res, a[l++]);
		if(!(r & 1))
			res = max(res, a[r--]);

		l /= 2;
		r /= 2;
	}
}

// OR

#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define nl '\n'
#define sp ' '
 
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
 
const int N = (1 << 18);
ll T[2*N+1];
 
void build() {
    for(int i = N-1; i > 0; i--)
        T[i] = T[i*2] + T[i*2+1];
}
 
void update(int p, int v) {
    p += N;
    T[p] = v;
 
    for(; p > 0; p /= 2)
        T[p/2] = T[p] + T[p^1];
}
 
ll query(int l, int r) {
    ll res = 0;
    l += N;
    r += N;
 
    while(l <= r) {
        if(l & 1)
            res += T[l++];
        if(!(r & 1))
            res += T[r--];
        
        l /= 2;
        r /= 2;
    }
    return res;
}
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); 
	#ifdef DBG
	freopen("in.txt", "r", stdin); 
	#endif
 
    int n,q;
    cin>>n>>q;
 
    for(int i = 0; i < n; i++)
        cin>>T[N+i];
    build();
    
    while(q--) {
        ll t,a,b;
        cin>>t>>a>>b;
 
        if(t == 1)
            update(a-1, b);
        else
            cout<<query(a-1,b-1)<<nl;
    }
 
	return 0;
}
