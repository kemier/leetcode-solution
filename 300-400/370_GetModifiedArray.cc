#include <vector>

using namespace std;

class Solution {
public:
    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
        vector<int> ans(length, 0);
        for(auto vec1: updates)
        {
            int left = vec1[0], right = vec1[1], val = vec1[2];
            ans[left] += val;
            if(right+1 < length) ans[right+1] -= val;
        }
        for(int i = 0, sum = 0; i < length; i++)
        {
            sum += ans[i];
            ans[i] = sum;
        }
        return ans;
    }
};