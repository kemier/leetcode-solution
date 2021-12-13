#include <vector>

using namespace std;

class UnionFind
{ //出入并查集只需要一个逻辑正确功能完备的UF类即可，效率什么的不用太考虑
public:
    UnionFind(int n)
    {

        count = n;
        parent = vector<int>(n);
        rank = vector<int>(n);
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
            rank[i] = 1;
        }
        // cout<<"flag:2"<<endl;
    }

    int find(int x)
    {
        while (parent[x] != x)
        {
            parent[x] = parent[parent[x]]; //通过递归返回根节点
            x = parent[x];
        }
        return x;
    }

    void Union(int x, int y)
    {
        int rootx = find(x);
        int rooty = find(y);
        if (rootx == rooty)
        {
            return;
        }
        if (rank[rootx] > rank[rooty])
        {
            parent[rooty] = rootx;
            rank[rootx] = rank[rootx] + rank[rooty];
        }
        else
        {
            parent[rootx] = rooty;
            rank[rooty] = rank[rooty] + rank[rootx];
        }
        count = count - 1;
    }

    int connected(int x, int y)
    {
        int rootx = find(x);
        int rooty = find(y);
        return rootx == rooty;
    }

    int getCount() const
    {
        return count;
    }

private:
    // vector<int> parent=vector<int>(100);
    // vector<int> rank=vector<int>(100);
    vector<int> parent;
    vector<int> rank;
    int count;
};

class Solution //利用并查集
{
public:
    void solve(vector<vector<char>> &board)
    {

        // cout<<board[1][1]<<endl;
        int m = board.size();

        int n = board[0].size();
        if (m <= 2 || n <= 2)
        {
            return;
        }
        // cout<<"flag:1"<<endl;
        // cout<<"m: "<<m<<endl;
        // cout<<"n: "<<n<<endl;
        UnionFind *un = new UnionFind(m * n + 1);

        int bb = m * n;
        for (int i = 0; i < m; i++)
        {
            if (board[i][0] == 'O')
            {
                un->Union(i * n, bb);
            }
            if (board[i][n - 1] == 'O')
            {
                un->Union(i * n + n - 1, bb);
            }
        }
        for (int j = 0; j < n; j++)
        {
            if (board[0][j] == 'O')
            {
                un->Union(j, bb);
            }
            if (board[m - 1][j] == 'O')
            {
                un->Union(n * (m - 1) + j, bb);
            }
        }
        vector<vector<int>> jj(4, vector<int>(2, 0));
        jj[0][0] = 0;
        jj[0][1] = 1;
        jj[1][0] = 0;
        jj[1][1] = -1;
        jj[2][0] = 1;
        jj[2][1] = 0;
        jj[3][0] = -1;
        jj[3][1] = 0;
        for (int i = 1; i < m - 1; i++)
        {
            for (int j = 1; j < n - 1; j++)
            {
                if (board[i][j] == 'O')
                {
                    for (int k = 0; k < 4; k++)
                    {
                        int x = i + jj[k][0];
                        int y = j + jj[k][1];
                        // cout<<"jj[k][0]: "<<jj[k][0]<<endl;
                        // cout<<"jj[k][1]: "<<jj[k][1]<<endl;
                        // cout<<"----"<<endl;
                        if (board[x][y] == 'O')
                        {
                            un->Union(n * x + y, n * i + j);
                            // cout<<"work once"<<endl;
                        }
                    }
                }
            }
        }

        // cout<<"un->find(1*20+10)"<<un->find(1*20+10)<<endl;

        for (int i = 1; i < m - 1; i++)
        {
            for (int j = 1; j < n - 1; j++)
            {
                if (!un->connected(i * n + j, bb))
                {
                    board[i][j] = 'X';
                }
            }
        }
    }
};
