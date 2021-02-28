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
ListPtr reverseList(ListPtr head);

#include <cassert>
#include <cstdarg>
#include <cstddef>
#include <iostream>
#include <cstdlib>

using namespace std;

/* Push an element into top of the list */
ListPtr List_push(ListPtr list, int num)
{
      ListPtr new_elem = (ListPtr)malloc(sizeof(ListNode));
      if (list == nullptr) //empty list
      {
            new_elem->val = num;
            new_elem->next = nullptr;
            return new_elem;
      }
      new_elem->val = num;
      new_elem->next = list;
      return new_elem;
}

/* Length of list */
int List_length(ListPtr list)
{
      int n;
      for (n = 0; list; list = list->next)
            n++;
      return n;
}

/* Convert list to array */
int *List_toArray(ListPtr list)
{
      int i, n = List_length(list);
      int *array = (int *)malloc(n * sizeof(int));

      for (i = 0; i < n; i++)
      {
            array[i] = list->val;
            list = list->next;
      }
      return array;
}
/* Create and return a list */
ListPtr List_list(ListPtr list, int val, ...)
{
      va_list ap;
      ListPtr *p = &list;

      va_start(ap, val);
      for (; val; val = va_arg(ap, int))
      {
            *p = (ListPtr)malloc(sizeof(ListNode));
            (*p)->val = val;
            p = &(*p)->next;
      }
      *p = NULL;
      va_end(ap);
      return list;
}

/* Append 2 lists together */
ListPtr List_append(ListPtr list, ListPtr tail)
{
      ListPtr *p = &list;
      while ((*p)->next)
      {
            p = &(*p)->next;
      }

      *p = tail;
      return list;
}

/* Print number in list*/
void PrintList(ListPtr list)
{
      if (list == nullptr)
      {
            cout << "empty list" << endl;
            return;
      }
      cout << "List:";
      while (list != nullptr)
      {
            cout << list->val;
            if (list->next != nullptr)
                  cout << "->";
            list = list->next;
      }
      cout << "." << endl;
}

ListPtr reverseList(ListPtr head) //迭代
{
      ListPtr prev = nullptr;
      ListPtr curr = head;
      while (curr)
      {
            ListPtr next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
      }
      head->next = nullptr;
      return prev;
}

#endif