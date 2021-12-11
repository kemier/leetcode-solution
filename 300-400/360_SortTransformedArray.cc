#include <vector>
#include <algorithm>
#include <climits>

using namespace std;


class Solution {
public:
    vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {
        vector<int> ret;
        double DOUBLE_MAX = numeric_limits<double>::max();
        if(nums.size() == 0) {
            return ret;
        }
        if(a == 0) {        // transform directly
            for(int i = 0; i < nums.size(); ++i) {
                ret.push_back(b * nums[i] + c);
            }
            if(b < 0) {
                reverse(ret.begin(), ret.end());
            }
        }
        else {
            double axis = ((double)(-b)) / (2 * a);     // re sort accoring to the axis (-b / (2 * a))
            int upper = distance(nums.begin(), lower_bound(nums.begin(), nums.end(), axis));
            int lower = upper - 1;
            while(upper < nums.size() || lower >= 0) {
                double upper_differ = (upper == nums.size()) ? DOUBLE_MAX : abs(nums[upper] - axis);
                double lower_differ = (lower == -1) ? DOUBLE_MAX : abs(axis - nums[lower]);
                if(upper_differ < lower_differ) {
                    ret.push_back(nums[upper++]);
                }
                else {
                    ret.push_back(nums[lower--]);
                }
            }
            for(int i = 0; i < ret.size(); ++i) {       // transform after resorting
                ret[i] = a * ret[i] * ret[i] + b * ret[i] + c;
            }
            if(a < 0) {
                reverse(ret.begin(), ret.end());
            }
        }
        return ret;
    }
};