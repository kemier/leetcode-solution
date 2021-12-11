#include <vector>

using namespace std;

class Solution
{
public:
    bool isUgly(int num)
    {
        if (num <= 0)
        {
            return false;
        }

        vector<int> factor{2, 3, 5};
        for (int i : factor)
        {
            while (num % i == 0)
            {
                num = num / i;
            }
        }
        if (num == 1)
        {
            return true;
        }
        return false;
    }
};
