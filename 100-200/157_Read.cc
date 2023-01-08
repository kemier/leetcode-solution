//
// Created by 曾宁 on 2023/1/8.
//

#include <bits/stdc++.h>
using namespace std;

// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Number of characters to read
     * @return    The number of actual characters read
     */
    int read(char *buf, int n) {
        int count = 0;
        while (n) {
            char file[4];
            int m = read4(file);
            for (int i = 0; i < m && count < n; ++i) {
                buf[count] = file[i];
                count ++;
            }
            if (m < 4)
                break;
        }
        return count;
    }
};
