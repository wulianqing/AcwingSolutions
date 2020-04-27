/*
给定一个按照升序排列的长度为n的整数数组，以及 q 个查询。
对于每个查询，返回一个元素k的起始位置和终止位置（位置从0开始计数）。
如果数组中不存在该元素，则返回“-1 -1”。

输入格式
第一行包含整数n和q，表示数组长度和询问个数。
第二行包含n个整数（均在1~10000范围内），表示完整数组。
接下来q行，每行包含一个整数k，表示一个询问元素。

输出格式
共q行，每行包含两个整数，表示所求元素的起始位置和终止位置。
如果数组中不存在该元素，则返回“-1 -1”。

数据范围
1≤n≤100000
1≤q≤10000
1≤k≤10000

输入样例：
6 3
1 2 2 3 3 4
3
4
5

输出样例：
3 4
5 5
-1 -1
*/

#include<iostream>

using namespace std;

int main(){
    int counts_nums;
    cout<<"输入数组元素个数"<<endl;
    cin>>counts_nums;
    int counts_search;
    cout<<"输入要查找范围的数的个数"<<endl;
    cin>>counts_search;
    int nums[counts_nums];
    cout<<"输入数组"<<endl;
    for(int i = 0;i<counts_nums;i++){
        cin>>nums[i];
    }
    int nums_search[counts_search];
    cout<<"输入要查找范围的数"<<endl;
    for(int i = 0;i<counts_search;i++){
        cin>>nums_search[i];
    }
    cout<<"搜索结果为："<<endl;
    //搜索nums_search[i]的范围
    for(int i = 0;i<counts_search;i++){
        int left = 0;
        int right = counts_nums-1;
        int mid;
        //开始搜索
        while(left<right){
            mid = (left + right)/2;
            if(nums[mid] == nums_search[i])break;
            else if(nums[mid] > nums_search[i])right = mid;
            else left = mid + 1;
        }
        //如果找到了
        if(nums[(left+right)/2] == nums_search[i]){
            //开始左右拓展找范围
            int begin = (left+right)/2;
            int end = (left+right)/2;
            while(nums[begin]==nums_search[i])begin--;
            begin++;
            while(nums[end]==nums_search[i])end++;
            end--;
            cout<<begin<<' '<<end<<endl;
        }
        //如果找不到
        else cout<<-1<<' '<<-1<<endl;
    }
    return 0;
}
