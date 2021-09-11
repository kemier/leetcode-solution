#include <string>
#include <unordered_map>
#include <iostream>
using namespace std;

#define DSA_STACK_LIST
#include "stack/stack.h"

class Solution //栈  时间复杂度：O(n)  空间复杂度：O(n + |\Sigma|)  其中 |\Sigma| 表示字符集长度
{
public:
    bool isValid(string s)
    {
        int n = s.size();
        if (n % 2 == 1)
        {
            return false;
        }

        unordered_map<char, char> pairs = {
            {')', '('},
            {']', '['},
            {'}', '{'}};
        Stack<char> stk;
        for (char ch : s)
        {
            if (pairs.count(ch))
            {
                if (stk.empty() || stk.top() != pairs[ch])
                {
                    return false;
                }
                stk.pop();
            }
            else
            {
                stk.push(ch);
            }
        }
        return stk.empty();
    }
};

int main()
{
    string s = "([)]";
    Solution solution;
    cout << boolalpha << solution.isValid(s) << endl;
    return 0;
}