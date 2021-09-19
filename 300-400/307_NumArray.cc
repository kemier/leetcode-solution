#include <vector>

using namespace std;

class NumArray
{
public:
    NumArray(vector<int> &nums)
    {
        if (nums.size() > 0)
        {
            int n = nums.size();
            tree = (int *)malloc(n * 2);
            buildTree(nums);
        }
    }

    void update(int pos, int val)
    {
        pos += n;
        tree[pos] = val;
        while (pos > 0)
        {
            int left = pos;
            int right = pos;
            if (pos % 2 == 0)
            {
                right = pos + 1;
            }
            else
            {
                left = pos - 1;
            }
            // parent is updated after child is updated
            tree[pos / 2] = tree[left] + tree[right];
            pos /= 2;
        }
    }

    int sumRange(int l, int r)
    {
        // get leaf with value 'l'
        l += n;
        // get leaf with value 'r'
        r += n;
        int sum = 0;
        while (l <= r)
        {
            if ((l % 2) == 1)
            {
                sum += tree[l];
                l++;
            }
            if ((r % 2) == 0)
            {
                sum += tree[r];
                r--;
            }
            l /= 2;
            r /= 2;
        }
        return sum;
    }

private:
    int *tree;
    long n;

    void buildTree(vector<int> nums)
    {
        for (int i = n, j = 0; i < 2 * n; i++, j++)
            tree[i] = nums[j];
        for (int i = n - 1; i > 0; --i)
            tree[i] = tree[i * 2] + tree[i * 2 + 1];
    }
};