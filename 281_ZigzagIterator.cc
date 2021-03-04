
#include <vector>
#include <queue>
#include <utility>

using namespace std;

class ZigzagIterator
{
public:
    ZigzagIterator(vector<int> &v1, vector<int> &v2)
    {
        if (v1.size() != 0)
            que.push(make_pair(v1.begin(), v1.end()));
        if (v2.size() != 0)
            que.push(make_pair(v2.begin(), v2.end()));
    }

    int next()
    {
        int val = *que.front().first;
        auto it1 = que.front().first, it2 = que.front().second;
        if (it1 + 1 != it2)
            que.push(make_pair(it1 + 1, it2));
        que.pop();
        return val;
    }

    bool hasNext()
    {
        return !que.empty();
    }

private:
    queue<pair<vector<int>::iterator, vector<int>::iterator>> que;
};
