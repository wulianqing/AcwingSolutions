#include<iostream>
using namespace std;

void quickSort(int* nums,int begin,int end){
    if(begin < end){
        int pivot = nums[begin];
        int left = begin;
        int right = end;
        while(left < right){
            while(left<right && nums[right]>=pivot)right--;
            while(left<right && nums[left]<=pivot)left++;
            if(nums[left]>nums[right])swap(nums[left],nums[right]);
        }
        swap(nums[begin],nums[left]);
        quickSort(nums,begin,left-1);
        quickSort(nums,left+1,end);
    }
}

int main(){
    int number;
    cout<<"输入数组元素个数"<<endl;
    cin>>number;
    int nums[number];
    cout<<"输入数组元素"<<endl;
    for(int i = 0;i<number;i++){
        cin>>nums[i];
    }
    quickSort(nums,0,number-1);
    for(int i = 0;i<number;i++){
        cout<<nums[i]<<' ';
    }
    return 0;
}