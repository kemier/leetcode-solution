#include <vector>
#include <algorithm>

using namespace std;


class Solution {
public:
    int minTotalDistance(vector<vector<int>>& grid) {
        vector<int> row;
        vector<int> col;
        for(int i = 0; i<grid.size(); ++i){
            for(int j = 0; j < grid[i].size(); ++j){
                if(grid[i][j] == 1){
                    row.push_back(i);
                    col.push_back(j);
                }
            }
        }
        sort(col.begin(), col.end());
        int m = row.size(), n = col.size();
        int midRow = (m%2) ? row[m/2] : (row[(m/2)-1] + row[(m/2)])/2;
        int midCol = (n%2) ? col[n/2] : (col[(n/2) - 1] + col[n/2])/2;
        int dist = 0;
        for(int i = 0; i<m; ++i) dist += abs(row[i] - midRow);
        for(int j = 0; j<n; ++j) dist += abs(col[j] - midCol);
        return dist;
    }
};