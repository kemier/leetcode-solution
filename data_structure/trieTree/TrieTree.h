#ifndef __TRIE_TREE_H__
#define __TRIE_TREE_H__

#include <string>

using namespace std;

// 字典树
class TrieNode
{
private:
    TrieNode *next[26]; // 孩子列表[0-25]表示['a'-'z']，nullptr表示无
    TrieNode *parent;   // 该结点的父结点/双亲结点
    char flag;          // 控制标记。-1 逻辑已删除； 0：作为中间链路；1：有效单词结束
    int numsOfNext;     // 当前结点的孩子个数，叶结点为0

public:
    // 构造函数
    // param: [bool] isRoot - 初始化的根结点需要置true
    TrieNode(bool isRoot = false)
    {
        for (int i = 0; i < 26; ++i)
            next[i] = nullptr;
        flag = isRoot;
        parent = nullptr;
        numsOfNext = 0;
    }

    // 在字典树的根结点插入单词记录 (若存在则跳过，默认在单词结尾的字符结点置其控制标记flag为1)
    // param: [TrieNode*] root - 一般传字典树根结点
    // param: [string] word - 单词
    // return: [TrieNode*] - 返回插入的单词末尾字符结点
    TrieNode *insert(TrieNode *root, string word)
    {
        auto ptr = root;
        for (char c : word)
        {
            if (ptr->next[c - 'a'] == nullptr)
            {
                ptr->next[c - 'a'] = new TrieNode();
                ptr->next[c - 'a']->parent = ptr;
                ++ptr->numsOfNext;
            }
            ptr = ptr->next[c - 'a'];
        }
        ptr->flag = true;
        return ptr;
    }

    // 在字典树的某个结点插入下一个字符结点 (若存在则跳过，需要指定其是否是单词结尾)
    // param: [TrieNode*] root - 字典树的某个结点
    // param: [char] c - 字符
    // param: [bool] isEnd - 是否以此为结尾够成新单词
    // return: [TrieNode*] - 返回插入的新字符结点
    TrieNode *insert(TrieNode *root, char c, bool isEnd)
    {
        if (root->next[c - 'a'] == nullptr)
        {
            root->next[c - 'a'] = new TrieNode();
            root->next[c - 'a']->parent = root;
            ++root->numsOfNext;
        }
        root->next[c - 'a']->flag = isEnd;
        return root->next[c - 'a'];
    }

    // 在字典树的根个结点查找单词记录 (需满足单词结尾的字符结点其控制标记flag为1)
    // param: [TrieNode*] root - 一般传字典树根结点
    // param: [string] word - 单词
    // return: [bool] - 是否存在
    bool has(TrieNode *root, string word)
    {
        if (!root)
            return false;
        auto ptr = root;
        for (char c : word)
        {
            if (ptr->next[c - 'a'] == nullptr || ptr->next[c - 'a']->flag == -1)
            {
                return false;
            }
            ptr = ptr->next[c - 'a'];
        }
        return ptr->flag == 1;
    }

    // 在字典树的某结点查找是否存在下一个指定的字符
    // param: [TrieNode*] root - 字典树的某结点
    // param: [char] c - 查找的字符
    // return: [bool] - 是否存在
    bool has(TrieNode *root, char c)
    {
        if (!root)
            return false;
        if (root->next[c - 'a'] == nullptr || root->next[c - 'a']->flag == -1)
        {
            return false;
        }
        return true;
    }

    // 逻辑上删除(flag置-1)，在字典树的某子结点开始向上追溯父结点/双亲结点并删除，若父结点/双亲结点有其他分叉或其flag为1(作为单词结尾)则停止删除
    // param: [TrieNode*] root - 字典树的某结点
    // return: [TrieNode*] - 返回停止删除的父结点
    TrieNode *del_up_logicly(TrieNode *root)
    {
        auto cur = root;
        do
        {
            cur->flag = -1;
            cur = cur->parent;
            --cur->numsOfNext;

        } while (cur->flag <= 0 && cur->numsOfNext == 0);
        return cur;
    }

    //=========================================================
    // setter & getter 不做详细注释

    // 返回当前结点的下一个指定字符结点
    TrieNode *getNextNode(TrieNode *root, char c)
    {
        return root->next[c - 'a'];
    }

    // 返回当前结点的父结点/双亲结点
    TrieNode *getParentNode(TrieNode *root)
    {
        return root->parent;
    }

    // 返回当前结点是否是单词结尾
    bool isEnd(TrieNode *root)
    {
        return root->flag == 1;
    }

    // 返回当前结点的分支next数量
    int getNumsOfNext(TrieNode *root)
    {
        return root->numsOfNext;
    }

    // 设置当前结点是否是单词结尾
    void setEnd(TrieNode *root, bool isEnd)
    {
        root->flag = isEnd;
    }
};

#endif