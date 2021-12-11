#include  <stdlib.h>


struct ListNode {
     int val;
     ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


class Solution {
public:
    ListNode* head;
    Solution(ListNode* head): head(head){}
    
    int getRandom() {
        int ans = head->val;
        ListNode* n = head->next;
        int k = 2;
        while (n) {
            // rand() % k == 0 模拟概率为 1/k 的情况
            if ((rand() % k) == 0) {
                ans = n->val;
            }
            ++k;
            n = n->next;
        }
        return ans;
    }
};
