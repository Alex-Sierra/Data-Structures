#include <bits/stdc++.h>
 
using namespace std;

struct trie {
    struct node {
        int ocurrences;
        int count;
        map<char, node*> next;
        node() {
            ocurrences = 0;
            count = 0;
        }
    };
    node *root;
    trie() {
        root = new node();
    }
    void add(string s) {
        node *cur = root;
        for (char c : s) {
            cur->count++;
            if (cur->next.find(c) == cur->next.end())
                cur->next[c] = new node();
            cur = cur->next[c];
        }
        cur->ocurrences++;
        cur->count++;
    }
    bool delete_(string s) {
        node *cur = root;
        for (char c : s) {
            if (cur->next.find(c) == cur->next.end())
                return false;
            cur = cur->next[c];
        }
        if (cur->ocurrences != 0) {
            cur = root;
            for (char c : s) {
                cur->count--;
                cur = cur->next[c];
            }
            cur->ocurrences--;
            cur->count--;
            return true;
        }
        return false;
    }
    int find(string s) {
        node *cur = root;
        for (char c : s) {
            if (cur->next.find(c) == cur->next.end())
                return 0;
            cur = cur->next[c];
        }
        return cur->ocurrences;
    }
    string find_prefix(string s) {
        node *cur = root;
        string result;
        for (char c : s) {
            if (cur->next.find(c) == cur->next.end())
                break;
            cur = cur->next[c];
            result += c;
        }
        return result;
    }
    vector<string> find_suffixes(string s) {
        node *cur = root;
        for (char c : s) {
            if (cur->next.find(c) == cur->next.end())
                return {};
            cur = cur->next[c];
        }
        vector<string> result;
        function<void(node*, string)> dfs = [&](node *cur, string s) {
            if (cur->ocurrences != 0)
                result.push_back(s);
            for (auto p : cur->next)
                dfs(p.second, s + p.first);
        };
        dfs(cur, "");
        return result;
    }
    int count_prefix(string s) {
        node *cur = root;
        for (char c : s) {
            if (cur->next.find(c) == cur->next.end())
                return 0;
            cur = cur->next[c];
        }
        return cur->count;
    }
    string find_kth(int k) {
        node *cur = root;
        string result;
        while (k > 0) {
            vector<pair<char, node*>> v(cur->next.begin(), cur->next.end());
            sort(v.begin(), v.end());
            if (v.empty())
                break;
            for (auto p : v) {
                if (p.second->count >= k) {
                    result += p.first;
                    cur = p.second;
                    break;
                }
                k -= p.second->count;
            }
        }
        return result;
    }
};