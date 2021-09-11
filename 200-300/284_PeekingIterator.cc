// Below is the interface for Iterator, which is already defined for you.
// **DO NOT** modify the interface for Iterator.

class Iterator
{
    struct Data;
    Data *data;

public:
    Iterator(const vector<int> &nums);
    Iterator(const Iterator &iter);
    virtual ~Iterator();
    // Returns the next element in the iteration.
    int next();
    // Returns true if the iteration has more elements.
    bool hasNext() const;
};
//----------------------以上不用提交----------

#include <vector>

using namespace std;

class PeekingIterator : public Iterator
{
    int curVal;
    bool end;

public:
    PeekingIterator(const vector<int> &nums) : Iterator(nums)
    {
        end = false;
        if (Iterator::hasNext())
        {
            curVal = Iterator::next();
        }
        else
            end = true;
    }
    int peek()
    {
        return curVal;
    }

    int next()
    {
        if (end)
            return -1;
        int ans = curVal;
        if (Iterator::hasNext())
            curVal = Iterator::next();
        else
            end = true;
        return ans;
    }

    bool hasNext() const
    {
        return !end;
    }
};
