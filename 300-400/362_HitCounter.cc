
#include <list>

using namespace std;

class HitCounter
{
public:
    /** Initialize your data structure here. */
    HitCounter()
    {
    }

    /** Record a hit.
        @param timestamp - The current timestamp (in seconds granularity). */
    void hit(int timestamp)
    {
        lt.push_back(timestamp);
    }

    /** Return the number of hits in the past 5 minutes.
        @param timestamp - The current timestamp (in seconds granularity). */
    int getHits(int timestamp)
    {
        auto it = lt.begin();
        while (it != lt.end() && timestamp - *it >= 300)
            it = lt.erase(it);
        return lt.size();
    }

private:
    list<int> lt;
};

/**
 * Your HitCounter object will be instantiated and called as such:
 * HitCounter obj = new HitCounter();
 * obj.hit(timestamp);
 * int param_2 = obj.getHits(timestamp);
 */