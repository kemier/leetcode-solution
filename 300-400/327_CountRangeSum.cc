#include <vector>
#include <set>
#include <unordered_map>
#include <climits>
#include <algorithm>
#include <random>



using namespace std;

class Solution {//归并排序
public:
    int countRangeSumRecursive(vector<long>& sum, int lower, int upper, int left, int right) {
        if (left == right) {
            return 0;
        } else {
            int mid = (left + right) / 2;
            int n1 = countRangeSumRecursive(sum, lower, upper, left, mid);
            int n2 = countRangeSumRecursive(sum, lower, upper, mid + 1, right);
            int ret = n1 + n2;

            // 首先统计下标对的数量
            int i = left;
            int l = mid + 1;
            int r = mid + 1;
            while (i <= mid) {
                while (l <= right && sum[l] - sum[i] < lower) l++;
                while (r <= right && sum[r] - sum[i] <= upper) r++;
                ret += (r - l);
                i++;
            }

            // 随后合并两个排序数组
            vector<long> sorted(right - left + 1);
            int p1 = left, p2 = mid + 1;
            int p = 0;
            while (p1 <= mid || p2 <= right) {
                if (p1 > mid) {
                    sorted[p++] = sum[p2++];
                } else if (p2 > right) {
                    sorted[p++] = sum[p1++];
                } else {
                    if (sum[p1] < sum[p2]) {
                        sorted[p++] = sum[p1++];
                    } else {
                        sorted[p++] = sum[p2++];
                    }
                }
            }
            for (int i = 0; i < sorted.size(); i++) {
                sum[left + i] = sorted[i];
            }
            return ret;
        }
    }

    int countRangeSum(vector<int>& nums, int lower, int upper) {
        long s = 0;
        vector<long> sum{0};
        for(auto& v: nums) {
            s += v;
            sum.push_back(s);
        }
        return countRangeSumRecursive(sum, lower, upper, 0, sum.size() - 1);
    }
};


struct SegNode {
    int lo, hi, add;
    SegNode* lchild, *rchild;
    SegNode(int left, int right): lo(left), hi(right), add(0), lchild(nullptr), rchild(nullptr) {}
};

class Solution2 { //线段树
public:
    SegNode* build(int left, int right) {
        SegNode* node = new SegNode(left, right);
        if (left == right) {
            return node;
        }
        int mid = (left + right) / 2;
        node->lchild = build(left, mid);
        node->rchild = build(mid + 1, right);
        return node;
    }

    void insert(SegNode* root, int val) {
        root->add++;
        if (root->lo == root->hi) {
            return;
        }
        int mid = (root->lo + root->hi) / 2;
        if (val <= mid) {
            insert(root->lchild, val);
        }
        else {
            insert(root->rchild, val);
        }
    }

    int count(SegNode* root, int left, int right) const {
        if (left > root->hi || right < root->lo) {
            return 0;
        }
        if (left <= root->lo && root->hi <= right) {
            return root->add;
        }
        return count(root->lchild, left, right) + count(root->rchild, left, right);
    }

    int countRangeSum(vector<int>& nums, int lower, int upper) {
        long long sum = 0;
        vector<long long> preSum = {0};
        for (int v: nums) {
            sum += v;
            preSum.push_back(sum);
        }
        
        set<long long> allNumbers;
        for (long long x: preSum) {
            allNumbers.insert(x);
            allNumbers.insert(x - lower);
            allNumbers.insert(x - upper);
        }
        // 利用哈希表进行离散化
        unordered_map<long long, int> values;
        int idx = 0;
        for (long long x: allNumbers) {
            values[x] = idx;
            idx++;
        }

        SegNode* root = build(0, values.size() - 1);
        int ret = 0;
        for (long long x: preSum) {
            int left = values[x - upper], right = values[x - lower];
            ret += count(root, left, right);
            insert(root, values[x]);
        }
        return ret;
    }
};


struct SegNode {
    long long lo, hi;
    int add;
    SegNode* lchild, *rchild;
    SegNode(long long left, long long right): lo(left), hi(right), add(0), lchild(nullptr), rchild(nullptr) {}
};

class Solution3 {
public:
    void insert(SegNode* root, long long val) {
        root->add++;
        if (root->lo == root->hi) {
            return;
        }
        long long mid = (root->lo + root->hi) >> 1;
        if (val <= mid) {
            if (!root->lchild) {
                root->lchild = new SegNode(root->lo, mid);
            }
            insert(root->lchild, val);
        }
        else {
            if (!root->rchild) {
                root->rchild = new SegNode(mid + 1, root->hi);
            }
            insert(root->rchild, val);
        }
    }

    int count(SegNode* root, long long left, long long right) const {
        if (!root) {
            return 0;
        }
        if (left > root->hi || right < root->lo) {
            return 0;
        }
        if (left <= root->lo && root->hi <= right) {
            return root->add;
        }
        return count(root->lchild, left, right) + count(root->rchild, left, right);
    }

    int countRangeSum(vector<int>& nums, int lower, int upper) {
        long long sum = 0;
        vector<long long> preSum = {0};
        for(int v: nums) {
            sum += v;
            preSum.push_back(sum);
        }
        
        long long lbound = LLONG_MAX, rbound = LLONG_MIN;
        for (long long x: preSum) {
            lbound = min({lbound, x, x - lower, x - upper});
            rbound = max({rbound, x, x - lower, x - upper});
        }
        
        SegNode* root = new SegNode(lbound, rbound);
        int ret = 0;
        for (long long x: preSum) {
            ret += count(root, x - upper, x - lower);
            insert(root, x);
        }
        return ret;
    }
};

