#include <vector>

using namespace std;

class Solution
{

public:
    bool validTree(int n, vector<vector<int>> edges)
    {
        int len = edges.size();
        vector<int> parent(n, -1); //这是记录关系的数组
        for (int i = 0; i < len; i++)
        {
            if (find(parent, edges[i][0]) == find(parent, edges[i][1]))
                return false;
            union(parent, edges[i][0], edges[i][1]);
        }
        int count = 0;
        //查根的数量
        for (int i = 0; i < n; i++)
            if (parent[i] == -1)
                count++;
        return count == 1;
    }

private:
    //查找
    int find(vector<int> parent, int i)
    {
        if (parent[i] == -1)
            return i;
        return find(parent, parent[i]);
    }
    //合并
    void union(vector<int> parent, int x, int y)
    {
        int xset = find(parent, x);
        int yset = find(parent, y);
        if (xset != yset)
            parent[xset] = yset;
    }
};