// 并查集模板
#include <vector>
#include <algorithm>
using namespace std;

class UnionFind
{
public:
    vector<int> parent;
    vector<int> size;
    int n;
    // 当前连通分量数目
    int setCount;

public:
    UnionFind(int _n) : n(_n), setCount(_n), parent(_n), size(_n, 1)
    {
        iota(parent.begin(), parent.end(), 0);
    }

    int findset(int x)
    {
        return parent[x] == x ? x : parent[x] = findset(parent[x]);
    }

    bool unite(int x, int y)
    {
        x = findset(x);
        y = findset(y);
        if (x == y)
        {
            return false;
        }
        if (size[x] < size[y])
        {
            swap(x, y);
        }
        parent[y] = x;
        size[x] += size[y];
        --setCount;
        return true;
    }

    bool connected(int x, int y)
    {
        x = findset(x);
        y = findset(y);
        return x == y;
    }
};

class Solution //枚举 + 最小生成树判定
{
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>> &edges)
    {
        int m = edges.size();
        for (int i = 0; i < m; ++i)
        {
            edges[i].push_back(i);
        }
        sort(edges.begin(), edges.end(), [](const auto &u, const auto &v)
             { return u[2] < v[2]; });

        // 计算 value
        UnionFind uf_std(n);
        int value = 0;
        for (int i = 0; i < m; ++i)
        {
            if (uf_std.unite(edges[i][0], edges[i][1]))
            {
                value += edges[i][2];
            }
        }

        vector<vector<int>> ans(2);

        for (int i = 0; i < m; ++i)
        {
            // 判断是否是关键边
            UnionFind uf(n);
            int v = 0;
            for (int j = 0; j < m; ++j)
            {
                if (i != j && uf.unite(edges[j][0], edges[j][1]))
                {
                    v += edges[j][2];
                }
            }
            if (uf.setCount != 1 || (uf.setCount == 1 && v > value))
            {
                ans[0].push_back(edges[i][3]);
                continue;
            }

            // 判断是否是伪关键边
            uf = UnionFind(n);
            uf.unite(edges[i][0], edges[i][1]);
            v = edges[i][2];
            for (int j = 0; j < m; ++j)
            {
                if (i != j && uf.unite(edges[j][0], edges[j][1]))
                {
                    v += edges[j][2];
                }
            }
            if (v == value)
            {
                ans[1].push_back(edges[i][3]);
            }
        }

        return ans;
    }
};

// 并查集模板
class UnionFind
{
public:
    vector<int> parent;
    vector<int> size;
    int n;
    // 当前连通分量数目
    int setCount;

public:
    UnionFind(int _n) : n(_n), setCount(_n), parent(_n), size(_n, 1)
    {
        iota(parent.begin(), parent.end(), 0);
    }

    int findset(int x)
    {
        return parent[x] == x ? x : parent[x] = findset(parent[x]);
    }

    bool unite(int x, int y)
    {
        x = findset(x);
        y = findset(y);
        if (x == y)
        {
            return false;
        }
        if (size[x] < size[y])
        {
            swap(x, y);
        }
        parent[y] = x;
        size[x] += size[y];
        --setCount;
        return true;
    }

    bool connected(int x, int y)
    {
        x = findset(x);
        y = findset(y);
        return x == y;
    }
};

// Tarjan 算法求桥边模版
class TarjanSCC
{
private:
    const vector<vector<int>> &edges;
    const vector<vector<int>> &edgesId;
    vector<int> low;
    vector<int> dfn;
    vector<int> ans;
    int n;
    int ts;

private:
    void getCuttingEdge_(int u, int parentEdgeId)
    {
        low[u] = dfn[u] = ++ts;
        for (int i = 0; i < edges[u].size(); ++i)
        {
            int v = edges[u][i];
            int id = edgesId[u][i];
            if (dfn[v] == -1)
            {
                getCuttingEdge_(v, id);
                low[u] = min(low[u], low[v]);
                if (low[v] > dfn[u])
                {
                    ans.push_back(id);
                }
            }
            else if (id != parentEdgeId)
            {
                low[u] = min(low[u], dfn[v]);
            }
        }
    }

public:
    TarjanSCC(int n_, const vector<vector<int>> &edges_, const vector<vector<int>> &edgesId_) : edges(edges_), edgesId(edgesId_), low(n_, -1), dfn(n_, -1), n(n_), ts(-1) {}

    vector<int> getCuttingEdge()
    {
        for (int i = 0; i < n; ++i)
        {
            if (dfn[i] == -1)
            {
                getCuttingEdge_(i, -1);
            }
        }
        return ans;
    }
};