class BIT {
private:
    vector<int> tree;
    int n;

public:
    BIT(int _n): n(_n), tree(_n + 1) {}

    static constexpr int lowbit(int x) {
        return x & (-x);
    }

    void update(int x, int d) {
        while (x <= n) {
            tree[x] += d;
            x += lowbit(x);
        }
    }

    int query(int x) const {
        int ans = 0;
        while (x) {
            ans += tree[x];
            x -= lowbit(x);
        }
        return ans;
    }
};

class Solution4 {//树状数组
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        long long sum = 0;
        vector<long long> preSum = {0};
        for (int v: nums) {
            sum += v;
            preSum.push_back(sum);
        }
        
        set<long long> allNumbers;
        for (long long x: preSum) {
            allNumbers.insert(x);
            allNumbers.insert(x - lower);
            allNumbers.insert(x - upper);
        }
        // 利用哈希表进行离散化
        unordered_map<long long, int> values;
        int idx = 0;
        for (long long x: allNumbers) {
            values[x] = idx;
            idx++;
        }

        int ret = 0;
        BIT bit(values.size());
        for (int i = 0; i < preSum.size(); i++) {
            int left = values[preSum[i] - upper], right = values[preSum[i] - lower];
            ret += bit.query(right + 1) - bit.query(left);
            bit.update(values[preSum[i]] + 1, 1);
        }
        return ret;
    }
};

class BalancedTree {
private:
    struct BalancedNode {
        long long val;
        long long seed;
        int count;
        int size;
        BalancedNode* left;
        BalancedNode* right;

        BalancedNode(long long _val, long long _seed): val(_val), seed(_seed), count(1), size(1), left(nullptr), right(nullptr) {}

        BalancedNode* left_rotate() {
            int prev_size = size;
            int curr_size = (left ? left->size : 0) + (right->left ? right->left->size : 0) + count;
            BalancedNode* root = right;
            right = root->left;
            root->left = this;
            root->size = prev_size;
            size = curr_size;
            return root;
        }

        BalancedNode* right_rotate() {
            int prev_size = size;
            int curr_size = (right ? right->size : 0) + (left->right ? left->right->size : 0) + count;
            BalancedNode* root = left;
            left = root->right;
            root->right = this;
            root->size = prev_size;
            size = curr_size;
            return root;
        }
    };

private:
    BalancedNode* root;
    int size;
    mt19937 gen;
    uniform_int_distribution<long long> dis;

private:
    BalancedNode* insert(BalancedNode* node, long long x) {
        if (!node) {
            return new BalancedNode(x, dis(gen));
        }
        ++node->size;
        if (x < node->val) {
            node->left = insert(node->left, x);
            if (node->left->seed > node->seed) {
                node = node->right_rotate();
            }
        }
        else if (x > node->val) {
            node->right = insert(node->right, x);
            if (node->right->seed > node->seed) {
                node = node->left_rotate();
            }
        }
        else {
            ++node->count;
        }
        return node;
    }

public:
    BalancedTree(): root(nullptr), size(0), gen(random_device{}()), dis(LLONG_MIN, LLONG_MAX) {}

    long long get_size() const {
        return size;
    }

    void insert(long long x) {
        ++size;
        root = insert(root, x);
    }

    long long lower_bound(long long x) const {
        BalancedNode* node = root;
        long long ans = LLONG_MAX;
        while (node) {
            if (x == node->val) {
                return x;
            }
            if (x < node->val) {
                ans = node->val;
                node = node->left;
            }
            else {
                node = node->right;
            }
        }
        return ans;
    }

    long long upper_bound(long long x) const {
        BalancedNode* node = root;
        long long ans = LLONG_MAX;
        while (node) {
            if (x < node->val) {
                ans = node->val;
                node = node->left;
            }
            else {
                node = node->right;
            }
        }
        return ans;
    }

    pair<int, int> rank(long long x) const {
        BalancedNode* node = root;
        int ans = 0;
        while (node) {
            if (x < node->val) {
                node = node->left;
            }
            else {
                ans += (node->left ? node->left->size : 0) + node->count;
                if (x == node->val) {
                    return {ans - node->count + 1, ans};
                }
                node = node->right;
            }
        }
        return {INT_MIN, INT_MAX};
    }
};

class Solution5 {//平衡二叉搜索树
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        long long sum = 0;
        vector<long long> preSum = {0};
        for (int v: nums) {
            sum += v;
            preSum.push_back(sum);
        }
        
        BalancedTree* treap = new BalancedTree();
        int ret = 0;
        for (long long x: preSum) {
            long long numLeft = treap->lower_bound(x - upper);
            int rankLeft = (numLeft == LLONG_MAX ? treap->get_size() + 1 : treap->rank(numLeft).first);
            long long numRight = treap->upper_bound(x - lower);
            int rankRight = (numRight == LLONG_MAX ? treap->get_size() : treap->rank(numRight).first - 1);
            ret += (rankRight - rankLeft + 1);
            treap->insert(x);
        }
        return ret;
    }
};

