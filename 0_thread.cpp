#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
using namespace std;

mutex mtx;
condition_variable cond;
int flag = 0;

void hello(int num){
    for (int i = 0; i < 5;i++){
        unique_lock<mutex> ul(mtx);
        cond.wait(ul, [&]() { return flag == num; });
        cout<< "thread " << num << ": hello thread world!" << endl;
        flag = (flag + 1) % 2;
        cond.notify_all();
    }
}

int main(){
    thread t1(hello, 0);
    thread t2(hello, 1);
    //hello(0);
    t1.join();
    t2.join();
}