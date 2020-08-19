#include<iostream>
#include<vector>
using namespace std;
int main(){
    vector<int> v;
    int num;
    for(int i = 0;i < num;i++)
        cin>>v[i];
    int even = 0,odd = 1;
    while(even < num && odd <num){
        //找不符合要求的偶数位置
        while(v[even] % 2 == 0)
            even += 2;
        //不符合的奇数位置
        while(v[odd] % 2 == 1)
            odd += 2;
        swap(v[even],v[odd]);
    }
    for(int i = 0;i<num;i++)
        cout<<v[i]<<' ';
    return 0;
}