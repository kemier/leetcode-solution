#include <unordered_set>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next){}
                                                  *
};

class Solution
{
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
    {
        unordered_set<ListNode *> visited;
        ListNode *temp = headA;
        while (temp != nullptr)
        {
            visited.insert(temp);
            temp = temp->next;
        }
        temp = headB;
        while (temp != nullptr)
        {
            if (visited.count(temp))
            {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }
};

class Solution2
{
public:
    ListNode *getIntersectionNode(ListNode *headA,
                                  ListNode *headB)
    {
        if (headA == nullptr || headB == nullptr)
        {
            return nullptr;
        }
        ListNode *pA = headA, *pB = headB;
        while (pA != pB)
        {
            pA = pA == nullptr ? headB : pA->next;
            pB = pB == nullptr ? headA : pB->next;
        }
        return pA;
    }
};
