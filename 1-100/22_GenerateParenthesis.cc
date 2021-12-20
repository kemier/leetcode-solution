#include <vector>
#include <string>
#include <memory>
using namespace std;

class Solution //暴力法
{
    bool valid(const string &str)
    {
        int balance = 0;
        for (char c : str)
        {
            if (c == '(')
            {
                ++balance;
            }
            else
            {
                --balance;
            }
            if (balance < 0)
            {
                return false;
            }
        }
        return balance == 0;
    }

    void generate_all(string &current, int n, vector<string> &result)
    {
        if (n == current.size())
        {
            if (valid(current))
            {
                result.push_back(current);
            }
            return;
        }
        current += '(';
        generate_all(current, n, result);
        current.pop_back();
        current += ')';
        generate_all(current, n, result);
        current.pop_back();
    }

public:
    vector<string> generateParenthesis(int n)
    {
        vector<string> result;
        string current;
        generate_all(current, n * 2, result);
        return result;
    }
};

class Solution2 //回溯法
{
    void backtrack(vector<string> &ans, string &cur, int open, int close, int n)
    {
        if (cur.size() == n * 2)
        {
            ans.push_back(cur);
            return;
        }
        if (open < n)
        {
            cur.push_back('(');
            backtrack(ans, cur, open + 1, close, n);
            cur.pop_back();
        }
        if (close < open)
        {
            cur.push_back(')');
            backtrack(ans, cur, open, close + 1, n);
            cur.pop_back();
        }
    }

public:
    vector<string> generateParenthesis(int n)
    {
        vector<string> result;
        string current;
        backtrack(result, current, 0, 0, n);
        return result;
    }
};

class Solution3 //按括号序列的长度递归
{
    shared_ptr<vector<string>> cache[100] = {nullptr};

public:
    shared_ptr<vector<string>> generate(int n)
    {
        if (cache[n] != nullptr)
            return cache[n];
        if (n == 0)
        {
            cache[0] = shared_ptr<vector<string>>(new vector<string>{""});
        }
        else
        {
            auto result = shared_ptr<vector<string>>(new vector<string>);
            for (int i = 0; i != n; ++i)
            {
                auto lefts = generate(i);
                auto rights = generate(n - i - 1);
                for (const string &left : *lefts)
                    for (const string &right : *rights)
                        result->push_back("(" + left + ")" + right);
            }
            cache[n] = result;
        }
        return cache[n];
    }
    vector<string> generateParenthesis(int n)
    {
        return *generate(n);
    }
};
