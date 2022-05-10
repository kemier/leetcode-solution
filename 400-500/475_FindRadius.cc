#include <bits/stdc++.h>

using namespace std;

class Solution // Sorting+BinarySearch
{
public:
    int findRadius(vector<int> &houses, vector<int> &heaters)
    {
        int ans = 0;
        sort(heaters.begin(), heaters.end());
        for (int house : houses)
        {
            int j = upper_bound(heaters.begin(), heaters.end(), house) - heaters.begin();
            int i = j - 1;
            int rightDistance = j >= heaters.size() ? INT_MAX : heaters[j] - house;
            int leftDistance = i < 0 ? INT_MAX : house - heaters[i];
            int curDistance = min(leftDistance, rightDistance);
            ans = max(ans, curDistance);
        }
        return ans;
    }
};

class Solution2 //Sorting+DoublePointer
{
public:
    int findRadius(vector<int> &houses, vector<int> &heaters)
    {
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());
        int ans = 0;
        for (int i = 0, j = 0; i < houses.size(); i++)
        {
            int curDistance = abs(houses[i] - heaters[j]);
            while (j < heaters.size() - 1 && abs(houses[i] - heaters[j]) >= abs(houses[i] - heaters[j + 1]))
            {
                j++;
                curDistance = min(curDistance, abs(houses[i] - heaters[j]));
            }
            ans = max(ans, curDistance);
        }
        return ans;
    }
};
