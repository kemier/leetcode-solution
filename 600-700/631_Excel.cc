#include <vector>
#include <string>

using namespace std;

class Excel
{
public:
    Excel(int H, char W)
    {
        exl = vector<vector<int>>(H + 1, vector<int>(W - 'A' + 1, 0));
        fward.clear();
        bward.clear();
    }

    void set(int r, char c, int v)
    {
        int col = c - 'A';
        int key = r * 26 + col;
        update(r, col, v); // update its value and all the sum related
        if (bward.count(key))
        { // reset, so break all the forward links if existing
            for (int k : bward[key])
            {
                fward[k].erase(key);
            }
            bward[key].clear();
        }
    }

    int get(int r, char c)
    {
        return exl[r][c - 'A'];
    }

    int sum(int r, char c, vector<string> strs)
    {
        int col = c - 'A', key = r * 26 + col, ans = 0;
        if (bward.count(key))
        { // another reset for position (r, c)
            for (int k : bward[key])
            {
                fward[k].erase(key);
            }
            bward[key].clear();
        }
        for (string str : strs)
        { // get the sum over multiple ranges
            int p = str.find(':'), left, right, top, bot;
            left = str[0] - 'A';
            right = str[p + 1] - 'A';
            if (p == -1)
            {
                top = stoi(str.substr(1));
            }
            else
            {
                top = stoi(str.substr(1, p - 1));
            }
            bot = stoi(str.substr(p + 2));
            for (int i = top; i <= bot; ++i)
            {
                for (int j = left; j <= right; ++j)
                {
                    ans += exl[i][j];
                    ++fward[i * 26 + j][key];
                    bward[key].insert(i * 26 + j);
                }
            }
        }
        update(r, col, ans); // update this cell and all the sum related
        return ans;
    }

private:
    void update(int r, int col, int v)
    {
        // update a cell and all the sum related, using BFS
        int prev = exl[r][col];
        exl[r][col] = v;
        queue<int> q;      // q is keys for cells in next level
        queue<int> update; // update is the increment for each cell
        q.push(r * 26 + col);
        update.push(v - prev);
        while (!q.empty())
        {
            int key = q.front(), dif = update.front();
            q.pop(), update.pop();
            if (fward.count(key))
            {
                for (auto it = fward[key].begin(); it != fward[key].end(); ++it)
                {
                    int k = it->first;
                    q.push(k);
                    update.push(dif * (it->second));
                    exl[k / 26][k % 26] += dif * (it->second);
                }
            }
        }
    }
    // The key of a cell is defined as 26 * row + col, which is int
    vector<vector<int>> exl;
    // fward links a cell to all the cells which use it for sum, and it may be used for
    // multiple times due to overlap ranges, so another map is used for its weight
    unordered_map<int, unordered_map<int, int>> fward;
    // bward links a cell to all the cells that contribute to its sum. When reset its value,
    // or reassign a new sum range to it, we need disconnect the forward link of those cells to it.
    unordered_map<int, unordered_set<int>> bward;
};

/**
 * Your Excel object will be instantiated and called as such:
 * Excel obj = new Excel(H, W);
 * obj.set(r,c,v);
 * int param_2 = obj.get(r,c);
 * int param_3 = obj.sum(r,c,strs);
 */

class Excel2
{
public:
    Excel(int H, char W)
    {
        exl = vector<vector<int>>(H + 1, vector<int>(W - 'A' + 1, 0));
        fward.clear();
        bward.clear();
    }

    void set(int r, char c, int v)
    {
        int col = c - 'A';
        int key = r * 26 + col;
        update(r, col, v); // update its value and all the sum related
        if (bward.count(key))
        { // reset, so break all the forward links if existing
            for (int k : bward[key])
            {
                fward[k].erase(key);
            }
            bward[key].clear();
        }
    }

    int get(int r, char c)
    {
        return exl[r][c - 'A'];
    }

    int sum(int r, char c, vector<string> strs)
    {
        int col = c - 'A', key = r * 26 + col, ans = 0;
        if (bward.count(key))
        { // another reset for position (r, c)
            for (int k : bward[key])
            {
                fward[k].erase(key);
            }
            bward[key].clear();
        }
        for (string str : strs)
        { // get the sum over multiple ranges
            int p = str.find(':'), left, right, top, bot;
            left = str[0] - 'A';
            right = str[p + 1] - 'A';
            if (p == -1)
            {
                top = stoi(str.substr(1));
            }
            else
            {
                top = stoi(str.substr(1, p - 1));
            }
            bot = stoi(str.substr(p + 2));
            for (int i = top; i <= bot; ++i)
            {
                for (int j = left; j <= right; ++j)
                {
                    ans += exl[i][j];
                    ++fward[i * 26 + j][key];
                    bward[key].insert(i * 26 + j);
                }
            }
        }
        update(r, col, ans); // update this cell and all the sum related
        return ans;
    }

private:
    void update(int r, int col, int v)
    {
        // update a cell and all the sum related, using BFS
        int prev = exl[r][col];
        exl[r][col] = v;
        queue<int> q;      // q is keys for cells in next level
        queue<int> update; // update is the increment for each cell
        q.push(r * 26 + col);
        update.push(v - prev);
        while (!q.empty())
        {
            int key = q.front(), dif = update.front();
            q.pop(), update.pop();
            if (fward.count(key))
            {
                for (auto it = fward[key].begin(); it != fward[key].end(); ++it)
                {
                    int k = it->first;
                    q.push(k);
                    update.push(dif * (it->second));
                    exl[k / 26][k % 26] += dif * (it->second);
                }
            }
        }
    }
    // The key of a cell is defined as 26 * row + col, which is int
    vector<vector<int>> exl;
    // fward links a cell to all the cells which use it for sum, and it may be used for
    // multiple times due to overlap ranges, so another map is used for its weight
    unordered_map<int, unordered_map<int, int>> fward;
    // bward links a cell to all the cells that contribute to its sum. When reset its value,
    // or reassign a new sum range to it, we need disconnect the forward link of those cells to it.
    unordered_map<int, unordered_set<int>> bward;
};

/**
 * Your Excel object will be instantiated and called as such:
 * Excel obj = new Excel(H, W);
 * obj.set(r,c,v);
 * int param_2 = obj.get(r,c);
 * int param_3 = obj.sum(r,c,strs);
 */