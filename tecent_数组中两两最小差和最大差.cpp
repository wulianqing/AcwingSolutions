#include<iostream>
#include<limits.h>
using namespace std;
int main(){
    int counts;
    cout<<"输入数组元素个数"<<endl;
    while(cin>>counts){
        int nums[counts];
        cout<<"输入数组"<<endl;
         for(int i = 0;i<counts;i++){
            cin>>nums[i];
            }
        int min = INT_MAX;
        int min_pair=0;
        int max = -1;
        int max_pair=0;
        for(int i=0;i<counts;i++){
        for(int j=i+1;j<counts;j++){
            if(abs(nums[i]-nums[j])<min){
                min = abs(nums[i]-nums[j]);
                min_pair =1;
            }
            else if(abs(nums[i]-nums[j]) == min)min_pair++;
            if(abs(nums[i]-nums[j])>max){
                max = abs(nums[i]-nums[j]);
                max_pair = 1;
            }
            else if(abs(nums[i]-nums[j]) == max)max_pair++;
        }
    }
    cout<<min_pair<<' '<<max_pair<<endl;
    }

    return 0;
}