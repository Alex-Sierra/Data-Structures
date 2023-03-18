#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// Sparse Table
struct spt {
    int n;
    vector<vi> st;
    vi log2;
    spt(vi &a) {
        n = a.size();
        log2.assign(n + 1, 0);
        for (int i = 2; i <= n; i++)
            log2[i] = log2[i / 2] + 1;
        st.assign(n, vi(log2[n] + 1));
        for (int i = 0; i < n; i++)
            st[i][0] = a[i];
        for (int j = 1; j <= log2[n]; j++)
            for (int i = 0; i + (1 << j) <= n; i++)
                st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    }
    int query(int l, int r) {
        int j = log2[r - l + 1];
        return min(st[l][j], st[r - (1 << j) + 1][j]);
    }
};