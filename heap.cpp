#include <bits/stdc++.h>
 
using namespace std;

struct heap {
    vector<int> h;
    function<bool(int, int)> cmp = [&](int a, int b) {
        if (_comparer) 
            return a >= b;
        else
            return a <= b;
    };
    bool _comparer;
    void build(vector<int> &a, bool comparer = true) {
        h = a;
        _comparer = comparer;
        for (int i = h.size() / 2 - 1; i >= 0; i--)
            sift_down(i);
    }
    void sift_up(int i) {
        while (i > 0 && cmp(h[i], h[(i - 1) / 2])) {
            swap(h[i], h[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }
    void sift_down(int i) {
        while (2 * i + 1 < h.size()) {
            int j = 2 * i + 1;
            if (j + 1 < h.size() && cmp(h[j + 1], h[j]))
                j++;
            if (cmp(h[i], h[j]))
                break;
            swap(h[i], h[j]);
            i = j;
        }
    }
    void push(int x) {
        h.push_back(x);
        sift_up(h.size() - 1);
    }
    bool empty() {
        return h.empty();
    }
    int pop() {
        int result = h[0];
        h[0] = h.back();
        h.pop_back();
        sift_down(0);
        return result;
    }
    void remove(int i) {
        h[i] = _comparer ? INT_MAX : INT_MIN;
        sift_up(i);
        pop();
    }
    void change_priority(int i, int p) {
        int old_p = h[i];
        h[i] = p;
        if (cmp(p, old_p))
            sift_up(i);
        else
            sift_down(i);
    }
};