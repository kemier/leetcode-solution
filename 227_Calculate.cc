#include <string>
#include <cctype>
#include <stack>

using namespace std;

class Solution
{
public:
    int calculate(string s)
    {
        int begin = 0;
        return calHelper(s, begin);
    }
    int calHelper(string s, int &i) //i用于记录计算开始的索引
    {
        char operation = '+';
        stack<int> nums;
        int num = 0;
        int res = 0;
        bool flag = false;
        for (i; i < s.size(); i++)
        {
            if (s[i] >= '0' && s[i] <= '9')
            {
                num = num * 10 + (s[i] - '0');
            }
            if (s[i] == '(')
            {
                num = calHelper(s, ++i); //从i的下一个开始计算， 进入递归
                i++;                     //计算完之后的i指向)所以再++
            }
            if (((s[i] < '0' || s[i] > '9') && s[i] != ' ') || i >= s.size() - 1) // 继续计算
            {
                int pre = 0;
                switch (operation)
                {
                case '+':
                    nums.push(num);
                    break;
                case '-':
                    nums.push(-num);
                    break;
                case '*':
                    pre = nums.top();
                    nums.pop();
                    nums.push(pre * num);
                    break;
                case '/':
                    pre = nums.top();
                    nums.pop();
                    nums.push(pre / num);
                    break;
                }

                operation = s[i];
                num = 0;
            }
            if (s[i] == ')') //遇到)回到上一级递归
            {
                break;
            }
        }
        while (!nums.empty())
        {
            res += nums.top();
            nums.pop();
        }
        return res;
    }
};