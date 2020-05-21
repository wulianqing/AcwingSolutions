#include<iostream>

int main(){
    int num_length;
    std::cin >> num_length;
    int nums[num_length];
    for (int i = 0; i < num_length;i++){
        std::cin >> nums[i];
    }
    int target;
    std::cin >> target;
    int left = 0, right = num_length - 1;
    int mid;
    while(left<right){
        mid = left + (right - left) / 2;
        if(nums[mid] == target){
            while (nums[mid] == target)
                mid++;
            std::cout<<mid - 1<<std::endl;
            return 0;
        }
        //target is in right part
        else if(nums[mid] < target){
            left = mid + 1;
        }
        //in left part
        else{
            right = mid;
        }
    }
    //left == right,maybe not found
    if(nums[mid]==target)
        std::cout << mid << std::endl;
    else
        std::cout << "not fount\n";
    return 0;
}