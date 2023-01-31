#include <bits/stdc++.h>
 
using namespace std;

vector<int> kmp(string text, string pattern) {
    int n = text.size();
    int m = pattern.size();
    vector<int> pi(m);
    vector<int> result;
    // prefix function
    for (int i = 1; i < m; i++) {
        int j = pi[i - 1];
        while (j > 0 && pattern[i] != pattern[j])
            j = pi[j - 1];
        if (pattern[i] == pattern[j])
            j++;
        pi[i] = j;
    }
    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j > 0 && text[i] != pattern[j])
            j = pi[j - 1];
        if (text[i] == pattern[j])
            j++;
        if (j == m) {
            result.push_back(i - m + 1);
            j = pi[j - 1];
        }
    }
    return result;
}