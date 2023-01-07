//
// Created by 曾宁 on 2023/1/7.
//

#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int climbStairs(int n) {
        int p = 0, q = 0, r = 1;
        for (int i = 1; i <= n; ++i) {
            p = q;
            q = r;
            r = p + q;
        }
        return r;
    }
};

