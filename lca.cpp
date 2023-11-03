/*
    OBRATI PAZNJU!
    - slobodno raspizdi MAX_LOG
    - slucaj da je b potomak od a
    - root mora biti parent sam sebe
*/
    

#include <bits/stdc++.h>
#define all(x) x.begin(), x.end();
#define nl '\n'
#define sp ' '

using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;

const int MAX = 2e5;
const int MAX_LOG = 20;
int depth[MAX], parent[MAX], bl[MAX][MAX_LOG];

void binary_lifting() {
    for(int i = 0; i < MAX; i++)
        bl[i][0] = parent[i];
    for(int pot = 1; pot < MAX_LOG; pot++)
        for(int i = 0; i < MAX; i++)
            bl[i][pot] = bl[bl[i][pot-1]][pot-1];
}

int lca(int a, int b) {
    if(depth[a] > depth[b])
        swap(a,b);
    int diff = depth[b] - depth[a];
    
    int pot = 0;
    while(diff > 0) {
        if(diff & 1)
            b = bl[b][pot];
        pot++;
        diff >>= 1;
    }

    if(a == b)
        return a;

    for(int pot = MAX_LOG - 1; pot >= 0; pot--) {
        if(bl[a][pot] == bl[b][pot])
            continue;
        a = bl[a][pot];
        b = bl[b][pot];
    }
    return parent[a];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    return 0;
}
