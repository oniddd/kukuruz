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

int main() {

}