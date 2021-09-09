#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution //哈希表 O(m+n)  O(min(m,n))
{
public:
    vector<int> intersect(vector<int> &nums1, vector<int> &nums2)
    {
        if (nums1.size() > nums2.size())
        {
            return intersect(nums2, nums1);
        }
        unordered_map<int, int> m;
        for (int num : nums1)
        {
            ++m[num];
        }
        vector<int> intersection;
        for (int num : nums2)
        {
            if (m.count(num))
            {
                intersection.push_back(num);
                --m[num];
                if (m[num] == 0)
                {
                    m.erase(num);
                }
            }
        }
        return intersection;
    }
};

class Solution2 //排序+双指针 O(mlogm+nlogn) O(min(m,n))
{
public:
    vector<int> intersect(vector<int> &nums1, vector<int> &nums2)
    {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        int length1 = nums1.size(), length2 = nums2.size();
        vector<int> intersection;
        int index1 = 0, index2 = 0;
        while (index1 < length1 && index2 < length2)
        {
            if (nums1[index1] < nums2[index2])
            {
                index1++;
            }
            else if (nums1[index1] > nums2[index2])
            {
                index2++;
            }
            else
            {
                intersection.push_back(nums1[index1]);
                index1++;
                index2++;
            }
        }
        return intersection;
    }
};
