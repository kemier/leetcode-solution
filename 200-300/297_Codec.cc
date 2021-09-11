#include <vector>
#include <cstring>
#include <string>
#define DSA_STACK_LIST
#include "binTree/BinTree.h"
#include <iostream>

using namespace std;
class Codec
{
public:
    string rserialize(BinNode<int> *root, string str)
    {
        if (root == nullptr)
        {
            str += "None,";
        }
        else
        {
            str += to_string(root->data) + ",";
            str = rserialize(root->lc, str);
            str = rserialize(root->rc, str);
        }
        return str;
    }

    string serialize(BinNode<int> *root)
    {
        return rserialize(root, "");
    }

    BinNode<int> *rdeserialize(vector<string> l)
    {
        if (*(l.begin()) == "None")
        {
            l.erase(l.begin());
            return nullptr;
        }

        BinNode<int> *root = new BinNode<int>(atoi(l.at(0).c_str()));
        l.erase(l.begin());
        root->lc = rdeserialize(l);
        root->rc = rdeserialize(l);

        return root;
    }

    BinNode<int> *deserialize(string data)
    {
        vector<string> data_array = split(data, ",");
        return rdeserialize(data_array);
    }

    vector<string> split(const string &str, const string &delim)
    {
        vector<string> res;
        if ("" == str)
            return res;
        //先将要切割的字符串从string类型转换为char*类型
        char *strs = new char[str.length() + 1]; //不要忘了
        strcpy(strs, str.c_str());

        char *d = new char[delim.length() + 1];
        strcpy(d, delim.c_str());

        char *p = strtok(strs, d);
        while (p)
        {
            string s = p;     //分割得到的字符串转换为string类型
            res.push_back(s); //存入结果数组
            p = strtok(NULL, d);
        }

        return res;
    }
};

class Codec2
{
public:
    string serialize(BinNode<int> *root)
    {
        if (!root)
            return "X";
        auto l = "(" + serialize(root->lc) + ")";
        auto r = "(" + serialize(root->rc) + ")";
        return l + to_string(root->data) + r;
    }

    inline BinNode<int> *parseSubtree(const string &data, int &ptr)
    {
        ++ptr; // 跳过左括号
        auto subtree = parse(data, ptr);
        ++ptr; // 跳过右括号
        return subtree;
    }

    inline int parseInt(const string &data, int &ptr)
    {
        int x = 0, sgn = 1;
        if (!isdigit(data[ptr]))
        {
            sgn = -1;
            ++ptr;
        }
        while (isdigit(data[ptr]))
        {
            x = x * 10 + data[ptr++] - '0';
        }
        return x * sgn;
    }

    BinNode<int> *parse(const string &data, int &ptr)
    {
        if (data[ptr] == 'X')
        {
            ++ptr;
            return nullptr;
        }
        auto cur = new BinNode<int>(0);
        cur->lc = parseSubtree(data, ptr);
        cur->data = parseInt(data, ptr);
        cur->rc = parseSubtree(data, ptr);
        return cur;
    }

    BinNode<int> *deserialize(string data)
    {
        int ptr = 0;
        return parse(data, ptr);
    }
};

void Print(int x)
{
    cout << x << " ";
}
template <typename VST> //操作器
void travPre(BinNode<int> *root, VST &visit)
{
    if (root)
        root->travPre(visit);
} //先序遍历

int main()
{

    BinTree<int> *tree = new BinTree<int>();
    BinNodePosi<int> root = tree->insertAsRoot(1);
    BinNodePosi<int> L1_l = tree->insertAsLC(root, 2);
    BinNodePosi<int> L1_r = tree->insertAsRC(root, 3);
    BinNodePosi<int> L2_rl = tree->insertAsLC(L1_l, 4);
    BinNodePosi<int> L2_rr = tree->insertAsLC(L1_r, 5);

    tree->travPre(Print);
    cout << endl;

    Codec2 solution;

    cout << "------------------------begin test------------------------" << endl;
    string ans = solution.serialize(root);
    cout << ans << endl;
    root = solution.deserialize(ans);
    travPre(root, Print);
    return 0;
}