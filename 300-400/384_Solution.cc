#include <vector>
#include <stdlib.h>
#include <algorithm>

using namespace std;


class Solution {
public:
    vector<int>original;
    Solution(vector<int>& nums) {
        original=nums;
    }
    
    vector<int> reset() {
        return original;
    }

    vector<int> shuffle() {
        vector<int>ans(original);
        int i=ans.size()-1;
        while(i>=0){
            swap(ans[i],ans[rand()%(i+1)]);
            i--;
        }
        return ans;
    }
};

