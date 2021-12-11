#include <climits>
#include <vector>

using namespace std;

class Solution
{
public:
    bool verifyPreorder(vector<int> preorder)
    {
        return verify(preorder, 0, preorder.size() - 1, INT_MIN, INT_MAX);
    }

private:
    bool verify(vector<int> preorder, int start, int end, int min, int max)
    {
        if (start > end)
            return true;
        int root = preorder[start];
        if (root > max || root < min)
            return false;
        int rightIndex = start;
        while (rightIndex <= end && preorder[rightIndex] <= root)
            rightIndex++;
        return verify(preorder, start + 1, rightIndex - 1, min, root) && verify(preorder, rightIndex, end, root, max);
    }
};