#include <vector>
#include <queue>

using namespace std;

class MedianFinder //简单排序  时间复杂度：O(n\log n) + O(1) \simeq O(n\log n)  空间复杂度：O(n)
{
    vector<double> store;

public:
    // Adds a number into the data structure.
    void addNum(int num)
    {
        store.push_back(num);
    }

    // Returns the median of current data stream
    double findMedian()
    {
        sort(store.begin(), store.end());

        int n = store.size();
        return (n & 1 ? store[n / 2] : (store[n / 2 - 1] + store[n / 2]) * 0.5);
    }
};

class MedianFinder2 //插入排布  时间复杂度：O(n) + O(\log n) \approx  O(n)   空间复杂度：O(n)
{
    vector<int> store; // resize-able container

public:
    // Adds a number into the data structure.
    void addNum(int num)
    {
        if (store.empty())
            store.push_back(num);
        else
            store.insert(lower_bound(store.begin(), store.end(), num), num); // binary search and insertion combined
    }

    // Returns the median of current data stream
    double findMedian()
    {
        int n = store.size();
        return n & 1 ? store[n / 2] : (store[n / 2 - 1] + store[n / 2]) * 0.5;
    }
};

class MedianFinder3
{
    priority_queue<int> lo;                            // max heap
    priority_queue<int, vector<int>, greater<int>> hi; // min heap

public:
    // Adds a number into the data structure.
    void addNum(int num)
    {
        lo.push(num); // Add to max heap

        hi.push(lo.top()); // balancing step
        lo.pop();

        if (lo.size() < hi.size())
        { // maintain size property
            lo.push(hi.top());
            hi.pop();
        }
    }

    // Returns the median of current data stream
    double findMedian()
    {
        return lo.size() > hi.size() ? (double)lo.top() : (lo.top() + hi.top()) * 0.5;
    }
};
