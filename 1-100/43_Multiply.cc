#include <string>

using namespace std;

class Solution
{
public:
    string multiply(string num1, string num2)
    {
        if (num1 == "0" || num2 == "0")
            return "0";
        int m = num1.size(), n = num2.size();
        auto ansArr = vector<int>(m + n);
        for (int i = 0; i < m; i++)
        {
            int x = num1.at(i) - '0';
            for (int j = 0; j < n; j++)
            {
                int y = num2.at(j) - '0';
                ansArr.at[i + j + 1] += x * y;
            }
        }

        for (int i = m + n - 1; i > 0; i--)
        {
            ansArr[i - 1] += ansArr[i] / 10;
            ansArr[i] %= 10;
        }
        int index = ansArr[0] == 0 ? 1 : 0;
        string ans;
        while (index < m + n)
        {
            ans.push_back(ansArr[index]);
            index++;
        }
        for (auto &c : ans)
        {
            c += '0';
        }
        return ans;
    }
}