#include <string>
#include <unordered_set>
#include <queue>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct State
{
    string board;
    string hand;
    int step;
    State(const string &board, const string &hand, int step)
    {
        this->board = board;
        this->hand = hand;
        this->step = step;
    }
};

class Solution // BFS
{
public:
    string clean(const string &s)
    {
        string res;
        vector<pair<char, int>> st;

        for (auto c : s)
        {
            while (!st.empty() && c != st.back().first && st.back().second >= 3)
            {
                st.pop_back();
            }
            if (st.empty() || c != st.back().first)
            {
                st.push_back({c, 1});
            }
            else
            {
                st.back().second++;
            }
        }
        if (!st.empty() && st.back().second >= 3)
        {
            st.pop_back();
        }
        for (int i = 0; i < st.size(); ++i)
        {
            for (int j = 0; j < st[i].second; ++j)
            {
                res.push_back(st[i].first);
            }
        }
        return res;
    }

    int findMinStep(string board, string hand)
    {
        unordered_set<string> visited;
        sort(hand.begin(), hand.end());

        visited.insert(board + " " + hand);
        queue<State> qu;
        qu.push(State(board, hand, 0));
        while (!qu.empty())
        {
            State curr = qu.front();
            qu.pop();

            for (int j = 0; j < curr.hand.size(); ++j)
            {
                // 第 1 个剪枝条件: 当前选择的球的颜色和前一个球的颜色相同
                if (j > 0 && curr.hand[j] == curr.hand[j - 1])
                {
                    continue;
                }
                for (int i = 0; i <= curr.board.size(); ++i)
                {
                    // 第 2 个剪枝条件: 只在连续相同颜色的球的开头位置插入新球
                    if (i > 0 && curr.board[i - 1] == curr.hand[j])
                    {
                        continue;
                    }

                    // 第 3 个剪枝条件: 只在以下两种情况放置新球
                    bool choose = false;
                    //   第 1 种情况 : 当前球颜色与后面的球的颜色相同
                    if (i < curr.board.size() && curr.board[i] == curr.hand[j])
                    {
                        choose = true;
                    }
                    //   第 2 种情况 : 当前后颜色相同且与当前颜色不同时候放置球
                    if (i > 0 && i < curr.board.size() && curr.board[i - 1] == curr.board[i] && curr.board[i] != curr.hand[j])
                    {
                        choose = true;
                    }
                    if (choose)
                    {
                        string new_board = clean(curr.board.substr(0, i) + curr.hand[j] + curr.board.substr(i));
                        string new_hand = curr.hand.substr(0, j) + curr.hand.substr(j + 1);
                        if (new_board.size() == 0)
                        {
                            return curr.step + 1;
                        }
                        if (!visited.count(new_board + " " + new_hand))
                        {
                            qu.push(State(new_board, new_hand, curr.step + 1));
                            visited.insert(new_board + " " + new_hand);
                        }
                    }
                }
            }
        }

        return -1;
    }
};

struct State
{
    string board;
    string hand;
    int step;
    State(const string &board, const string &hand, int step)
    {
        this->board = board;
        this->hand = hand;
        this->step = step;
    }
};

class Solution2 //记忆化搜索
{
public:
    unordered_map<string, int> dp;
    string clean(const string &s)
    {
        string res;
        vector<pair<char, int>> st;

        for (auto c : s)
        {
            while (!st.empty() && c != st.back().first && st.back().second >= 3)
            {
                st.pop_back();
            }
            if (st.empty() || c != st.back().first)
            {
                st.push_back({c, 1});
            }
            else
            {
                st.back().second++;
            }
        }
        if (!st.empty() && st.back().second >= 3)
        {
            st.pop_back();
        }
        for (int i = 0; i < st.size(); ++i)
        {
            for (int j = 0; j < st[i].second; ++j)
            {
                res.push_back(st[i].first);
            }
        }
        return res;
    }

    int dfs(const string &board, const string &hand)
    {
        if (board.size() == 0)
        {
            return 0;
        }
        if (dp.count(board + " " + hand))
        {
            return dp[board + " " + hand];
        }

        int res = 6;
        for (int j = 0; j < hand.size(); ++j)
        {
            // 第 1 个剪枝条件: 当前选择的球的颜色和前一个球的颜色相同
            if (j > 0 && hand[j] == hand[j - 1])
            {
                continue;
            }
            for (int i = 0; i <= board.size(); ++i)
            {
                // 第 2 个剪枝条件: 只在连续相同颜色的球的开头位置插入新球
                if (i > 0 && board[i - 1] == hand[j])
                {
                    continue;
                }
                bool choose = false;
                // 第 3 个剪枝条件: 只在以下两种情况放置新球
                //   第 1 种情况 : 当前球颜色与后面的球的颜色相同
                if (i < board.size() && board[i] == hand[j])
                {
                    choose = true;
                }
                //   第 2 种情况 : 当前后颜色相同且与当前颜色不同时候放置球
                if (i > 0 && i < board.size() && board[i - 1] == board[i] && board[i] != hand[j])
                {
                    choose = true;
                }
                if (choose)
                {
                    string new_board = clean(board.substr(0, i) + hand[j] + board.substr(i));
                    string new_hand = hand.substr(0, j) + hand.substr(j + 1);
                    res = min(res, dfs(new_board, new_hand) + 1);
                }
            }
        }
        dp[board + " " + hand] = res;
        return res;
    }

    int findMinStep(string board, string hand)
    {
        sort(hand.begin(), hand.end());
        int ans = dfs(board, hand);
        return ans <= 5 ? ans : -1;
    }
};
