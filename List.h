#ifndef __LIST_H__
#define __LIST_H__

typedef struct ListNode
{
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
} List, *ListPtr;

ListPtr List_push(ListPtr list, int num);
int List_length(ListPtr list);
int *List_toArray(ListPtr list);
ListPtr List_append(ListPtr list, ListPtr tail);
ListPtr List_list(ListPtr list, void *val, ...);
void PrintList(ListPtr list);
/* TODO */
ListPtr List_copy(ListPtr list);
int List_pop(ListPtr *list);

#endif