class Solution2 //连通性 + 最小生成树性质
{
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>> &edges)
    {
        int m = edges.size();
        for (int i = 0; i < m; ++i)
        {
            edges[i].push_back(i);
        }
        sort(edges.begin(), edges.end(), [](const auto &u, const auto &v)
             { return u[2] < v[2]; });

        UnionFind uf(n);
        vector<vector<int>> ans(2);
        vector<int> label(m);
        for (int i = 0; i < m;)
        {
            // 找出所有权值为 w 的边，下标范围为 [i, j)
            int w = edges[i][2];
            int j = i;
            while (j < m && edges[j][2] == edges[i][2])
            {
                ++j;
            }

            // 存储每个连通分量在图 G 中的编号
            unordered_map<int, int> compToId;
            // 图 G 的节点数
            int gn = 0;

            for (int k = i; k < j; ++k)
            {
                int x = uf.findset(edges[k][0]);
                int y = uf.findset(edges[k][1]);
                if (x != y)
                {
                    if (!compToId.count(x))
                    {
                        compToId[x] = gn++;
                    }
                    if (!compToId.count(y))
                    {
                        compToId[y] = gn++;
                    }
                }
                else
                {
                    // 将自环边标记为 -1
                    label[edges[k][3]] = -1;
                }
            }

            // 图 G 的边
            vector<vector<int>> gm(gn), gmid(gn);

            for (int k = i; k < j; ++k)
            {
                int x = uf.findset(edges[k][0]);
                int y = uf.findset(edges[k][1]);
                if (x != y)
                {
                    int idx = compToId[x], idy = compToId[y];
                    gm[idx].push_back(idy);
                    gmid[idx].push_back(edges[k][3]);
                    gm[idy].push_back(idx);
                    gmid[idy].push_back(edges[k][3]);
                }
            }

            vector<int> bridges = TarjanSCC(gn, gm, gmid).getCuttingEdge();
            // 将桥边（关键边）标记为 1
            for (int id : bridges)
            {
                ans[0].push_back(id);
                label[id] = 1;
            }

            for (int k = i; k < j; ++k)
            {
                uf.unite(edges[k][0], edges[k][1]);
            }

            i = j;
        }

        // 未标记的边即为非桥边（伪关键边）
        for (int i = 0; i < m; ++i)
        {
            if (!label[i])
            {
                ans[1].push_back(i);
            }
        }

        return ans;
    }
};

/*
* 关键边：最小生成树中删去某条边，会导致最小生成树的权值和增加
  解法：1. 该边必须出现在mst中
       2. 删除该边，重新构建mst则权值会和会改变
       注：有可能一开始给的图就是mst，即删除边后无法构建mst导致权值和反而变小
           正常情况就是该边是关键边，那么权值和会变大
* 伪关键边：可能会出现在某些最小生成树中但不会出现在所有最小生成树中的边
  解法：1. 可能出现在mst中
       2. 把该边一开始就加入最终生成树中，看最后权值不变则是伪关键边
       3. 且一定不是关键边
* 求最小生成树这里用克鲁斯卡尔，判断有无环用并查集
* 注意最后ans是在_edges的索引所以要提前存好索引以免排序就乱了
*/
class Solution3
{
    vector<vector<int>> edges;
    vector<int> parent;

public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>> &_edges)
    {
        edges.clear();
        int _edges_size = _edges.size();
        for (int i = 0; i < _edges_size; ++i)
        {
            edges.push_back(_edges.at(i));
            edges.at(i).push_back(i);
        }
        parent = vector<int>(n);
        //使用kruskal所以权值要按从小到大排序
        sort(edges.begin(), edges.end(), [](const vector<int> &A, const vector<int> &B)
             { return A.at(2) < B.at(2); });
        //求mst的最小权值和，因为没有删除的边就一个无意义的数组
        int mst_weight_sum = kruskal(n, {-1, -1, -1});
        //求关键边
        vector<int> key_edge = get_key_edge(n, mst_weight_sum);
        //求伪关键边，且伪关键边中不能有关键边
        unordered_set<int> key_edge_set(key_edge.begin(), key_edge.end());
        vector<int> fake_key_edge = get_fake_key_edge(n, mst_weight_sum, key_edge_set);
        return {key_edge, fake_key_edge};
    }
    void initialise(int n)
    {
        for (int i = 0; i < n; ++i)
            parent.at(i) = i;
    }
    int find_root(int i)
    {
        if (parent.at(i) != i)
        {
            int root = find_root(parent.at(i));
            parent.at(i) = root;
            return root;
        }
        return i;
    }
    bool union_vertices(int a, int b)
    {
        int a_root = find_root(a);
        int b_root = find_root(b);
        if (a_root == b_root)
            return false;
        parent.at(a_root) = b_root;
        return true;
    }
    int kruskal(int n, vector<int> delete_edge)
    {
        initialise(n);
        int weight_sum = 0;
        int cur_size = 0;
        for (vector<int> &i : edges)
        {
            if (i == delete_edge)
                continue;
            if (union_vertices(i.at(0), i.at(1)))
            {
                ++cur_size;
                weight_sum += i.at(2);
                if (cur_size == n - 1)
                    return weight_sum;
            }
        }
        return weight_sum;
    }
    vector<int> get_key_edge(int n, const int &mst_weight_sum)
    {
        vector<int> ans;
        for (vector<int> &i : edges)
        {
            int cur_weight_sum = kruskal(n, i);
            if (cur_weight_sum != mst_weight_sum)
                ans.push_back(i.at(3));
        }
        return ans;
    }
    vector<int> get_fake_key_edge(int n, const int &mst_weight_sum, unordered_set<int> &key_edge_set)
    {
        vector<int> ans;
        for (vector<int> &i : edges)
        {
            if (key_edge_set.find(i.at(3)) != key_edge_set.end())
                continue;
            int cur_weight_sum = add_one_edge_kruskal(n, i);
            if (cur_weight_sum == mst_weight_sum)
                ans.push_back(i.at(3));
        }
        return ans;
    }
    int add_one_edge_kruskal(int n, vector<int> add_edge)
    {
        initialise(n);
        union_vertices(add_edge.at(0), add_edge.at(1));
        int weight_sum = add_edge.at(2);
        int cur_size = 1;
        for (vector<int> &i : edges)
        {
            if (i == add_edge)
                continue;
            if (union_vertices(i.at(0), i.at(1)))
            {
                ++cur_size;
                weight_sum += i.at(2);
                if (cur_size == n - 1)
                    return weight_sum;
            }
        }
        return weight_sum;
    }
};