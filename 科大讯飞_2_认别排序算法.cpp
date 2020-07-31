#include<iostream>
#include<vector>
using namespace std;

void quickSort(vector<int> & nums,int begin,int end){
    if(begin < end){
        int pivot = nums[begin];
        int left = begin;
        int right = end;
        while(left < right){
            while(left<right && nums[right]>=pivot)
                right--;
            while(left<right && nums[left]<=pivot)
                left++;
            if(nums[left]>nums[right])
                swap(nums[left],nums[right]);
        }
        swap(nums[begin],nums[left]);
        for (int i = 0; i < nums.size()-1;i++)
            cout << nums[i] << ' ';
        cout << nums[nums.size()-1]<<endl;
        quickSort(nums, begin, left - 1);
        quickSort(nums,left+1,end);
    }
}

int main(){
    int number;
    cin>>number;
    vector<int> nums(number);
    for(int i = 0;i<number;i++)
        cin>>nums[i];
    quickSort(nums,0,number-1);
    return 0;
}