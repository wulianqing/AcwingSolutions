#include <iostream>

int HammingDistance(int a,int b){
    int big, small;
    int counter=0;
    if (a > b)
    {
        big = a;
        small = b;
    }
    else{
        big = b;
        small = a;
    }
    while(big!=0){
        if((big&1)^(small&1))
            counter++;
        big >>= 1;
        small >>= 1;
    }
    return counter;
}

int main(){
    int max_distance=0;
    int num_count;
    std::cin >> num_count;
    if(num_count== 0 || num_count == 1)
        std::cout << 0 << std::endl;
    int nums[num_count];
    for (int i = 0; i < num_count;i++){
        std::cin >> nums[i];
    }
    for (int i = 0; i < num_count;i++){
        for (int j = i + 1; j < num_count;j++){
            if(HammingDistance(nums[i],nums[j])>max_distance)
                max_distance = HammingDistance(nums[i], nums[j]);
        }
    }
    std::cout << max_distance << std::endl;
    return 0;
}
