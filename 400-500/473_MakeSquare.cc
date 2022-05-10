#include <bits/stdc++.h>

using namespace std;

class Solution // DFS timeout
{

private:
    int possibleSquareSide;
    vector<int> nums;
    vector<int> sums;

public:
    // Depth First Search function.
    bool dfs(int index)
    {

        // If we have exhausted all our matchsticks, check if all sides of the square are of equal length
        if (index == nums.size())
        {
            return sums[0] == sums[1] && sums[1] == sums[2] && sums[2] == sums[3];
        }

        // Get current matchstick.
        int element = nums[index];

        // Try adding it to each of the 4 sides (if possible)
        for (int i = 0; i < 4; i++)
        {
            if (sums[i] + element <= possibleSquareSide)
            {
                sums[i] += element;
                if (dfs(index + 1))
                {
                    return true;
                }
                sums[i] -= element;
            }
        }

        return false;
    }

    bool makesquare(vector<int> arr)
    {
        // Empty matchsticks.
        if (arr.size() == 0)
        {
            return false;
        }

        nums.reserve(arr.size());
        nums.swap(arr);
        sums.reserve(4);
        // Find the perimeter of the square (if at all possible)
        int L = nums.size();
        int perimeter = 0;
        for (int i = 0; i < L; i++)
        {
            perimeter += nums[i];
        }

        possibleSquareSide = perimeter / 4;
        if (possibleSquareSide * 4 != perimeter)
        {
            return false;
        }

        sort(nums.begin(), nums.end(), less<int>());
        return dfs(0);
    }
};

class Solution2 //DFS+Pruning
{
public:
    bool dfs(vector<int> &matchsticks, int ind, int *arr)
    {
        if (ind == matchsticks.size())
        {
            for (int i = 0; i < 4; i++)
            {
                if (arr[i] != 0)
                    return false;
            }
            return true;
        }
        for (int i = 0; i < 4; i++)
        {
            if (ind >= i)
            { //剪枝
                if (arr[i] >= matchsticks[ind])
                {
                    arr[i] -= matchsticks[ind];
                    if (dfs(matchsticks, ind + 1, arr))
                        return true;
                    arr[i] += matchsticks[ind];
                }
            }
        }
        return false;
    }

    bool makesquare(vector<int> &matchsticks)
    {
        int nsum = 0;
        for (auto x : matchsticks)
            nsum += x;
        if (nsum % 4 != 0)
            return false;
        int arr[4] = {nsum / 4, nsum / 4, nsum / 4, nsum / 4};
        return dfs(matchsticks, 0, arr);
    }
};

int main()
{
    Solution s;
    vector<int> nums = {4, 4, 10, 7, 5, 3, 9, 10, 6, 6, 5, 10, 5, 7, 5};
    cout << s.makesquare(nums) << endl;
    return 0;
}