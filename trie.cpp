#include <bits/stdc++.h>
 
using namespace std;

struct trie {
    struct node {
        int ocurrences;
        map<char, node*> next;
        node() {
            ocurrences = 0;
        }
    };
    node *root;
    trie() {
        root = new node();
    }
    void add(string &s) {
        node *cur = root;
        for (char c : s) {
            if (cur->next.find(c) == cur->next.end())
                cur->next[c] = new node();
            cur = cur->next[c];
        }
        cur->ocurrences++;
    }
    bool delete_(string &s) {
        node *cur = root;
        for (char c : s) {
            if (cur->next.find(c) == cur->next.end())
                return false;
            cur = cur->next[c];
        }
        if (cur->ocurrences != 0) {
            cur->ocurrences--;
            return true;
        }
        return false;
    }
    int find(string &s) {
        node *cur = root;
        for (char c : s) {
            if (cur->next.find(c) == cur->next.end())
                return 0;
            cur = cur->next[c];
        }
        return cur->ocurrences;
    }
    string find_prefix(string &s) {
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
};