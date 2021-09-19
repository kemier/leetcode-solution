#include <vector>

using namespace std;

class Solution //BFS
{
public:
    int minArea(vector<vector<char>> &image, int x, int y)
    {
        if (image.empty())
        {
            return 0;
        }

        int left = y, right = y, top = x, down = x;
        queue<pair<int, int>> que;
        pair<int, int> p = make_pair(x, y), q;
        que.push(p);
        image[p.first][p.second] = '0'; // 该点为1，且访问过就将该点置为0；

        while (!que.empty())
        {
            p = que.front();
            que.pop();

            // 检测p点左侧的点
            if (p.second != 0 && image[p.first][p.second - 1] == '1')
            {
                image[p.first][p.second - 1] = '0';
                q = make_pair(p.first, p.second - 1);
                que.push(q);
                left = left < (p.second - 1) ? left : (p.second - 1);
            }
            // 检测p点右侧的点
            if (p.second != image[0].size() - 1 && image[p.first][p.second + 1] == '1')
            {
                image[p.first][p.second + 1] = '0';
                q = make_pair(p.first, p.second + 1);
                que.push(q);
                right = right > (p.second + 1) ? right : (p.second + 1);
            }
            // 检测p点上面的点
            if (p.first != 0 && image[p.first - 1][p.second] == '1')
            {
                image[p.first - 1][p.second] = '0';
                q = make_pair(p.first - 1, p.second);
                que.push(q);
                top = top < (p.first - 1) ? top : (p.first - 1);
            }
            // 检测p点下面的点
            if (p.first != image.size() - 1 && image[p.first + 1][p.second] == '1')
            {
                image[p.first + 1][p.second] = '0';
                q = make_pair(p.first + 1, p.second);
                que.push(q);
                down = down > (p.first + 1) ? down : (p.first + 1);
            }
        }

        return (right - left + 1) * (down - top + 1);
    }
};

class Solution2 //DFS
{
public:
    int minArea(vector<vector<char>> &image, int x, int y)
    {
        int left = y, right = y, top = x, down = x;
        dfs(image, x, y, left, right, top, down);
        return (right - left + 1) * (down - top + 1);
    }

    void dfs(vector<vector<char>> &image, int x, int y, int &left, int &right, int &top, int &down)
    {
        if (x < 0 || x >= image.size() || y < 0 || y >= image[0].size() || image[x][y] != '1')
        {
            return;
        }
        image[x][y] = '0';
        left = min(y, left);
        right = max(y, right);
        top = min(x, top);
        down = max(x, down);
        dfs(image, x - 1, y, left, right, top, down);
        dfs(image, x + 1, y, left, right, top, down);
        dfs(image, x, y - 1, left, right, top, down);
        dfs(image, x, y + 1, left, right, top, down);
    }
};

class Solution3 //二分查找
{
public:
    int minArea(vector<vector<char>> &image, int x, int y)
    {
                if (!image.size() || !image[0].size())
        {
                        return 0;
                   
        }
                int row_num = image.size(), col_num = image[0].size();
                // find the leftmost '1' in the range [0, row_num]
        int left  = horizontalSearch(0,     y,          0, row_num, image, '1');
                // find the rightmost '1' in the range [0, row_num] by searching 0
        int right = horizontalSearch(y + 1, col_num,    0, row_num, image, '0');
                // find the upmost '1' in the range [left, right]
        int up  = verticalSearch(0,  x, left, right, image, '1');
         
        // find the downmost '1' in the range [left, right] by searching 0
        int down  = verticalSearch(x + 1, row_num, left, right, image, '0');
         
        return (right - left) * (down - up);
           
    }

private:
        // the time complexity is O(log(end - start) * (bottom - up))
    int horizontalSearch(int start, int end, int top, int bottom, vector<vector<char>> &image, char target)
    {
                while (start < end)
        {
                        int mid = start + (end - start) / 2;
                        int temp_top = top;
                        char found = '0';
                        while (temp_top < bottom)
            {
                                if (image[temp_top++][mid] == '1')
                {
                                        found = '1';
                     
                    break;
                                   
                }
                           
            }
            if (target == found)
            {
                    end = mid;
                           
            }
             else
            {
                start = mid + 1;
                           
            }
                   
        }
          return start;
           
    }
        
    // the time complexity is O(log(end - start) * (right - left))
    int verticalSearch(int start, int end, int left, int right, vector<vector<char>> &image, char target)
    {
         
        while (start < end)
        {
                        int mid = start + (end - start) / 2;
                        int temp_left = left;
                        char found = '0';
                        while (temp_left < right)
            {
                                if (image[mid][temp_left++] == '1')
                {
                                        found = '1';
                     
                    break;
                                   
                }
                           
            }
                        if (target == found)
            {
                                end = mid;
                           
            }
                        else
            {
                                start = mid + 1;
                           
            }
                   
        }
                return start;
           
    }
};
