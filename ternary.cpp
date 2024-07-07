int lo = 0;
int hi = x;
while(hi - lo >= 3) {
	int m1 = lo + (hi - lo) / 3;
	int m2 = hi - (hi - lo) / 3;
	if(f(m1, x) > f(m2, x))
		lo = m1;
	else if(f(m1, x) < f(m2, x))
		hi = m2;
	else {
		lo = m1;
		hi = m2;
	}
}
for(int i = lo; i <= hi; i++)
	// compute
