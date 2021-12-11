#include <unordered_map>
#include <vector>

using namespace std;


// Brutal Force
class Solution1 {
public:
    Solution1(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            mp[nums[i]].push_back(i);
        }
    }
    
    int pick(int target) {
        auto indices = mp[target];
        int r = rand() % indices.size();
        return indices[r];
    }

private:
    unordered_map<int, vector<int>> mp;
};

// 假设当前正要读取第n个数据，则我们以1/n的概率留下该数据，否则以(n-1)/n 的概率留下前n-1个数据中的一个。
// 而前n-1个数组留下的那个概率为1/(n-1), 因此最终留下上次n-1个数中留下的那个数的概率为[1/(n-1)]*[(n-1)/n] = 1/n,符合均匀分布的要求
class Solution2 {
public:
    Solution2(vector<int>& nums) {
        this->nums = nums;
    }
    
    int pick(int target) {
        int cnt = 0;
        int index = -1;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == target) {
                cnt++;
                if (rand() % cnt == 0) {
                    index = i; // 1/i prob
                }
            }
        }

        return index;
    }

private:
    vector<int> nums;
};


class Solution3 {
public:
    Solution3(vector<int>& nums) {
        begin = nums.begin();
        end = nums.end();
    }
    
    int pick(int target) {
        int index = -1;
        int cnt = 0;
        int i = 0;
        for (auto iter = begin; iter != end; iter++) {
            if (*iter == target) {
                cnt++;
                if (rand() % cnt == 0) {
                    index = i; // 1/i prob choose current index
                }
            }
            i++;
        }

        return index;
    }

private:
    vector<int>::iterator begin;
    vector<int>::iterator end;
};



