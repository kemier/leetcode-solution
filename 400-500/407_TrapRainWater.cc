#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;



struct Cell
{
    int x,y,h;
    Cell(int _x,int _y,int _h):x(_x),y(_y),h(_h){};
    bool operator < (const Cell &c) const
    {
        return h>c.h;
    }
};
class Solution{
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        if(heightMap.size()==0 || heightMap[0].size()==0 )
            return 0;
        int n=heightMap.size();
        int m=heightMap[0].size();
        vector<vector<bool>> vis(n,vector<bool>(m));
        priority_queue<Cell> pq;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                if(i==0 || i==n-1 || j==0|| j==m-1)
                {
                    pq.push({i,j,heightMap[i][j]});
                    vis[i][j]=true;
                }
            }
        }
        int res=0;
        int dirs[]={-1,0,1,0,-1};
        while(!pq.empty())
        {
            Cell c=pq.top();
            pq.pop();
            for(int i=0;i<4;i++)
            {
                int nx=c.x+dirs[i];
                int ny=c.y+dirs[i+1];
                if(nx>=0 && nx<n && ny>=0 && ny<m && !vis[nx][ny])
                {
                    if(c.h>heightMap[nx][ny])
                    {
                        res+=c.h-heightMap[nx][ny];
                    }
                    pq.push({nx,ny,max(c.h,heightMap[nx][ny])});
                    vis[nx][ny]=true;
                }
            }
        }
        return res;
    }
};

int main(){
    vector<vector<int>> array;
    array.push_back(vector<int>{3,3,3,3,3});
    array.push_back(vector<int>{3,2,2,2,3});
    array.push_back(vector<int>{3,2,1,2,3});
    array.push_back(vector<int>{3,2,2,2,3});
    array.push_back(vector<int>{3,3,3,3,3});

    Solution solution;
    int res=solution.trapRainWater(array);
    cout<<"the result is: "<<res<<endl;
    return  0;
}