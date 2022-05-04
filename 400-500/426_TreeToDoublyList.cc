
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node() {}
    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }
    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};

class Solution {
public:
    Node* treeToDoublyList(Node* root) {

        if (!root)
            return root;

        Node* l_beg = treeToDoublyList(root->left);
        Node* r_beg = treeToDoublyList(root->right);

        Node* l_end = l_beg ? l_beg->left : nullptr;
        if (l_end) {
            l_end->right = root;
            root->left = l_end;
        }
        Node* beg = l_beg ? l_beg : root;
        Node* end = r_beg ? r_beg->left : root;
        if (r_beg) {
            root->right = r_beg;
            r_beg->left = root;
        }

        beg->left = end;
        end->right = beg;
        return beg;
    }
};



class Solution2 {
public:
    Node* treeToDoublyList(Node* root) {

        if (!root)
            return root;

        Node dummy(0);
        Node* pre = &dummy, * cur = root;
        stack<Node*> stk;
        while (!stk.empty() || cur) {
            while (cur) {
                stk.push(cur);
                cur = cur->left;
            }
            cur = stk.top();
            stk.pop();
            cur->left = pre;
            pre->right = cur;
            pre = cur;
            cur = cur->right;
        }

        Node* ret = dummy.right;
        ret->left = pre;
        pre->right = ret;
        return ret;
    }
};