#include <bits/stdc++.h>

using namespace  std;

class Solution1{//BFS
public:
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
    	int m = maze.size(), n = maze[0].size(), i, j, k, x, y;
    	vector<vector<int>> dir = {{1,0},{0,1},{0,-1},{-1,0}};
    	queue<vector<int>> q;
    	vector<vector<bool>> visited(m, vector<bool>(n,false));
    	q.push(start);
    	visited[start[0]][start[1]] = true;
    	while(!q.empty())
    	{
    		i = q.front()[0];
    		j = q.front()[1];
    		q.pop();
            if(i==destination[0] && j==destination[1])
                return true;
    		for(k = 0; k < 4; ++k)
    		{
    			x = i;
	    		y = j;
    			while(x+dir[k][0]>=0 && x+dir[k][0]<m && y+dir[k][1]>=0 && y+dir[k][1]<n
                        && maze[x+dir[k][0]][y+dir[k][1]]==0)
	    		{	//下一个位置不是墙壁，进入循环，接着走
	    			x += dir[k][0];
	    			y += dir[k][1];
                    // visited[x][y] = true;//不能加这一句，一会下面进不了队列
	    		}
	    		//x,y,下一个位置是墙壁，停在xy
                if(!visited[x][y])
	    		{
                    q.push({x, y});
                    visited[x][y] = true;
                }
    		}
    	}
    	return false;
    }
};



class Solution2 {//DFS
    int m, n;
    vector<vector<int>> dir = {{1,0},{0,1},{0,-1},{-1,0}};
    bool found = false;
public:
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
    	m = maze.size(), n = maze[0].size();
    	vector<vector<bool>> visited(m, vector<bool>(n,false));
    	visited[start[0]][start[1]] = true;
        dfs(maze,start,destination,visited);
        return found;
    }
    void dfs(vector<vector<int>>& maze, vector<int> start, vector<int>& destination, vector<vector<bool>> &visited)
    {
        if(found) return;
        int i = start[0], j = start[1], x, y, k;
        if(i==destination[0] && j==destination[1])
        {
            found = true;
            return;
        }
        for(k = 0; k < 4; ++k)
        {
            x = i;
            y = j;
            while(x+dir[k][0]>=0 && x+dir[k][0]<m && y+dir[k][1]>=0 && y+dir[k][1]<n
                    && maze[x+dir[k][0]][y+dir[k][1]]==0)
            {
                x += dir[k][0];
                y += dir[k][1];
                // visited[x][y] = true;//不能加这一句，一会下面进不了队列
            }
            if(!visited[x][y])
            {
                visited[x][y] = true;
                dfs(maze,{x,y},destination,visited);
            }
        }
    }
};

