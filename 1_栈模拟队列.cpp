#include<iostream>
#include<stack>
using namespace std;

class my_queue{
    private:
    stack<int> stack_1;
    stack<int> stack_2;
    public:
    void push(int n){
        stack_1.push(n);
    }
    bool pop(){
        if(!stack_2.empty()){
            stack_2.pop();
            return true;
        }
        else{
            if(!stack_1.empty()){
                while(!stack_1.empty()){
                    stack_2.push(stack_1.top());
                    stack_1.pop();
                }
                stack_2.pop();
                return true;
            }
            else
                return false;
        }
    }
    int front(){
        if(!stack_2.empty()){
            return stack_2.top();
        }
        else{
            if(!stack_1.empty()){
                while(!stack_1.empty()){
                    stack_2.push(stack_1.top());
                    stack_1.pop();
                }
                return stack_2.top();
            }
            else
                cout << "error: queue is empty" << endl;
            return -1;
        }
    }
};

int main(){
    my_queue q;
    cout << q.front() << endl;
    q.push(1);
    q.push(2);
    q.push(3);
    cout << q.front()<<endl;
    q.push(4);
    q.pop();
    cout << q.front()<<endl;
    q.pop();
    q.pop();
    cout << q.front()<<endl;
    return 0;
}