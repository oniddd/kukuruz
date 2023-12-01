/*
    PAZNJA: RADI PROVJERU POSJECENOSTI NA OBA MJESTA!
*/
    

#include <bits/stdc++.h>

using namespace std;
using pii = pair<int,int>;

const int MAXN = 100100;
int n,m;
bool bio[MAXN];

set<pii> edges;
vector<pii> E[MAXN];

int mst() {
    int total = 0;

    edges.insert({0,1});

    while(!edges.empty()) {
        int cvor = (*edges.begin()).second;
        int dist = (*edges.begin()).first;
        edges.erase(edges.begin());

        if(bio[cvor])
            continue;

        bio[cvor] = 1;
        total += dist; 

        for(auto t : E[cvor]) {
            int ncvor = t.first;
            int ndist = t.second;
            if(bio[cvor])
                continue;
            edges.insert({ndist, ncvor});
        }
    }

    return total;
}

int main() {
    cin>>n>>m;
    for(int i = 0; i < m; i++) {
        int a,b,c;
        cin>>a>>b>>c;
        E[a].push_back({b,c});
        E[b].push_back({a,c});
    }

    cout<<mst()<<endl;

    return 0;
}
