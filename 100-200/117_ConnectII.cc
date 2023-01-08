//
// Created by 曾宁 on 2023/1/8.
//

#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};


class Solution {
public:
    Node* connect(Node* root) {
        //BFS广度优先遍历
        if(root==NULL) return root; //当根节点为空时，直接返回
        queue<Node*> q;  //记录队列
        q.push(root);  //首先将根节点存入
        Node* temp;   //遍历指针
        Node* m;      //用于进行next连接的指针
        int k=1,t=0;  //每层节点个数记录
        while(!q.empty())
        {
            //每一层的遍历开始，将t=0，用于结束时更新k值，m指向null，进行每一层首个节点之前无next判断
            t=0;
            m=NULL;
            for(int i=0;i<k;i++)
            {   //队列取出
                temp=q.front();
                q.pop();
                //next连接
                if(m!=NULL) m->next=temp;
                m=temp;
                //左节点存入
                if(temp->left) q.push(temp->left),t++;
                //右节点存入
                if(temp->right) q.push(temp->right),t++;
            }
            //更新k值
            k=t;
        }
        return root;
    }
};

