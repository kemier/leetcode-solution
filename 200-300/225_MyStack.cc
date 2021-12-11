#include "list/list.h"
#include <iostream>

using namespace std;

class MyStack
{
public:
    /** Initialize your data structure here. */
    MyStack()
    {
    }

    /** Push element x onto stack. */
    void push(int x)
    {
        list.insertAsFirst(x);
    }

    /** Removes the element on top of the stack and returns that element. */
    int pop()
    {
        return list.remove(list.first());
    }

    /** Get the top element. */
    int top()
    {
        return list.first()->data;
    }

    /** Returns whether the stack is empty. */
    bool empty()
    {
        return list.empty();
    }

private:
    List<int> list;
};

int main()
{
    MyStack *obj = new MyStack();
    obj->push(3);
    cout << obj->pop() << endl;
    obj->push(10);
    cout << obj->top() << endl;
    cout << boolalpha << obj->empty() << endl;
    obj->pop();
    cout << boolalpha << obj->empty() << endl;
    return 0;
}
