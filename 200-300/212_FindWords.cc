#include "TrieTree.h"
#include <vector>
#include <iostream>

using namespace std;

class Solution // 字典树方法
{
public:
    int R, C;           // 最大行列值
    TrieNode *trie;     // 字典树根结点
    vector<string> ans; // 答案数组
    int need;           // 还需要多少答案数量

    vector<string> findWords(vector<vector<char>> &board, vector<string> &words)
    {
        R = board.size();
        C = board[0].size();

        need = words.size(); // 设置答案需求数量

        trie = new TrieNode(true); // 创建字典树根节点

        // 创建需要单词的字典树
        for (string &word : words)
        {
            trie->insert(trie, word);
        }

        // DFS回溯搜索
        string temp;
        for (int row = 0; row < R; ++row)
        {
            for (int col = 0; col < C; ++col)
            {
                DFS(board, row, col, 0, trie, temp);
            }
        }

        return ans;
    }

    // 深度回溯字符矩阵
    // 试探回溯字符是否够成答案需要的单词
    // param: [int] depth - 递归/回溯/DFS 深度，因为单词长度最多10，因此我们只需要递归深度到10即可返回
    // param: [TrieNode*] curNode - 当前字典树字符结点，初始化传入根结点
    // param: [string&] word - 回溯单词，临时存储当前组成的单词
    void DFS(vector<vector<char>> &board, int row, int col, int depth, TrieNode *curNode, string &word)
    {

        // DFS深度10
        if (depth >= 10)
            return;

        // 不需要再寻找了，因为答案已经找完了
        if (need == 0)
            return;

        // 坐标超出范围
        if (row < 0 || row >= R || col < 0 || col >= C)
            return;

        // 已被访问过(标记过)
        if (board[row][col] < 'a')
            return;

        // 在字典树中，要么该字符结点已被删除，或者没有/不存在
        if (!trie->has(curNode, board[row][col]))
            return;

        // 当前能够构成的单词
        word += board[row][col];

        // 取出下一个字符结点
        curNode = trie->getNextNode(curNode, board[row][col]);

        // 如果这个字符结点可以组成单词的话
        if (trie->isEnd(curNode))
        {
            // 修改当前字符结点不能组成单词
            trie->setEnd(curNode, false);
            // 加入答案数组
            ans.push_back(word);
            // 减少需求数量
            --need;
            if (!need)
                return;

            // 如果该字符节点为叶结点
            if (trie->getNumsOfNext(curNode) == 0)
            {
                // 逻辑地向上回溯删除该分叉
                trie->del_up_logicly(curNode);
                // 回溯// 回溯单词
                word.pop_back();
                return;
            }
        }

        // 标记访问
        board[row][col] -= 26;

        DFS(board, row + 1, col, depth + 1, curNode, word);
        DFS(board, row - 1, col, depth + 1, curNode, word);
        DFS(board, row, col + 1, depth + 1, curNode, word);
        DFS(board, row, col - 1, depth + 1, curNode, word);

        // 回溯单词
        word.pop_back();
        // 回溯标记/访问
        board[row][col] += 26;
        return;
    }
};

int main()
{
    Solution solution;
    vector<vector<char>> board(4);
    board[0].push_back('o');
    board[0].push_back('a');
    board[0].push_back('a');
    board[0].push_back('n');

    board[1].push_back('e');
    board[1].push_back('t');
    board[1].push_back('a');
    board[1].push_back('e');

    board[2].push_back('i');
    board[2].push_back('h');
    board[2].push_back('k');
    board[2].push_back('r');

    board[3].push_back('i');
    board[3].push_back('f');
    board[3].push_back('l');
    board[3].push_back('v');

    vector<string> words;
    words.push_back("oath");
    words.push_back("pea");
    words.push_back("eat");
    words.push_back("rain");
    cout << "------------------------begin test------------------------" << endl;
    solution.findWords(board, words);
    vector<string>::iterator iter;
    for (iter = solution.ans.begin(); iter != solution.ans.end(); ++iter)
    {
        cout << *iter << endl;
    }
    return 0;
}