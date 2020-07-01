/* worst:O(log n)*/

#include<iostream>

int main(){
    int num_length;
    std::cin >> num_length;
    int* nums = new int[num_length];
    for (int i = 0; i < num_length;i++){
        std::cin >> nums[i];
    }
    int target;
    std::cin >> target;
    int left = 0, right = num_length - 1;
    int mid;
    while(left<right){
        //+ 1:Otherwise can not pick the last number when numbers are equal
        mid = left + (right - left) / 2 + 1; 
        //target is in left part
        if(nums[mid] > target){
            right = mid - 1;
        }
        //in right part
        else{
            left = mid;
        }
    }
    //left == right, maybe not found
    if(nums[left]==target)
        std::cout << mid << std::endl;
    else
        std::cout << "not fount\n";
    return 0;
}