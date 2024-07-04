  multiset<int> a,b;

void balance() {
	if(b.size() > a.size()) {
		int x = *b.begin();
		b.erase(b.begin());
		a.insert(x);
	} else if(b.size() + 1 < a.size()) {
		int x = *a.rbegin();
		a.erase(--a.end());
		b.insert(x);
	}
}

void add(int x) {
	if(a.size() && x <= *a.rbegin())
		a.insert(x);
	else
		b.insert(x);
	balance();
}

void remove(int x) {
	if(a.count(x))
		a.erase(a.lower_bound(x));
	else
		b.erase(b.lower_bound(x));
	balance();
}

int median() {
	return *a.rbegin();
}
