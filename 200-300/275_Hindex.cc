#include <vector>
using namespace std;

class Solution
{
public:
    int hIndex(vector<int> citations)
    {
        int n = citations.size();
        for (int h = n; h > 0; h--)
        {
            if (citations[n - h] >= h)
            {
                return h;
            }
        }
        return 0;
    }
};

class Solution2 //二分搜索  时间复杂度:O(logN)  空间复杂度:O(1)
{
public:
    int hIndex(vector<int> citations)
    {
        int idx = 0, n = citations.szie();
        int pivot, left = 0, right = n - 1;
        while (left <= right)
        {
            pivot = left + (right - left) / 2;
            if (citations[pivot] == n - pivot)
                return n - pivot;
            else if (citations[pivot] < n - pivot)
                left = pivot + 1;
            else
                right = pivot - 1;
        }
        return n - left;
    }
}
