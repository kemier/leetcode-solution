#include <vector>
#include <list>
#include <algorithm>

using namespace std;

class NestedInteger {
  public:
    // Constructor initializes an empty nested list.

    NestedInteger();

    // Constructor initializes a single integer.

    NestedInteger(int value);

    // Return true if this NestedInteger holds a single integer, rather than a nested list.

    bool isInteger() const;

    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list

    int getInteger() const;

    // Set this NestedInteger to hold a single integer.

    void setInteger(int value);

    // Set this NestedInteger to hold a nested list and adds a nested integer to it.

    void add(const NestedInteger &ni);

    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer

    const vector<NestedInteger> &getList() const;
};

class Solution {
private:
     int maxDepth(vector<NestedInteger> nestedList, int depth) {
        int Max = depth;
        for(NestedInteger ni : nestedList) {
            if (!ni.isInteger()) {
                Max = max(Max, maxDepth(ni.getList(), depth + 1));
            }
        }
        return Max;
    }
    int Sum(vector<NestedInteger> nestedList, int depth) {
        int sum = 0;
        for(NestedInteger ni : nestedList) {
            if (ni.isInteger()) {
                sum += ni.getInteger() * depth;
            } else {
                sum += Sum(ni.getList(), depth - 1);
            }
        }
        return sum;
    }
public:
    int depthSumInverse(vector<NestedInteger> nestedList) {
        if (nestedList.size() ==0) return 0;
        int max = maxDepth(nestedList, 1);
        return Sum(nestedList, max);
    }
};