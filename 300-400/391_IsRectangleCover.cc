#include <vector>
#include <climits>
#include <algorithm>
#include <sstream>
#include <unordered_set>

using namespace std;




class Solution {

public:
    string int2str( int val )
    {
        ostringstream out;
        out<<val;
        return out.str();
    }
    bool isRectangleCover(vector<vector<int>> rectangles) {
        // 完美矩形的左下角和右上角坐标
        int X1 = INT_MAX, Y1 = INT_MAX;
        int X2 = INT_MIN, Y2 = INT_MIN;
		
        // 小矩形面积之和
        int areas = 0;
        // 记录所有顶点的出现情况
        unordered_set<string> points;
        for (auto rectangle : rectangles) {
            int x1 = rectangle[0], y1 = rectangle[1], x2 = rectangle[2], y2 = rectangle[3];
            // 更新坐标
            X1 = min(x1, X1);
            Y1 = min(y1, Y1);
            X2 = max(x2, X2);
            Y2 = max(y2, Y2);

            areas += (x2 - x1) * (y2 - y1);
            // 判断顶点是否出现过
            vector<string> ps = {int2str(x1) + " " + int2str(y1), int2str(x2) + " " + int2str(y2), int2str(x1) + " " + int2str(y2), int2str(x2) + " " + int2str(y1)};
            for (auto s : ps) {
                // 没有出现过，添加；否则，移除
                if(points.find(s)!=points.end()){
                    points.erase(s);
                } else {
                    points.insert(s);
                }
            }
        }
		
        // 面积是否相等 
        int expected = (X2 - X1) * (Y2 -Y1);
        if(areas != expected){
            return false;
        }
        // 顶点情况是否满足
        if(points.size() != 4 || points.find(X1 + " " + Y1)!=points.end() || points.find(X2 + " " + Y2)!=points.end() || points.find(X1 + " " + Y2)!=points.end() || points.find(X2 + " " + Y1)!=points.end()){
            return false;
        }
        return true;
    }
};

