#include <bits/stdc++.h>

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b

using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;

// Fenwick Tree
struct fwt {
    int n;
    vi ft;
    fwt(int n) : n(n), ft(n + 1) {}
    void update(int i, int v) {
        for (; i <= n; i += i & -i) ft[i] += v;
    }
    int query(int i) {
        int sum = 0;
        for (; i; i -= i & -i) sum += ft[i];
        return sum;
    }
    int query(int i, int j) {
        return query(j) - query(i - 1);
    }
};