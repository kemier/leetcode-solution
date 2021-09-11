#include "List.h"
#include <iostream>

using namespace std;

class Solution
{
public:
    ListNode *reverseList(ListNode *head) //迭代
    {
        ListNode *prev = nullptr;
        ListNode *curr = head;
        while (curr)
        {
            ListNode *next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }

    ListNode *reverseList2(ListNode *head) //递归
    {
        if (!head || !head->next)
        {
            return head;
        }
        ListNode *newHead = reverseList2(head->next);
        head->next->next = head;
        head->next = nullptr;
        return newHead;
    }
};

int main()
{
    ListPtr ListHead = nullptr;
    ListHead = List_push(ListHead, 10);
    ListHead = List_push(ListHead, 20);
    ListHead = List_push(ListHead, 5);
    ListHead = List_push(ListHead, 4);
    ListHead = List_push(ListHead, 2);
    ListHead = List_push(ListHead, 100);
    ListHead = List_push(ListHead, 5);
    ListHead = List_push(ListHead, 7);
    cout << "before action:" << endl;
    PrintList(ListHead);
    cout << "------------------------begin test------------------------" << endl;
    Solution solution;
    ListHead = solution.reverseList(ListHead);
    cout << "after action:" << endl;
    PrintList(ListHead);
    return 0;
}