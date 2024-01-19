#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define nl '\n'
#define sp ' '

using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;

const int MIN = -1e9;
int dp[100][3][3][3][3];
int n;
string str;

inline int conv(char c) {
    switch(c) {
        case 'L':
            return 0;
        case 'I':
            return 1;
        default:
            return 2;
    }
}

int get(int p, int m, int f1, int f2) {
    if(p + m < n) {
        switch(str[p+m]) {
            case 'L':
                return 0;
            case 'I':
                return 1;
            default:
                return 2;
        }
    } 
    if(m == 1)
        return f1;
    if(m == 2)
        return f2;
    return 2;
}

int f(int i, int f1, int f2, int l1, int l2) {
    if(i == n)
        return 0;
    if(dp[i][f1][f2][l1][l2] != -1)
        return dp[i][f1][f2][l1][l2];

    if(str[i] == 'I') {
        if(l1 == 1 || get(i, 1, f1, f2) == 1)
            return MIN;
        return dp[i][f1][f2][l1][l2] = 1+f(i+1, i == 0 ? 1 : f1, i == 1 ? 1 : f2, 1, l1);
    } else if(str[i] == 'L') {
        if((l1 == 0 && l2 == 0) || (get(i, 1, f1, f2) == 0 && get(i, 2, f1, f2) == 0))
            return MIN;
        return dp[i][f1][f2][l1][l2] = f(i+1, i == 0 ? 0 : f1, i == 1 ? 0 : f2, 0, l1);
    }

    int ans = MIN;
    if(l1 != 1 && get(i, 1, f1, f2) != 1)
        ans = max(ans, 1+f(i+1, i == 0 ? 1 : f1, i == 1 ? 1 : f2, 1, l1));
    if(l1 != 0 && get(i, 1, f1, f2) != 0)
        ans = max(ans, f(i+1, i == 0 ? 0 : f1, i == 1 ? 0 : f2, 0, l1));
    if(!((l1 == 0 && l2 == 0) || (get(i, 1, f1, f2) == 0 && get(i, 2, f1, f2) == 0)))
        ans = max(ans, f(i+1, i == 0 ? 0 : f1, i == 1 ? 0 : f2, 0, l1));

    return dp[i][f1][f2][l1][l2] = ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); 
	#ifdef DBG
	freopen("in.txt", "r", stdin); 
	#endif

    cin>>n>>str;
    memset(dp, -1, sizeof dp);
    int ans = f(0, conv(str[n-1]), conv(str[n-2]), conv(str[n-1]), conv(str[n-2]));
    if(ans < 0)
        cout<<-1<<nl;
    else
        cout<<ans<<nl;

	return 0;
}