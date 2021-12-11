#include <iostream>
#include <vector>
#include <set>
using namespace std;

class Solution
{
public:
    vector<vector<int>> multiply(vector<vector<int>> &A, vector<vector<int>> &B)
    {
        if (A.size() == 0 || B.size() == 0)
            return {};
        int m = A.size(), n = A[0].size(), p = B[0].size();
        vector<vector<int>> result(m, vector<int>(p, 0));
        set<int> row, col;
        for (int i = 0, j; i < m; i++)
        {
            for (j = 0; j < n; j++)
                if (A[i][j])
                    break;
            if (j == n)
                row.insert(i);
        }
        for (int i = 0, j; i < p; i++)
        {
            for (j = 0; j < n; j++)
                if (B[j][i])
                    break;
            if (j == n)
                col.insert(i);
        }
        for (int i = 0; i < m; i++)
        {
            if (row.count(i))
                continue;
            for (int j = 0; j < p; j++)
            {
                if (col.count(j))
                    continue;
                for (int k = 0, sum = 0; k < n; k++)
                    result[i][j] += A[i][k] * B[k][j];
            }
        }
        return result;
    }
};