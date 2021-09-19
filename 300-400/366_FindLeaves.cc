#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
    vector<vector<int>> ans;
    queue<TreeNode*> q;
    unordered_map<TreeNode*, int> map;//父节点底下挂着几个子节点
public:
    vector<vector<int>> findLeaves(TreeNode* root) {
        reverse(root);//上下翻转二叉树
        while(!q.empty())
        {
        	int size = q.size(), i = 0;
        	vector<int> lv(size);
        	while(size--)
        	{
        		TreeNode *cur = q.front();
        		q.pop();
        		map[cur->left]--;//原父节点的子节点计数-1
        		lv[i++] = cur->val;//当前值写入答案
        		if(cur->left && map[cur->left]==0)//父节点计数为0，可以入队
        			q.push(cur->left);
        	}
        	ans.push_back(lv);
        }
        return ans;
    }
    TreeNode* reverse(TreeNode* root)
    {
    	if(!root) return NULL;
    	auto l = root->left;
    	auto r = root->right;
    	if(!l && !r)
    		q.push(root);//叶子节点加入队列
    	map[root] += (l?1:0) + (r?1:0);//记得加括号，子节点个数
    	root->left = NULL;//断开子节点
    	root->right = NULL;
    	auto lc = reverse(l);
    	auto rc = reverse(r);
    	if(lc)
    		lc->left = root;//子节点的left指向父节点
    	if(rc)
    		rc->left = root;
    	return root;
    }
};


class Solution2 {
    vector<vector<int>> ans;
public:
    vector<vector<int>> findLeaves(TreeNode* root) {
        dfs(root);
        return ans;
    }
    int dfs(TreeNode* root)
    {
        if(!root) return -1;
        int hl = dfs(root->left);
        int hr = dfs(root->right);
        int hcur = max(hl, hr) + 1;
        if(ans.size() <= hcur)
            ans.push_back({});
        ans[hcur].push_back(root->val);
        return hcur;
    }
};
