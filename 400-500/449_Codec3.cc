#include <bits/stdc++.h>

using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec
{
public:
    void postorder(TreeNode *root, string &res)
    {
        if (root == nullptr)
            return;
        postorder(root->left, res);
        postorder(root->right, res);
        res += to_string(root->val) + ' ';
    }

    // Encodes a tree to a single string.
    string serialize(TreeNode *root)
    {
        string res;
        postorder(root, res);
        if (res.length() > 0)
            res.at(res.length() - 1) = '\0';
        return res;
    }

    TreeNode *helper(int lower, int upper, deque<int> nums)
    {
        if (nums.empty())
            return nullptr;
        int val = nums.back();
        nums.pop_back();
        if (val < lower || val > upper)
            return nullptr;
        TreeNode *root = new TreeNode(val);
        root->right = helper(val, upper, nums);
        root->left = helper(lower, val, nums);
        return root;
    }

    // Decodes your encoded data to tree.
    TreeNode *deserialize(string data)
    {
        if (data.size() == 0)
            return nullptr;
        deque<int> nums;
        istringstream iss(data);         // 输入流
        string token;                    // 接收缓冲区
        while (getline(iss, token, ' ')) // 以split为分隔符
        {
            nums.push_back(stoi(token));
        }

        return helper(INT_MIN, INT_MAX, nums);
    }
};

class Codec2
{
public:
    string serialize(TreeNode *root)
    {
        if (!root)
            return "null";
        return to_string(root->val) + ' ' + serialize(root->left) + ' ' + serialize(root->right);
    }

    TreeNode *deserialize(string data)
    {
        stringstream ss(data);
        return dfs(ss);
    }
    TreeNode *dfs(stringstream &ss)
    {
        string val;
        ss >> val;
        if (val == "null")
            return nullptr;
        TreeNode *root = new TreeNode(stoi(val));
        root->left = dfs(ss);
        root->right = dfs(ss);
        return root;
    }
};

int main()
{
    TreeNode *root = new TreeNode(2);
    root->left = new TreeNode(1);
    root->right = new TreeNode(3);
    Codec c;
    cout << c.serialize(root) << endl;
    c.deserialize(c.serialize(root));
    return 0;
}