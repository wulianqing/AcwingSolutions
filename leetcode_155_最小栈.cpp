#include<iostream>
#include<stack>
using namespace std;
class MinStack
{
private:
    stack<int> chief_s;
    stack<int> vice_s;
public:
    /** initialize your data structure here. */
    MinStack() {
    }
    void push(int x) {
        chief_s.push(x);
        if(!vice_s.empty() && x > vice_s.top()){}
        else vice_s.push(x);
    }
    void pop() {
        if(chief_s.top() == vice_s.top())
            vice_s.pop();
        chief_s.pop();
        }
    int top() {
        return chief_s.top();
    }
    int getMin() {
        return vice_s.top();
    }
};