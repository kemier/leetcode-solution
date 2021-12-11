#include "List.h"
#include <vector>
#include <iostream>
using namespace std;

class Solution //将值复制到数组中后用双指针法  时间复杂度：O(n)  空间复杂度：O(n)
{
public:
    vector<int> vals;
    bool isPalindrome(ListNode *head)
    {
        while (head != nullptr)
        {
            vals.emplace_back(head->val);
            head = head->next;
        }
        for (int i = 0, j = (int)vals.size() - 1; i < j; ++i, --j)
        {
            if (vals[i] != vals[j])
            {
                return false;
            }
        }
        return true;
    }
};

class Solution2 //递归 时间复杂度：O(n)  空间复杂度：O(n)
{
    ListNode *frontPointer;

public:
    bool recursivelyCheck(ListNode *currentNode)
    {
        if (currentNode != nullptr)
        {
            if (!recursivelyCheck(currentNode->next))
            {
                return false;
            }
            if (currentNode->val != frontPointer->val)
            {
                return false;
            }
            frontPointer = frontPointer->next;
        }
        return true;
    }

    bool isPalindrome(ListNode *head)
    {
        frontPointer = head;
        return recursivelyCheck(head);
    }
};

class Solution3 //快慢指针  时间复杂度：O(n)  空间复杂度：O(1)
{
public:
    bool isPalindrome(ListNode *head)
    {
        if (head == nullptr)
        {
            return true;
        }

        // 找到前半部分链表的尾节点并反转后半部分链表
        // PrintList(head);
        ListNode *firstHalfEnd = endOfFirstHalf(head);
        ListNode *secondHalfStart = reverseList(firstHalfEnd->next);
        // PrintList(head);
        // 判断是否回文
        ListNode *p1 = head;
        ListNode *p2 = secondHalfStart;
        bool result = true;
        while (result && p2 != nullptr)
        {
            if (p1->val != p2->val)
            {
                result = false;
            }
            p1 = p1->next;
            p2 = p2->next;
        }

        // 还原链表并返回结果
        firstHalfEnd->next = reverseList(secondHalfStart);
        // PrintList(head);
        return result;
    }

    ListNode *endOfFirstHalf(ListNode *head)
    {
        ListNode *fast = head;
        ListNode *slow = head;
        while (fast->next != nullptr && fast->next->next != nullptr)
        {
            fast = fast->next->next;
            slow = slow->next;
        }
        return slow;
    }
};

int main()
{
    ListNode *head = nullptr;
    head = List_push(head, 10);
    head = List_push(head, 6);
    head = List_push(head, 1);
    head = List_push(head, 2);
    head = List_push(head, 2);
    head = List_push(head, 1);
    head = List_push(head, 6);
    head = List_push(head, 10);
    Solution3 solution;
    cout << boolalpha << solution.isPalindrome(head) << endl;
    return 0;
}