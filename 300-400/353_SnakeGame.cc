#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

class SnakeGame
{
public:
    /** Initialize your data structure here.
        @param width - screen width
        @param height - screen height 
        @param food - A list of food positions
        E.g food = [[1,1], [1,0]] means the first food is positioned at [1,1], the second is at [1,0]. */
    SnakeGame(int width, int height, vector<pair<int, int>> food)
        : w(width), h(height), x(0), y(0), cur(0), flag(0), fd(food)
    {
        que.push(0);
        hash[0] = true;
    }

    /** Moves the snake.
        @param direction - 'U' = Up, 'L' = Left, 'R' = Right, 'D' = Down 
        @return The game's score after the move. Return -1 if game over. 
        Game over when snake crosses the screen boundary or bites its body. */
    int move(string direction)
    {
        if (direction == "U")
            x--;
        if (direction == "L")
            y--;
        if (direction == "R")
            y++;
        if (direction == "D")
            x++;
        if (flag == 0)
        {
            int val = que.front();
            hash.erase(val);
            que.pop();
        }
        if (x < 0 || y < 0 || x >= h || y >= w || hash.count(x * w + y))
            return -1;
        que.push(x * w + y);
        hash[x * w + y] = true;
        flag = 0;
        if (x == fd[cur].first && y == fd[cur].second)
            flag = 1, cur++;
        return que.size() + flag - 1;
    }

private:
    queue<int> que;
    unordered_map<int, bool> hash;
    int w, h, x, y, cur, flag;
    vector<pair<int, int>> fd;
};

/**
 * Your SnakeGame object will be instantiated and called as such:
 * SnakeGame obj = new SnakeGame(width, height, food);
 * int param_1 = obj.move(direction);
 */