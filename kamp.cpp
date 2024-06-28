#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define nl '\n'
#define sp ' '

using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;

const int MAXN = 1e5+5;
const int MAXM = 15;

ll grid[MAXN][MAXM], ogrid[MAXN][MAXM];
int n,k;
int len[MAXN];

// broj ogranaka
int dfs(int i, ll sum, ll target) {
    if(i == n)
        return 1;
    
    int ans = 0;
    int lo = 0;
    int hi = len[i+1]-1;
    while(lo < hi) {
        int mid = (lo+hi+1)/2;
        if(sum + grid[i+1][mid] <= target)
            lo = mid;
        else
            hi = mid-1;
    }
    if(sum + grid[i+1][lo] <= target)
        for(int k = 0; k <= lo; k++)
            ans += dfs(i+1, sum + grid[i+1][k], target);
    else
        return 0;
    return ans;
}

ll dfs2(int i, int j, ll sum, ll target, vector<int> tracer) {
    if(i == n-1) {
        for(int x : tracer)
            cout<<x<<"-";
        cout<<ogrid[i][j]<<nl;
        return ogrid[i][j];
    }
    
    ll ans = 0;
    int lo = 0;
    int hi = len[i+1]-1;
    while(lo < hi) {
        int mid = (lo+hi+1)/2;
        if(sum + grid[i+1][mid] <= target)
            lo = mid;
        else
            hi = mid-1;
    }
    if(sum + grid[i+1][lo] <= target) {
        tracer.push_back(ogrid[i][j]);
        for(int k = 0; k <= lo; k++)
            ans += ogrid[i][j] + dfs2(i+1, k, sum + grid[i+1][k], target, tracer);
        tracer.pop_back();
    } else
        return 0;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); 

    freopen("in.txt", "r", stdin);    
    cin>>n>>k;
    for(int i = 0; i < n; i++) {
        int l;
        cin>>l;
        len[i] = l;
        for(int j = 0; j < l; j++) {
            cin>>grid[i][j];
            ogrid[i][j] = grid[i][j];
        }
    }

    ll sum = 0;
    for(int i = 0; i < n; i++) {
        sum += grid[i][0];
        for(int j = len[i]-1; j >= 0; j--)
            grid[i][j] -= grid[i][0];
    }

    ll lo = sum;
    ll hi = 1e18;
    while(lo < hi) {
        ll mid = (lo+hi)/2;
        if(dfs(-1, sum, mid) >= k)
            hi = mid;
        else
            lo = mid+1;
    }

    cout<<lo<<nl;
    cout<<dfs(-1, sum, lo)<<nl;
    ll ans = 0;
    for(int i = 0; i < len[0]; i++) {
        ans += dfs2(0, i, sum + grid[0][i], lo, {});
    }
    cout<<ans<<nl;
    /*    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < len[i]; j++)
            cout<<grid[i][j]<<sp;
        cout<<nl;
    }
    cout<<dfs(-1,sum, 100000)<<nl;
    */
    return 0;
}
