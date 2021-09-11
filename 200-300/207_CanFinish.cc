#include <vector>

using namespace std;

//有向无环图(DAG)
class Solution
{
private:
    vector<vector<int>> edges;
    vector<int> visited; //0-未搜索 1-搜索中 2-已搜索
    bool valid = true;

public:
    void dfs(int u) //深度优先搜索
    {
        visited[u] = 1;
        for (int v : edges[u])
        {
            if (visited[v] == 0)
            {
                dfs(v);
                if (!valid)
                {
                    return;
                }
            }
            else if (visited[v] == 1)
            {
                valid = false;
                return;
            }
        }
        visited[u] = 2;
    }

    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {
        edges.resize(numCourses);
        visited.resize(numCourses);
        for (const auto &info : prerequisites)
        {
            edges[info[1]].push_back(info[0]);
        }
        for (int i = 0; i < numCourses && valid; ++i)
        {
            if (!visited[i])
            {
                dfs(i);
            }
        }
        return valid;
    }
};

class Solution2
{
private:
    vector<vector<int>> edges; //课程 edges[0]=1  1依赖0
    vector<int> indeg;         //入度

public:
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites) //广度优先搜索
    {
        edges.resize(numCourses);
        indeg.resize(numCourses);
        for (const auto &info : prerequisites)
        {
            edges[info[1]].push_back(info[0]);
            ++indeg[info[0]];
        }

        queue<int> q;
        for (int i = 0; i < numCourses; ++i)
        {
            if (indeg[i] == 0) //入度为0才加入列表，代表可以学习此课程
            {
                q.push(i);
            }
        }

        int visited = 0;
        while (!q.empty()) //循环遍历列表，代表学习过程，pop后并将依赖此课程的课程的入度减一 BFS TopSort.
        {
            ++visited;
            int u = q.front();
            q.pop();
            for (int v : edges[u])
            {
                --indeg[v];
                if (indeg[v] == 0)
                {
                    q.push(v);
                }
            }
        }

        return visited == numCourses;
    }
};
