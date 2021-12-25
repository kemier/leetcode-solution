#include <vector>
#include <algorithm>

using namespace std;

class Solution //快速排序
{
    int partition(vector<int> &nums, int l, int r)
    {
        int pivot = nums[r];
        int i = l - 1;
        for (int j = l; j <= r - 1; ++j)
        {
            if (nums[j] <= pivot)
            {
                i = i + 1;
                swap(nums[i], nums[j]);
            }
        }
        swap(nums[i + 1], nums[r]);
        return i + 1;
    }
    int randomized_partition(vector<int> &nums, int l, int r)
    {
        int i = rand() % (r - l + 1) + l; // 随机选一个作为我们的主元
        swap(nums[r], nums[i]);
        return partition(nums, l, r);
    }
    void randomized_quicksort(vector<int> &nums, int l, int r)
    {
        if (l < r)
        {
            int pos = randomized_partition(nums, l, r);
            randomized_quicksort(nums, l, pos - 1);
            randomized_quicksort(nums, pos + 1, r);
        }
    }

public:
    vector<int> sortArray(vector<int> &nums)
    {
        srand((unsigned)time(NULL));
        randomized_quicksort(nums, 0, (int)nums.size() - 1);
        return nums;
    }
};

class Solution2 //堆排序
{
    void maxHeapify(vector<int> &nums, int i, int len)
    {
        for (; (i << 1) + 1 <= len;)
        {
            int lson = (i << 1) + 1;
            int rson = (i << 1) + 2;
            int large;
            if (lson <= len && nums[lson] > nums[i])
            {
                large = lson;
            }
            else
            {
                large = i;
            }
            if (rson <= len && nums[rson] > nums[large])
            {
                large = rson;
            }
            if (large != i)
            {
                swap(nums[i], nums[large]);
                i = large;
            }
            else
            {
                break;
            }
        }
    }
    void buildMaxHeap(vector<int> &nums, int len)
    {
        for (int i = len / 2; i >= 0; --i)
        {
            maxHeapify(nums, i, len);
        }
    }
    void heapSort(vector<int> &nums)
    {
        int len = (int)nums.size() - 1;
        buildMaxHeap(nums, len);
        for (int i = len; i >= 1; --i)
        {
            swap(nums[i], nums[0]);
            len -= 1;
            maxHeapify(nums, 0, len);
        }
    }

public:
    vector<int> sortArray(vector<int> &nums)
    {
        heapSort(nums);
        return nums;
    }
};

class Solution3 //归并排序
{
    vector<int> tmp;
    void mergeSort(vector<int> &nums, int l, int r)
    {
        if (l >= r)
            return;
        int mid = (l + r) >> 1;
        mergeSort(nums, l, mid);
        mergeSort(nums, mid + 1, r);
        int i = l, j = mid + 1;
        int cnt = 0;
        while (i <= mid && j <= r)
        {
            if (nums[i] <= nums[j])
            {
                tmp[cnt++] = nums[i++];
            }
            else
            {
                tmp[cnt++] = nums[j++];
            }
        }
        while (i <= mid)
        {
            tmp[cnt++] = nums[i++];
        }
        while (j <= r)
        {
            tmp[cnt++] = nums[j++];
        }
        for (int i = 0; i < r - l + 1; ++i)
        {
            nums[i + l] = tmp[i];
        }
    }

public:
    vector<int> sortArray(vector<int> &nums)
    {
        tmp.resize((int)nums.size(), 0);
        mergeSort(nums, 0, (int)nums.size() - 1);
        return nums;
    }
};

class Solution4 //基数排序
{
public:
    vector<int> sortArray(vector<int> &nums)
    {
        int n = nums.size();
        int max = abs(nums[0]);
        for (int i = 1; i < n; i++)
        {
            if (max < abs(nums[i]))
                max = abs(nums[i]);
        }
        int w = 0;
        while (max > 0)
        {
            max /= 10;
            w++;
        }
        int flag = 1;
        vector<int> ans(n);
        for (int i = 0; i < w; i++)
        {
            vector<int> bucket(19, 0);
            for (int j = 0; j < n; j++)
            {
                int temp = nums[j] / flag % 10 + 9;
                bucket[temp]++;
            }
            for (int j = 1; j < 19; j++)
                bucket[j] += bucket[j - 1];
            for (int j = n - 1; j >= 0; j--)
            {
                int temp = nums[j] / flag % 10 + 9;
                ans[--bucket[temp]] = nums[j];
            }
            nums.swap(ans);
            flag *= 10;
        }
        return nums;
    }
};

class Solution5 //计数排序
{
public:
    vector<int> sortArray(vector<int> &nums)
    {
        int n = nums.size();
        int max = nums[0], min = nums[0];
        for (int i = 1; i < n; i++)
        {
            if (nums[i] > max)
                max = nums[i];
            if (nums[i] < min)
                min = nums[i];
        }
        vector<int> count(max - min + 1, 0);
        for (int i = 0; i < n; i++)
            count[nums[i] - min]++;
        int k = 0;
        for (int i = 0; i < max - min + 1; i++)
        {
            while (count[i]--)
            {
                nums[k++] = i + min;
            }
        }
        return nums;
    }
};
