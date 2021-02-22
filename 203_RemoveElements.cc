#include "List.h"
#include <iostream>

using namespace std;

/*添加哨兵节点至链表头部，所有需要删除的节点现在都处于中间节点*/

class Solution
{
public:
  ListNode *removeElements(ListNode *head, int val)
  {
    ListNode *sentinel = new ListNode(0);
    sentinel->next = head;

    ListNode *prev = sentinel, *curr = head, *toDelete = nullptr;
    while (curr != nullptr)
    {
      if (curr->val == val)
      {
        prev->next = curr->next;
        toDelete = curr;
      }
      else
        prev = curr;

      curr = curr->next;

      if (toDelete != nullptr)
      {
        delete toDelete;
        toDelete = nullptr;
      }
    }

    ListNode *ret = sentinel->next;
    delete sentinel;
    return ret;
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
  cout << "before removal:" << endl;
  PrintList(ListHead);
  cout << "------------------------begin test------------------------" << endl;
  Solution solution;
  ListHead = solution.removeElements(ListHead, 5);
  cout << "after removal:" << endl;
  PrintList(ListHead);
  return 0;
}
