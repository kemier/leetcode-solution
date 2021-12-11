#include <map>
#include <vector>

using namespace std;

class SummaryRanges
{
public:
    map<int, int> RL; //[1, 3]     L[1] = 3
    map<int, int> LR; //[1, 3]     R[3] = 1

    /** Initialize your data structure here. */
    SummaryRanges()
    {
    }

    void addNum(int val)
    {
        //----- 先看val是否已经存在了
        if (RL.size() > 0)
        {
            auto it = RL.lower_bound(val); //第一个 ≥ val的位置
            if (it != RL.end())            // val=2 插到区间[1,3]
            {
                int section_L = it->second; //区间左端
                if (section_L <= val)
                    return;
            }
        }
        //----- val没存在
        int l = RL.count(val - 1); //val-1作为一个区间的R端点，被记录在L.keys()中
        int r = LR.count(val + 1); //val+1作为一个区间的L端点。被记录在R.keys()中
        if (l == 1 && r == 1)
        {
            int section_1_L = RL[val - 1]; //[区间1_L, val - 1] val [val+1, 区间2_R]
            int section_2_R = LR[val + 1];
            RL[section_2_R] = section_1_L;
            LR[section_1_L] = section_2_R;
            RL.erase(val - 1);
            LR.erase(val + 1);
        }
        else if (l == 1 && r == 0) //[区间1_L, val - 1] val
        {
            int section_1_L = RL[val - 1];
            RL[val] = section_1_L;
            LR[section_1_L] = val;
            RL.erase(val - 1);
        }
        else if (l == 0 && r == 1) //val [val+1, 区间2_R]
        {
            int section_2_R = LR[val + 1];
            LR[val] = section_2_R;
            RL[section_2_R] = val;
            LR.erase(val + 1);
        }
        else // val
        {
            RL[val] = val;
            LR[val] = val;
        }
    }

    vector<vector<int>> getIntervals()
    {
        vector<vector<int>> res;
        for (auto [r, l] : RL)
            res.push_back({l, r});
        return res;
    }
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges* obj = new SummaryRanges();
 * obj->addNum(val);
 * vector<vector<int>> param_2 = obj->getIntervals();
 */

class SummaryRanges2
{
public:
    /** Initialize your data structure here. */
    SummaryRanges2()
    {
    }

    void addNum(int val)
    {
        // 先用lower_bound找到val是否已覆盖，覆盖则直接忽略即可
        if (!right2left.empty())
        {
            // right >= val的下边界
            auto iter = right2left.lower_bound(val);
            if (iter != right2left.end())
            {
                if (iter->second <= val)
                {
                    return;
                }
            }
        }

        // val没被覆盖的情况，需要分类来讨论
        // 先找到val-1 和 val+1 找到可能的左右边界，这里直接用计数来判断
        int l = right2left.count(val - 1);
        int r = left2right.count(val + 1);
        // l=1,r=1:  这种情况可以扩展把两个区间连成一个更大的区间
        if (l == 1 && r == 1)
        {
            int newL = right2left[val - 1];
            int newR = left2right[val + 1];
            right2left[newR] = newL;
            left2right[newL] = newR;
            right2left.erase(val - 1);
            left2right.erase(val + 1);
        }
        // l=1,r=0: 扩展它的右边界 *~val
        else if (l == 1 && r == 0)
        {
            int newL = right2left[val - 1];
            right2left[val] = newL;
            left2right[newL] = val;
            // 坑：一定要移除right2left的val-1
            right2left.erase(val - 1);
        }
        // l=0,r=1: 扩展它的左边界 val~*
        else if (l == 0 && r == 1)
        {
            int newR = left2right[val + 1];
            left2right[val] = newR;
            right2left[newR] = val;
            // 坑：一定要移除 left2right 的val+1
            left2right.erase(val + 1);
        }
        // l=0,r=0: 都不存在的情况，直接加一个即可
        else
        {
            left2right[val] = val;
            right2left[val] = val;
        }
    }

    vector<vector<int>> getIntervals()
    {
        // 直接从 right2left 取出各个映射即范围即可
        vector<vector<int>> res;
        for (auto iter = right2left.begin(); iter != right2left.end(); ++iter)
        {
            // 注意这里要反一下插入left和right
            res.push_back({iter->second, iter->first});
        }
        return res;
    }

private:
    // 两个辅助map用于快速查找，同时它也是天然排序的
    // 左边界到右边界的映射
    map<int, int> left2right;
    // 右边界到左边界的映射
    map<int, int> right2left;
};
