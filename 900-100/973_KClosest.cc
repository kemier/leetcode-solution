#include <vector>
#include <algorithm>
#include <queue>
#include <random>

using namespace std;

class Solution //排序
{
public:
    vector<vector<int>> kClosest(vector<vector<int>> &points, int k)
    {
        sort(points.begin(), points.end(), [](const vector<int> &u, const vector<int> &v)
             { return u[0] * u[0] + u[1] * u[1] < v[0] * v[0] + v[1] * v[1]; });
        return {points.begin(), points.begin() + k};
    }
};

class Solution2 //堆
{
public:
    vector<vector<int>> kClosest(vector<vector<int>> &points, int k)
    {
        priority_queue<pair<int, int>> q;
        for (int i = 0; i < k; ++i)
        {
            q.emplace(points[i][0] * points[i][0] + points[i][1] * points[i][1], i);
        }
        int n = points.size();
        for (int i = k; i < n; ++i)
        {
            int dist = points[i][0] * points[i][0] + points[i][1] * points[i][1];
            if (dist < q.top().first)
            {
                q.pop();
                q.emplace(dist, i);
            }
        }
        vector<vector<int>> ans;
        while (!q.empty())
        {
            ans.push_back(points[q.top().second]);
            q.pop();
        }
        return ans;
    }
};

class Solution3 //快速选择   nth_element
{
private:
    mt19937 gen{random_device{}()};

public:
    void random_select(vector<vector<int>> &points, int left, int right, int k)
    {
        int pivot_id = uniform_int_distribution<int>{left, right}(gen);
        int pivot = points[pivot_id][0] * points[pivot_id][0] + points[pivot_id][1] * points[pivot_id][1];
        swap(points[right], points[pivot_id]);
        int i = left - 1;
        for (int j = left; j < right; ++j)
        {
            int dist = points[j][0] * points[j][0] + points[j][1] * points[j][1];
            if (dist <= pivot)
            {
                ++i;
                swap(points[i], points[j]);
            }
        }
        ++i;
        swap(points[i], points[right]);
        // [left, i-1] 都小于等于 pivot, [i+1, right] 都大于 pivot
        if (k < i - left + 1)
        {
            random_select(points, left, i - 1, k);
        }
        else if (k > i - left + 1)
        {
            random_select(points, i + 1, right, k - (i - left + 1));
        }
    }

    vector<vector<int>> kClosest(vector<vector<int>> &points, int k)
    {
        int n = points.size();
        random_select(points, 0, n - 1, k);
        return {points.begin(), points.begin() + k};
    }
};
