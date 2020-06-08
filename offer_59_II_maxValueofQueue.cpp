#include<iostream>
#include<deque>
#include<queue>
using namespace std;

class MaxQueue {
public:
    MaxQueue() {
    }

    int max_value() {
        if(q.size() == 0)
            return -1;
        return dq.front();
    }

    void push_back(int value) {
        q.push(value);
        while (!dq.empty() && dq.back() < value)
            dq.pop_back();
        dq.push_back(value);
    }

    int pop_front() {
        if(q.size() == 0)
            return -1;
        int temp = q.front();
        if (q.front() == dq.front())
            q.pop(), dq.pop_front();
        else
            q.pop();
        return temp;
    }

public:
    deque<int> dq;
    queue<int> q;
};

int main(){
    MaxQueue my_queue;
    cout << my_queue.max_value() << endl;
    my_queue.push_back(1);
    my_queue.push_back(3);
    cout << "1,3: " << my_queue.max_value() << endl;
    my_queue.push_back(2);
    cout << "1,3,2: " << my_queue.max_value() << endl;
    cout << "pop: " << my_queue.pop_front() << endl;
    cout << "3,2: " << my_queue.max_value() << endl;
    cout << "pop: " << my_queue.pop_front() << endl;
    cout << "2: " << my_queue.max_value() << endl;
    cout << "pop: " << my_queue.pop_front() << endl;
    cout << "pop: " << my_queue.pop_front() << endl;
    return 0;
}