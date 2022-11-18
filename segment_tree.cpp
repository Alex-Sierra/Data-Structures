#include <bits/stdc++.h>
 
#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b
 
using namespace std;
typedef long long ll;
typedef vector<int> vi;

struct item {
    ll sum;
};

struct segtree {
    int size;
    vector<item> values;
    item neutral_element = {0};

    item merge(item a, item b) {
        return {
            a.sum + b.sum
        };
    }

    item single(int v) {
        return {
            v
        };
    }

    void init(int n) {
        size = 1;
        while (size < n) size *= 2;
        values.resize(2 * size);
    }

    void build(vector<int> &a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < (int) a.size()) {
                values[x] = single(a[lx]);
            }
            return;
        }
        int m = (lx + rx) >> 1;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        values[x] = merge(values[2 * x + 1], values[2 * x + 2]);
    }
    void build(vector<int> &a) {
        build(a, 0, 0, size);
    }
    
    void set(int i, int v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            values[x] = single(v);
            return;
        }
        int m = (lx + rx) >> 1;
        if (i < m) {
            set(i, v, 2 * x + 1, lx, m);
        } else {
            set(i, v, 2 * x + 2, m, rx);
        }
        values[x] = merge(values[2 * x + 1], values[2 * x + 2]);
    }
    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    item calc(int l, int r, int x, int lx, int rx) {
        if (lx >= r || l >= rx) return neutral_element;
        if (lx >= l && rx <= r) return values[x];
        int m = (lx + rx) / 2;
        item s1 = calc(l, r, 2 * x + 1, lx, m);
        item s2 = calc(l, r, 2 * x + 2, m, rx);
        return merge(s1, s2);
    }
    item calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }

    int find_kth(int k, int x, int lx, int rx) {
        if (rx - lx == 1) return lx;
        int m = (lx + rx) / 2;
        int sl = values[2 * x + 1].sum;
        if (k < sl) {
            return find_kth(k, 2 * x + 1, lx, m);
        } else {
            return find_kth(k - sl, 2 * x + 2, m, rx);
        }
    }
    int find_kth(int k) {
        return find_kth(k, 0, 0, size);
    }
};