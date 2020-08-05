#include<iostream>
#include<vector>
using namespace std;
struct dice{
    int top;
    int down;
    int left;
    int right;
    int front;
    int back;
};
bool operator== (dice a,dice b){
    if(a.top == b.top && a.down == b.down && a.left == b.left && a.right == b.right && a.front == b.front && a.back == b.back)
        return true;
    else
        return false;
}
void go_up(dice & a){
    int temp_5 = a.front;
    int temp_6 = a.back;
    int temp_2 = a.down;
    int temp_1 = a.up;
    a.top = temp_5;
    a.down = temp_6;
    a.front = temp_2;
    a.back = temp_1;
}
void go_down(dice & a){
    int temp_5 = a.front;
    int temp_6 = a.back;
    int temp_2 = a.down;
    int temp_1 = a.up;
    a.top = temp_6;
    a.down = temp_5;
    a.front = temp_1;
    a.back = temp_2;
}
void go_left(dice & a){
    int temp_5 = a.front;
    int temp_6 = a.back;
    int temp_3 = a.left;
    int temp_4 = a.right;
    a.left = temp_5;
    a.right = temp_6;
    a.front = temp_4;
    a.back = temp_3;
}
void go_left(dice & a){
    int temp_5 = a.front;
    int temp_6 = a.back;
    int temp_3 = a.left;
    int temp_4 = a.right;
    a.left = temp_6;
    a.right = temp_5;
    a.front = temp_3;
    a.back = temp_4;
}
