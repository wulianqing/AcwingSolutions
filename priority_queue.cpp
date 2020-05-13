#include<iostream>
#include<vector>
#include<queue>

int main(){
    std::priority_queue<int, std::vector<int>, std::greater<int> > my_pri_que;
    my_pri_que.push(4);
    my_pri_que.push(7);
    my_pri_que.push(3);
    while(!my_pri_que.empty()){
        std::cout << my_pri_que.top() << std::endl;
        my_pri_que.pop();
    }
    return 0;
}