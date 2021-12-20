#include <vector>

using namespace std;

class Solution
{
private:
    vector<int> c;
    vector<int> a;

    void Init(int length)
    {
        c.resize(length, 0);
    }

    int LowBit(int x)
    {
        return x & (-x);
    }

    void Update(int pos)
    {
        while (pos < c.size())
        {
            c[pos] += 1;
            pos += LowBit(pos);
        }
    }

    int Query(int pos)
    {
        int ret = 0;

        while (pos > 0)
        {
            ret += c[pos];
            pos -= LowBit(pos);
        }

        return ret;
    }

    void Discretization(vector<int> &nums)
    {
        a.assign(nums.begin(), nums.end());
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
    }

    int getId(int x)
    {
        return lower_bound(a.begin(), a.end(), x) - a.begin() + 1;
    }

public:
    vector<int> countSmaller(vector<int> &nums)
    {
        vector<int> resultList;

        Discretization(nums);

        Init(nums.size() + 5);

        for (int i = (int)nums.size() - 1; i >= 0; --i)
        {
            int id = getId(nums[i]);
            resultList.push_back(Query(id - 1));
            Update(id);
        }

        reverse(resultList.begin(), resultList.end());

        return resultList;
    }
};

class Solution2 //二分查找
{
public:
    vector<int> countSmaller(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
            return {};

        // ordered_arr存储排序后的有序数组
        vector<int> ordered_arr, res(n, 0);
        for (int i = n - 1; i >= 0; i--)
        {
            int l = 0, r = ordered_arr.size();
            while (l < r)
            {
                int mid = l + ((r - l) >> 1);
                if (nums[i] > ordered_arr[mid])
                    l = mid + 1;
                else
                    r = mid;
            }
            // r即插入ordered_arr的位置，也是在其右侧比其小的元素个数
            res[i] = r;
            // 倒序逐个插入元素
            ordered_arr.insert(ordered_arr.begin() + r, nums[i]);
        }
        return res;
    }
};

class Solution3 // STL lower_bound
{
public:
    vector<int> countSmaller(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
            return {};

        // ordered_arr存储排序后的有序数组
        vector<int> ordered_arr, res;

        for (int i = n - 1; i >= 0; i--)
        {
            // 通过lower_bound()函数得到在ordered_arr中的index
            auto index = lower_bound(ordered_arr.begin(), ordered_arr.end(), nums[i]);
            // count记录在nums[i]右侧且比nums[i]小的元素个数
            int count = index - ordered_arr.begin();
            // 倒序逐个插入元素
            ordered_arr.insert(index, nums[i]);
            // 插入count值
            res.push_back(count);
        }
        // 由于数组是从后向前遍历的，所以还需要反转数组
        reverse(res.begin(), res.end());
        return res;
    }
};

struct BSTNode
{
    int val;   // 值
    int count; // 当前节点的左子树节点个数
    BSTNode *left;
    BSTNode *right;
    BSTNode(int x) : val(x), left(NULL), right(NULL), count(0) {}
};

void BST_insert(BSTNode *node, BSTNode *insert_node, int &num)
{
    if (node->val >= insert_node->val)
    {
        // 插入的结点比当前节点值小
        node->count++;
        if (node->left)
            // 左子树不空
            BST_insert(node->left, insert_node, num);
        else
            // 左子树空
            node->left = insert_node;
    }
    else
    {
        // 插入的结点比当前节点值大
        num += node->count + 1;
        if (node->right)
            // 右子树不空
            BST_insert(node->right, insert_node, num);
        else
            // 右子树空
            node->right = insert_node;
    }
}

class Solution4 //二叉搜索/排序树
{
public:
    vector<int> countSmaller(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
            return {};
        vector<int> count;
        // 比数组最右边元素小的且在其右边的元素个数 = 0
        count.push_back(0);

        // 建立BST的根节点
        BSTNode *node = new BSTNode(nums[n - 1]);

        for (int i = 1; i < n; i++)
        {
            // 记录比当前节点小的节点个数
            int num = 0;
            BSTNode *insert_node = new BSTNode(nums[n - i - 1]);
            BST_insert(node, insert_node, num);
            count.push_back(num);
        }
        delete node;
        // 由于BST是从数组倒序插入的，所以还需要反转数组
        reverse(count.begin(), count.end());
        return count;
    }
};

class Solution5 //归并排序
{
public:
    // 记录下标
    vector<int> index;
    vector<int> temp;

    void merge(vector<int> &nums, int l, int r, vector<int> &res)
    {
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        merge(nums, l, mid, res);
        merge(nums, mid + 1, r, res);

        // 若数组本身有序，则提前终止
        if (nums[index[mid]] <= nums[index[mid + 1]])
            return;

        // 只需要赋值 index 数组的 [l, r] 这个子区间里的值
        for (int i = l; i <= r; ++i)
            temp[i] = index[i];

        int li = l;
        int ri = mid + 1;
        int j = l;

        while (li <= mid || ri <= r)
        {
            if (li > mid || (ri <= r && nums[temp[li]] > nums[temp[ri]]))
            {
                index[j] = temp[ri];
                j++;
                ri++;
            }
            else
            {
                index[j] = temp[li];
                j++;
                if (li <= mid)
                    res[temp[li]] += ri - mid - 1;
                li++;
            }
        }
    }

    vector<int> countSmaller(vector<int> &nums)
    {
        if (!nums.size())
            return {};

        vector<int> res(nums.size(), 0);

        for (int i = 0; i < nums.size(); i++)
        {
            temp.push_back(0);
            index.push_back(i);
        }

        merge(nums, 0, nums.size() - 1, res);
        return res;
    }
};
