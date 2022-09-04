#include <bits/stdc++.h>

using namespace  std;

class Solution {
public:
    string findShortestWay(vector<vector<int>>& maze, vector<int>& ball, vector<int>& hole) {
        pair<string, int> res = {"impossible", INT_MAX};
        return roll(maze, ball[0], ball[1], hole, 0, 0, 0, "", res);
    }
private:
    string roll(vector<vector<int>>& maze, int row, int col, const vector<int>& hole, 
                int d_row, int d_col, int steps, const string &path, pair<string, int> &res) {
        if (steps < res.second) {
            if (d_row != 0 || d_col != 0) {     // check the position ball + {d_row, d_col}
                while ((row + d_row) >= 0 && (col + d_col) >= 0 && (row + d_row) <  maze.size() 
                        && (col + d_col) < maze[0].size() && maze[row + d_row][col + d_col] != 1) {
                    row += d_row;
                    col += d_col;
                    ++steps;
                    if (row == hole[0] && col == hole[1] && steps < res.second) {
                        res = {path, steps};
                    }
                }
            }
            if (maze[row][col] == 0 || steps + 2 < maze[row][col]) {
                maze[row][col] = steps + 2; // '1' is for the walls. We change the maze data when performing DFS
                if (d_row == 0) {   // can only start rolling down if the previous direction is horizontal
                    roll(maze, row, col, hole, 1, 0, steps, path + "d", res);
                }
                if (d_col == 0) {   // can only start rolling left if the previous direction is vertical
                    roll(maze, row, col, hole, 0, -1, steps, path + "l", res);
                }
                if (d_col == 0) {   // can only start rolling right if the previous direction is vertical
                    roll(maze, row, col, hole, 0, 1, steps, path + "r", res);
                }
                if (d_row == 0) {   // can only start rolling up if the previous direction is horizontal
                    roll(maze, row, col, hole, -1, 0, steps, path + "u", res);
                }
            }
        }
        return res.first;
    }
};

