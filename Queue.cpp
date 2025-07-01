#include <iostream>
#include "Queue.h"
using namespace std;

Queue::Queue()
{
    head = tail = NULL;
}

Queue::~Queue()
{
    while (head) pop();
}


bool Queue::empty(void)
{
    return !head;
}

int Queue::front(void)
{
    if (head) return head->v;
    else return -MAXINT;
}

void Queue::push(int v)
{
    slistEl* p = new slistEl;
    p->next = NULL;
    p->v = v;
    if (tail) tail->next = p;
    else     head = p;
    tail = p;
}

void Queue::pop(void)
{
    if (head)
    {
        slistEl* p = head;
        head = head->next;
        if (!head) tail = NULL;
        delete p;
    }
}

