#include <bits/stdc++.h>

using namespace  std;

class Solution {//Rabin-Karp 字符串编码
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
    	int k = 1, i = 0, j = 0, maxlen = 0;
    	for( ; j < nums.size(); ++j)
    	{
    		if(nums[j]==0)
    		{   
                k--;
                while(k < 0)//要维持窗口内可替换的次数 >= 0
                {
                    if(nums[i++]==0)
                        k++;
                }
    		}
    		maxlen = max(maxlen,j-i+1);
    	}
        return maxlen;
    }
};



class Solution2 {//KMP算法
public:
    string longestPrefix(string s) {
        int n = s.size();
        vector<int> fail(n, -1);
        for (int i = 1; i < n; ++i) {
            int j = fail[i - 1];
            while (j != -1 && s[j + 1] != s[i]) {
                j = fail[j];
            }
            if (s[j + 1] == s[i]) {
                fail[i] = j + 1;
            }
        }
        return s.substr(0, fail[n - 1] + 1);
    }
};

