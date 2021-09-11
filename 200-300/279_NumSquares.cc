#include <vector>
#include <cmath>
#include <climits>
#include <iostream>
#include <set>

using namespace std;

class Solution //n过大超出时间限制
{
public:
    int numSquares(int n)
    {
        findSquareNum(n);
        return minNumSquares(n);
    }
    int minNumSquares(int k)
    {
        int new_num = INT_MAX, min_num = INT_MAX;
        //bottom cases:find a square number
        for (int i = 0; i < square_num.size(); i++)
        {
            if (k == square_num[i])
                return 1;
        }

        for (int i = 0; i < square_num.size(); i++)
        {
            int square = square_num[i];
            if (k < square)
                break;
            new_num = minNumSquares(k - square) + 1;
            min_num = min(min_num, new_num);
        }
        return min_num;
    }

    void findSquareNum(int n)
    {
        square_num.reserve(int(sqrt(n)));
        for (int i = 1; i < int(sqrt(n)) + 1; i++)
            square_num.push_back(pow(i, 2));
    }

private:
    vector<int> square_num;
};

class Solution2 //DP  时间复杂度：O(n\cdot\sqrt{n})  空间复杂度：\mathcal{O}(n)
{

public:
    int numSquares(int n)
    {
        vector<int> dp(n + 1, INT_MAX);
        // bottom case
        dp[0] = 0;

        // pre-calculate the square numbers.
        int max_square_index = (int)sqrt(n) + 1;
        vector<int> square_nums(max_square_index);
        for (int i = 1; i < max_square_index; ++i)
        {
            square_nums[i] = i * i;
        }

        for (int i = 1; i <= n; ++i)
        {
            for (int s = 1; s < max_square_index; ++s)
            {
                if (i < square_nums[s])
                    break;
                dp[i] = min(dp[i], dp[i - square_nums[s]] + 1);
            }
        }
        return dp[n];
    }
};

class Solution3 //贪心算法
{

protected:
    bool is_divided_by(int n, int count)
    {
        if (count == 1)
        {
            return square_nums.find(n) == square_nums.end() ? false : true;
        }

        set<int>::iterator iter;
        for (iter = square_nums.begin(); iter != square_nums.end(); ++iter)
        {
            if (is_divided_by(n - *iter, count - 1))
            {
                return true;
            }
        }
        return false;
    }

public:
    int numSquares(int n)
    {
        square_nums.clear();

        for (int i = 1; i * i <= n; ++i)
        {
            square_nums.insert(i * i);
        }

        int count = 1;
        for (; count <= n; ++count)
        {
            if (is_divided_by(n, count))
                return count;
        }
        return count;
    }

private:
    set<int> square_nums;
};

class Solution4 //贪心 + BFS  时间复杂度：\mathcal{O}( \frac{\sqrt{n}^{h+1} - 1}{\sqrt{n} - 1} ) = \mathcal{O}(n^{\frac{h}{2}})   空间复杂度：\mathcal{O}\Big((\sqrt{n})^h\Big)
{
public:
    int numSquares(int n)
    {

        vector<int> square_nums((int)sqrt(n) + 1, 0);
        for (int i = 1; i * i <= n; ++i)
        {
            square_nums.push_back(i * i);
        }

        set<int> queue;
        queue.insert(n);

        int level = 0;
        while (queue.size() > 0)
        {
            level += 1;
            set<int> next_queue;

            for (set<int>::iterator iter1 = queue.begin(); iter1 != queue.end(); ++iter1)
            {
                for (vector<int>::iterator iter2 = square_nums.begin(); iter2 != square_nums.end(); ++iter2)
                {
                    int remainder = *iter1, square = *iter2;
                    if (remainder == square)
                    {
                        return level;
                    }
                    else if (remainder < square)
                    {
                        break;
                    }
                    else
                    {
                        next_queue.insert(remainder - square);
                    }
                }
            }
            queue = next_queue;
        }
        return level;
    }
};

class Solution5 //数学方法  时间复杂度：\mathcal{O}(\sqrt{n})  空间复杂度：\mathcal{O}(1)
{

protected:
    bool isSquare(int n)
    {
        int sq = (int)sqrt(n);
        return n == sq * sq;
    }

public:
    int numSquares(int n)
    {
        // four-square and three-square theorems.
        while (n % 4 == 0)
            n /= 4;
        if (n % 8 == 7)
            return 4;

        if (isSquare(n))
            return 1;
        // enumeration to check if the number can be decomposed into sum of two squares.
        for (int i = 1; i * i <= n; ++i)
        {
            if (isSquare(n - i * i))
                return 2;
        }
        // bottom case of three-square theorem.
        return 3;
    }
};

int main()
{
    int n = 12;
    Solution solution;
    int ans = solution.numSquares(n);
    cout << ans << endl;
    return 0;
}