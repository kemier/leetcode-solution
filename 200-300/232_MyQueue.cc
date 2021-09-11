#define DSA_STACK_VECTOR

#include "stack/stack.h"
#include <iostream>

using namespace std;

class MyQueue
{
public:
    /** Initialize your data structure here. */
    MyQueue()
    {
    }

    /** Push element x to the back of queue. */
    void push(int x)
    {
        while (!s1.empty())
            s2.push(s1.pop());
        s2.push(x);
        while (!s2.empty())
            s1.push(s2.pop());
    }

    /** Removes the element from in front of queue and returns that element. */
    int pop()
    {
        if (!s1.empty())
            return s1.pop();
    }

    /** Get the front element. */
    int peek()
    {
        if (!s1.empty())
            return s1.top();
    }

    /** Returns whether the queue is empty. */
    bool empty()
    {
        return s1.empty();
    }

private:
    Stack<int> s1;
    Stack<int> s2;
};

int main()
{

    MyQueue *obj = new MyQueue();
    cout << boolalpha << obj->empty() << endl;
    obj->push(10);
    obj->push(2);
    cout << obj->peek() << endl;
    obj->push(11);
    cout << obj->pop() << endl;
    cout << obj->peek() << endl;
    cout << boolalpha << obj->empty() << endl;
    cout << obj->pop() << endl;
    cout << obj->pop() << endl;
    cout << boolalpha << obj->empty() << endl;
    return 0;
}