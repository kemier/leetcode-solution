//
// Created by 曾宁 on 2023/1/8.
//
#include <bits/stdc++.h>
using namespace std;



/*
  Given two strings S and T, determine if they are both one edit distance apart.
*/
bool isOneEditDistance(string s, string t) {
    int sSize = s.size();
    int tSize = t.size();
    if(abs(sSize - tSize) > 1) return false;
    int count = 0;

    if(sSize == tSize) {
        int i = 0, j = 0;
        while(i < sSize && j < tSize) {
            if(s[i] != t[i]) {
                count++;
                if(count > 1) return false;
            }
            i++; j++;
        }
        return true;
    } else {
        string tmp = sSize > tSize ? s : t;
        string tmp_1 = sSize > tSize ? t : s;
        int i = 0, j = 0;
        while(i < sSize && j < tSize) {
            if((tmp[i] != tmp_1[j]) && (count != 0)) {
                return false;
            } else if(tmp[i] != tmp_1[j]) {
                count++;
                i++;
            } else {
                i++;
                j++;
            }
        }
        return true;
    }
}



