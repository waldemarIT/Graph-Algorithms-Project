#pragma once

struct slistEl
{
    slistEl* next;
    int v;
};

class Queue
{
private:
    slistEl* head;
    slistEl* tail;
   static const int MAXINT = -2147483647;


public:
    Queue();      
    ~Queue();    
    bool empty(void);
    int  front(void);
    void push(int v);
    void pop(void);
};

