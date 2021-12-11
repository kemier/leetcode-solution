struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(nullptr) {}
 };
 
class Solution {
public:
    int DFS(ListNode* head)
    {
        int flag = 0;
        if(!head->next) flag = 1;
        else flag = DFS(head->next);
        int val = head->val+flag;
        head->val = val%10;
        flag = val/10;
        return flag;
    }
    
    ListNode* plusOne(ListNode* head) {
        if(!head) return head;
        if(DFS(head)==0) return head;
        ListNode* p = new ListNode(1);
        p->next = head;
        return p;
    }
};