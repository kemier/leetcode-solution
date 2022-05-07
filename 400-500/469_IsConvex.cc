#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    bool isConvex(vector<vector<int>> &points)
    {
        for (long i = 0, n = points.size(), prev = 0, cur; i < n; ++i)
        {
            cur = det2({points[i], points[(i + 1) % n], points[(i + 2) % n]});
            if (cur != 0)
            {
                if (cur * prev < 0)
                {
                    return false;
                }
                else
                {
                    prev = cur;
                }
            }
        }
        return true;
    }

private:
    long det2(const vector<vector<int>> &A)
    {
        return (A[1][0] - A[0][0]) * (A[2][1] - A[0][1]) - (A[1][1] - A[0][1]) * (A[2][0] - A[0][0]);
    }
};21