#include <vector>

using namespace std;

class Solution //DFS
{
public:
    void DFS(int n, int factor, vector<int> vec)
    {
        if (factor > sqrt(n))
            return;
        DFS(n, factor + 1, vec);
        if (n % factor == 0)
        {
            vec.push_back(factor);
            DFS(n / factor, factor, vec);
            vec.push_back(n / factor);
            ans.push_back(vec);
        }
    }

    vector<vector<int>> getFactors(int n)
    {
        DFS(n, 2, vector<int>{});
        return ans;
    }

private:
    vector<vector<int>> ans;
};