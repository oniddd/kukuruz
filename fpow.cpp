
int fpow(int p, int n, int mod) {
	if(n == 0) 
		return 1;
	if(n % 2 == 0)
		return fpow(p*p%mod, n/2, mod) % mod;
	return (p*fpow(p, n-1, mod)) % mod;
}