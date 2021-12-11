#include <vector>
#include <algorithm>

using namespace std;
class Solution //二分查找  时间复杂度：O(lg(n!))  空间复杂度：O(1)
{
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target)
    {
        if (matrix.size() == 0)
            return false;

        int shorterDim = min(matrix.size(), matrix[0].size());
        for (int i = 0; i < shorterDim; i++)
        {
            bool verticalFound = binarySearch(matrix, target, i, true);
            bool horizontalFound = binarySearch(matrix, target, i, false);
            if (verticalFound || horizontalFound)
                return true;
        }
        return false;
    }

    bool binarySearch(vector<vector<int>> &matrix, int target, int start, bool vertical)
    {
        int lo = start;
        int hi = vertical ? matrix[0].size() - 1 : matrix.size() - 1;
        while (lo <= hi)
        {
            int mid = (lo + hi) / 2;
            if (vertical)
            { //searching a column
                if (matrix[start][mid] < target)
                    lo = mid + 1;
                else if (matrix[start][mid] > target)
                    hi = mid - 1;
                else
                    return true;
            }
            else
            {
                if (matrix[mid][start] < target)
                    lo = mid + 1;
                else if (matrix[mid][start] > target)
                    hi = mid - 1;
                else
                    return true;
            }
        }
        return false;
    }
};

class Solution2 //搜索空间的缩减 超出时间限制  时间复杂度：O(nlgn)  空间复杂度：O(lgn)
{
public:
    bool searchRec(int left, int up, int right, int down)
    {
        // this submatrix has no height or no width.
        if (left > right || up > down)
        {
            return false;
            // `target` is already larger than the largest element or smaller
            // than the smallest element in this submatrix.
        }
        else if (target < matrix[up][left] || target > matrix[down][right])
        {
            return false;
        }

        int mid = left + (right - left) / 2;

        // Locate `row` such that matrix[row-1][mid] < target < matrix[row][mid]
        int row = up;
        while (row <= down && matrix[row][mid] <= target)
        {
            if (matrix[row][mid] == target)
            {
                return true;
            }
            row++;
        }

        return searchRec(left, row, mid - 1, down) || searchRec(mid + 1, up, right, row - 1);
    }

    bool searchMatrix(vector<vector<int>> &mat, int targ)
    {
        // cache input values in object to avoid passing them unnecessarily
        // to `searchRec`
        matrix = mat;
        target = targ;

        // an empty matrix obviously does not contain `target`
        if (matrix == null || matrix.size() == 0)
        {
            return false;
        }

        return searchRec(0, 0, matrix[0].size() - 1, matrix.size() - 1);
    }

private:
    vector<vector<int>> matrix;
    int target;
};

class Solution3 //时间复杂度：O(n+m)  空间复杂度：O(1)
{
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target)
    {
        // start our "pointer" in the bottom-left
        int row = matrix.size() - 1;
        int col = 0;

        while (row >= 0 && col < matrix[0].size())
        {
            if (matrix[row][col] > target)
            {
                row--;
            }
            else if (matrix[row][col] < target)
            {
                col++;
            }
            else
            { // found it
                return true;
            }
        }

        return false;
    }
};

class Solution4 //从左下角开始搜索  时间复杂度：O(n + m) 空间复杂度：O(1)
{

public:
    bool searchMatrix(vector<vector<int>> &matrix, int target)
    {
        if (matrix.size() == 0)
        {
            return false;
        }
        int col = 0;
        int row = matrix.size() - 1;
        while (col < matrix[0].size() && row > -1)
        {
            if (matrix[row][col] > target)
            {
                row--;
            }
            else if (matrix[row][col] < target)
            {
                col++;
            }
            else
            {
                return true;
            }
        }
        return false;
    }
};
