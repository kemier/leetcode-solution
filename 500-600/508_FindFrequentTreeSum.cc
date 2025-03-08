
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>


using namespace std;

// Definition for a binary tree node.
struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


//source: https://leetcode.com/problems/most-frequent-subtree-sum/
// dfs 
// Time complexity: O(n)
// Space complexity: O(n)

class Solution {
    unordered_map<int, int> cnt;
    int maxCnt = 0;

    int dfs(TreeNode *node) {
        if (node == nullptr) {
            return 0;
        }
        int sum = node->val + dfs(node->left) + dfs(node->right);
        maxCnt = max(maxCnt, ++cnt[sum]);
        return sum;
    }

public:
    vector<int> findFrequentTreeSum(TreeNode *root) {
        dfs(root);
        vector<int> ans;
        for (auto &[s, c]: cnt) {
            if (c == maxCnt) {
                ans.emplace_back(s);
            }
        }
        return ans;
    }
};
