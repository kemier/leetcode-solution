//
// Created by 曾宁 on 2023/1/8.
//

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    void reverse(string s, int from, int to) {
        while (from<to) {
            char c = s[from];
            s[from] = s[to];
            s[to] = c;
            from ++;
            to --;
        }
    }
public:
    void reverseWords(string s) {
        int pos = 0;
        for(int i=0; i<=s.length(); i++) {
            if (i<s.length() && s[i] != ' ') continue;
            reverse(s, pos, i-1);
            pos = i+1;
        }
        reverse(s, 0, s.length-1);
    }
};
