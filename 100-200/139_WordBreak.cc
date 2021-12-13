#include <vector>
#include <string>

using namespace std;

class Solution //字典树+DFS缓存
{
public:
    // 小写字母的个数
    static const int LITTLE_CHAR_NUM = 26;

    struct Node
    {
        char value; // 字符
        bool isEnd; // 结束标志
        Node *next[LITTLE_CHAR_NUM];

        Node()
        {
            value = 0;
            isEnd = false;
            for (int i = 0; i < LITTLE_CHAR_NUM; i++)
            {
                next[i] = nullptr;
            }
        }
    };

    Node *CreateTies(vector<string> &wordDict)
    { // 建立字典树
        Node *root = new Node();
        for (auto word : wordDict)
        {
            Node *p = root; // 从根开始
            for (auto ch : word)
            {
                int index = ch - 'a';
                if (p->next[index] == nullptr)
                {
                    p->next[index] = new Node();
                }
                p->next[index]->value = ch;
                p = p->next[index];
            }
            p->isEnd = true; // 最后1个
        }
        return root;
    }

    void Destory(Node *root)
    { // 销毁字典树
        if (root != nullptr)
        {
            bool haveNext = false;
            for (int i = 0; i < LITTLE_CHAR_NUM; ++i)
            {
                if (root->next[i] != nullptr)
                {
                    Destory(root->next[i]);
                    haveNext = true;
                }
            }
            if (!haveNext)
            {
                delete root;
            }
        }
    }

    void Show(Node *root)
    {
        if (root != nullptr)
        {
            cout << root->value;
            if (root->isEnd)
            {
                cout << "(f)";
            }
            cout << endl;
            for (int i = 0; i < LITTLE_CHAR_NUM; ++i)
            {
                Show(root->next[i]);
            }
        }
    }

    bool dfsFind(Node *root, vector<bool> &dpFail, string &s, int startPos)
    {
        if (root == nullptr || startPos < 0 || startPos > s.size())
        {
            return false; // 参数错误
        }
        else if (startPos == s.size())
        {
            return true; // 刚好结束
        }
        else if (dpFail[startPos])
        {
            return false; // 已搜过，没找到
        }
        else
        {                   // 搜搜看
            Node *p = root; // 从根开始搜索
            for (int i = startPos; i < s.size(); i++)
            {
                int index = (s[i] - 'a');
                if (p->next[index] == nullptr)
                {
                    break; // 无需继续查找了
                }
                p = p->next[index];
                if (p->isEnd && dfsFind(root, dpFail, s, i + 1))
                {
                    return true; // 当前单词结束，后续也OK
                }
            }
            dpFail[startPos] = true; // 失败
            return false;            // 没找到
        }
    }

    bool wordBreak(string s, vector<string> &wordDict)
    {
        if (s.empty() || wordDict.empty())
        {
            return false;
        }
        Node *root = CreateTies(wordDict);
        // Show(root); // 可以打印出来看看
        // dp[i] 表示从i开始查找的答案（是否失败）
        vector<bool> dpFail(s.size(), false);
        bool ans = dfsFind(root, dpFail, s, 0);
        Destory(root);
        return ans;
    }
};
