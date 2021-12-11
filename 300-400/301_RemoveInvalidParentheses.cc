#include <vector>
#include <string>
#include <set>

using namespace std;

class Solution
{

public:
    vector<string> removeInvalidParentheses(string s)
    {
        len = s.length();
        charArray.assign(s.begin(), s.end());

        // 第 1 步：遍历一次，计算多余的左右括号
        int leftRemove = 0;
        int rightRemove = 0;
        for (int i = 0; i < len; i++)
        {
            if (charArray[i] == '(')
            {
                leftRemove++;
            }
            else if (charArray[i] == ')')
            {
                // 遇到右括号的时候，须要根据已经存在的左括号数量决定
                if (leftRemove == 0)
                {
                    rightRemove++;
                }
                if (leftRemove > 0)
                {
                    // 关键：一个右括号出现可以抵销之前遇到的左括号
                    leftRemove--;
                }
            }
        }

        // 第 2 步：回溯算法，尝试每一种可能的删除操作
        string path;
        dfs(0, 0, 0, leftRemove, rightRemove, path);
        vector<string> tmp(validExpressions.begin(), validExpressions.end());
        return tmp;
    }

    /**
     * @param index       当前遍历到的下标
     * @param leftCount   已经遍历到的左括号的个数
     * @param rightCount  已经遍历到的右括号的个数
     * @param leftRemove  最少应该删除的左括号的个数
     * @param rightRemove 最少应该删除的右括号的个数
     * @param path        一个可能的结果
     */
private:
    void dfs(int index, int leftCount, int rightCount, int leftRemove, int rightRemove, string &path)
    {
        if (index == len)
        {
            if (leftRemove == 0 && rightRemove == 0)
            {
                validExpressions.insert(path);
            }
            return;
        }

        char character = charArray[index];
        // 可能的操作 1：删除当前遍历到的字符
        if (character == '(' && leftRemove > 0)
        {
            // 由于 leftRemove > 0，并且当前遇到的是左括号，因此可以尝试删除当前遇到的左括号
            dfs(index + 1, leftCount, rightCount, leftRemove - 1, rightRemove, path);
        }
        if (character == ')' && rightRemove > 0)
        {
            // 由于 rightRemove > 0，并且当前遇到的是右括号，因此可以尝试删除当前遇到的右括号
            dfs(index + 1, leftCount, rightCount, leftRemove, rightRemove - 1, path);
        }

        // 可能的操作 2：保留当前遍历到的字符
        path += character;
        if (character != '(' && character != ')')
        {
            // 如果不是括号，继续深度优先遍历
            dfs(index + 1, leftCount, rightCount, leftRemove, rightRemove, path);
        }
        else if (character == '(')
        {
            // 考虑左括号
            dfs(index + 1, leftCount + 1, rightCount, leftRemove, rightRemove, path);
        }
        else if (rightCount < leftCount)
        {
            // 考虑右括号
            dfs(index + 1, leftCount, rightCount + 1, leftRemove, rightRemove, path);
        }
        path.erase(path.end() - 1);
    }
    int len;
    vector<char> charArray;

    set<string> validExpressions;
};

class Solution
{
public:
    void dfs(string &s, string &cur, int idx, int lcnt, int rcnt, int lnum, int rnum, set<string> &ans)
    {
        if (idx == s.size())
        {
            if (lcnt == 0 && rcnt == 0)
                ans.insert(cur);
            return;
        }
        if (lnum < rnum)
            return; //不合法，剪枝
        if (s[idx] == '(' && lcnt > 0)
        { //删除左括号
            dfs(s, cur, idx + 1, lcnt - 1, rcnt, lnum, rnum, ans);
        }
        else if (s[idx] == ')' && rcnt > 0)
        { //删除右括号
            dfs(s, cur, idx + 1, lcnt, rcnt - 1, lnum, rnum, ans);
        }
        //保留该字符
        if (s[idx] == '(')
            lnum++; //更新计数
        else if (s[idx] == ')')
            rnum++;
        cur.push_back(s[idx]);
        dfs(s, cur, idx + 1, lcnt, rcnt, lnum, rnum, ans);
        cur.pop_back();
    }

    vector<string> removeInvalidParentheses(string s)
    {
        int lcnt = 0, rcnt = 0;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '(')
                lcnt++;
            else if (s[i] == ')')
            {
                if (lcnt == 0)
                    rcnt++;
                else
                    lcnt--;
            }
        }
        if (lcnt == 0 && rcnt == 0)
            return {s};
        vector<string> ans;
        set<string> set;
        string str;
        dfs(s, str, 0, lcnt, rcnt, 0, 0, set);
        for (auto itr = set.begin(); itr != set.end(); itr++)
            ans.push_back(*itr);
        return ans;
    }
};