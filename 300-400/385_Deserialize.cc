#include <vector>
#include <string>
#include <ctype.h>

using namespace std;


/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 **/
class NestedInteger {
  public:
    // Constructor initializes an empty nested list.
    NestedInteger();
    // Constructor initializes a single integer.
    NestedInteger(int value);
    // Return true if this NestedInteger holds a single integer, rather than a nested list.
    bool isInteger() const;
    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const;
    // Set this NestedInteger to hold a single integer.
    void setInteger(int value);
    // Set this NestedInteger to hold a nested list and adds a nested integer to it.
    void add(const NestedInteger &ni);
    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    const vector<NestedInteger> &getList() const;
};
 
class Solution {
public:
    NestedInteger dfs(string& s,int& curp) {
        NestedInteger res = NestedInteger();
        curp ++;// '[' 跳过
        while(1) {
            if(isdigit(s[curp]) || s[curp] == '-') {// 处理数字
               int n = 0;
               bool f = s[curp] == '-' ? true : false;
               if(f) curp ++;
                while(isdigit(s[curp])) {
                    n *= 10;
                    n += s[curp] - '0';
                    curp ++;
                }
                if(f) n *= -1;
                res.add(NestedInteger(n)); 
            }
            if(s[curp] == ',') {// 跳过
                curp ++;
            }
            if(s[curp] == '[') {// 进入新的递归
                NestedInteger next = dfs(s,curp);
                res.add(next);
            }
            if(s[curp] == ']') {// 退出该层递归
                curp ++;
                break;
            } 
        }
        return res;
    }
    NestedInteger deserialize(string s) {
        if(s[0] != '[') return NestedInteger(stoi(s));
        int curp = 0;
        return dfs(s,curp);
    }
};

