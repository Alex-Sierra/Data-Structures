#include <bits/stdc++.h>
 
#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b
 
using namespace std;
typedef long long ll;
typedef vector<int> vi;
 
struct dsu {
    vi p;
    void init(int n) {
        p = vi(n, -1);
    }
    int get(int x) {
        if (p[x] < 0)
            return x;
        return p[x] = get(p[x]);
    }
    void unite(int a, int b) {
        a = get(a);
        b = get(b);
        if (a != b) {
            if (p[a] > p[b])
                swap(a, b);
            p[a] += p[b];
            p[b] = a;
        }
    }
};

struct DSU {
    vi p, rank;
    DSU(int n) {
        p.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; i++) {
            p[i] = i;
            rank[i] = 0;
        }
    }
    int find(int x) {
        if (p[x] != x) {
            p[x] = find(p[x]);
        }
        return p[x];
    }
    void unite(int x, int y) {
        int xroot = find(x);
        int yroot = find(y);
        if (xroot == yroot) {
            return;
        }
        if (rank[xroot] < rank[yroot]) {
            p[xroot] = yroot;
        } else if (rank[xroot] > rank[yroot]) {
            p[yroot] = xroot;
        } else {
            p[yroot] = xroot;
            rank[xroot]++;
        }
    }
};