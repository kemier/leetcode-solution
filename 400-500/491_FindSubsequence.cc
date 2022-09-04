#include <bits/stdc++.h>

using namespace  std;

class Solution1 {//二进制枚举 + 哈希二进制枚举 + 哈希
public:
    vector<int> temp;
    vector<vector<int>> ans;
    unordered_set<int> s;
    int n;

    void findSubsequences(int mask, vector<int>& nums) {
        temp.clear();
        for (int i = 0; i < n; ++i) {
            if (mask & 1) {
                temp.push_back(nums[i]);
            }
            mask >>= 1;
        }
    }

    bool check() {
        for (int i = 1; i < temp.size(); ++i) {
            if (temp[i] < temp[i - 1]) {
                return false;
            }
        }
        return temp.size() >= 2;
    }

    int getHash(int base, int mod) {
        int hashValue = 0;
        for (const auto &x: temp) {
            hashValue = 1LL * hashValue * base % mod + (x + 101);
            hashValue %= mod;
        }
        return hashValue;
    }

    vector<vector<int>> findSubsequences(vector<int>& nums) {
        n = nums.size();
        for (int i = 0; i < (1 << n); ++i) {
            findSubsequences(i, nums);
            int hashValue = getHash(263, int(1E9) + 7);
            if (check() && s.find(hashValue) == s.end()) {
                ans.push_back(temp);
                s.insert(hashValue);
            }
        }
        return ans;
    }
};


class Solution2 {//递归枚举 + 减枝
public:
    vector<int> temp; 
    vector<vector<int>> ans;

    void dfs(int cur, int last, vector<int>& nums) {
        if (cur == nums.size()) {
            if (temp.size() >= 2) {
                ans.push_back(temp);
            }
            return;
        }
        if (nums[cur] >= last) {
            temp.push_back(nums[cur]);
            dfs(cur + 1, nums[cur], nums);
            temp.pop_back();
        }
        if (nums[cur] != last) {
            dfs(cur + 1, last, nums);
        }
    }

    vector<vector<int>> findSubsequences(vector<int>& nums) {
        dfs(0, INT_MIN, nums);
        return ans;
    }
};

