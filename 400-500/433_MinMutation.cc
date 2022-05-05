#include <bits/stdc++.h>

using namespace std;

class Solution
{ //二进制转换+异或运算
public:
    int minMutation(string start, string end, vector<string> bank)
    {
        int a = convertGene(start);
        int b = convertGene(end);

        vector<int> s(bank.size(), 0);
        for (int i = 0; i < s.size(); ++i)
        {
            string str = bank[i];
            s[i] = convertGene(str);
        }

        // 方法1: 更优
        return bfs(a, b, s);

        // 方法2: 也可以
        // int ans = dfs(a, b, s, vector<int>(bank.size(),0));
        // return ans == INT_MAX ? -1 : ans;
    }

private:
    int convertGene(string gene)
    {
        int result = 0;
        for (int i = 0; i < gene.length(); ++i)
        {
            char c = gene[i];
            int value = 1; // default: 0 for 'A'
            switch (c)
            {
            case 'C':
                value = 2;
                break;
            case 'G':
                value = 4;
                break;
            case 'T':
                value = 8;
                break;
            }

            result |= value;
            if (i != gene.length() - 1)
            {
                result <<= 4;
            }
        }

        return result;
    }

    bool isNeibor(int a, int b)
    {
        b = a ^ b;
        a = b & (b - 1);
        b = a & (a - 1);

        return a != 0 && b == 0;
    }

    int bfs(int a, int b, vector<int> s)
    {
        queue<int> q;
        vector<int> v(s.size(), 0);

        q.push(a);

        int level = 0;
        while (!q.empty())
        {
            int size = q.size();
            while (size-- > 0)
            {
                int x = q.front();
                q.pop();
                if (x == b)
                {
                    return level;
                }

                for (int i = 0; i < s.size(); ++i)
                {
                    if (!v[i] && isNeibor(x, s[i]))
                    {
                        v[i] = 1;
                        q.push(s[i]);
                    }
                }
            }

            level++;
        }

        return -1;
    }

    int dfs(int a, int b, vector<int> s, vector<int> v)
    {
        if (a == b)
        {
            return 0;
        }

        int minRet = INT_MAX - 1;
        for (int i = 0; i < s.size(); ++i)
        {
            if (!v[i])
            {
                if (isNeibor(a, s[i]))
                {
                    v[i] = 1;
                    int ret = dfs(s[i], b, s, v);
                    minRet = min(minRet, ret);
                    v[i] = 0;
                }
            }
        }

        return 1 + min(minRet, INT_MAX - 1);
    }
};
