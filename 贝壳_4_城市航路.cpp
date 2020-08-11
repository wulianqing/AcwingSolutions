#include<iostream>
#include<vector>
using namespace std;
int C_a_b(int a,int b){
    if (a-b < b)
        b = a-b;
    int ret = 1;
    for (int i = 0;i < b;i++)
        ret *= a--;
    for (;b >= 2;b--)
        ret /= b;
    return ret;
}
int main(){
    
}