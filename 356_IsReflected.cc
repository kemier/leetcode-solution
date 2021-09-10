#include <set>
#include <vector>
#include <climits>

using namespace std;


class Solution {
public:
    bool isReflected(vector<pair<int, int>>& points) {
        set<pair<int, int>> st;
        int Min = INT_MAX, Max = INT_MIN;
        for(auto val: points)
        {
            Min = min(Min, val.first), Max = max(Max, val.first);
            st.insert(val);
        }
        int sum = Min + Max;
        for(auto val: points)
            if(st.count(make_pair(sum-val.first, val.second))==0) return false;
        return true;
    }
};