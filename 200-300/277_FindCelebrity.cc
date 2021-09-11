#include <vector>
#include <numeric>

using namespace std;

bool knows(int a, int b);

class Solution
{
public:
    int findCelebrity(int n)
    {
        vector<int> candidates(n);
        iota(candidates.begin(), candidates.end(), 0);
        while (candidates.size() >= 2)
        {
            int a = candidates.back();
            candidates.pop_back();
            int b = candidates.back();
            candidates.pop_back();
            if (knows(a, b))
                candidates.push_back(b);
            else
                candidates.push_back(a);
        }
        return verifyCelebrity(candidates[0], n);
    }

private:
    int verifyCelebrity(int c, int n)
    {
        for (int i = 0; i < n; i++)
        {
            if (i == c)
                continue;
            if (knows(c, i) || !knows(i, c))
                return -1;
        }
        return c;
    }
};
