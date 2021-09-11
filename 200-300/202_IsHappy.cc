#include <set>
using namespace std;

class Solution
{
public:
    bool isHappy(int n)
    {
        set<int> recordN;
        int sum = 0;
        while (n != 1)
        {
            recordN.insert(n);
            sum = 0;
            while (n != 0)
            {
                sum += ((n % 10) * (n % 10));
                n = n / 10;
            }
            if (recordN.find(sum) != recordN.end())
                return false;
            n = sum;
        }
        return true;
    }
};