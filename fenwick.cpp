template <typename T>
struct Fenwick {
private:
    vector<T> BIT;
    T query_internal(T x) {
        T sum = 0;
        for(; x > 0; x -= x & -x)
            sum += BIT[x];
        return sum;
    }
public:
    Fenwick(T n) : BIT(n+1, 0) {}

    void construct() {
        for(int i = 1; i <= n; i++) {
			int r = i + (i & -i);
			if(r <= n)
				BIT[r] += BIT[i];
		}
	}

    void update(T x, T delta) {
        for(; x <= n; x += x & -x)
            BIT[x] += delta;
    }
    // b > a
    T query(T a, T b) {
        return query_internal(b) - query_internal(a-1);
    }
};
