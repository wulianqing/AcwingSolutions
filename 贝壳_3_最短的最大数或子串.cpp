#include<iostream>
#include<vector>
using namespace std;
int calculate_or(vector<int> v,int left,int right){
    int counter = 0;
    int mixed = 0;
    for (int i = left;i<=right;i++) 
        mixed |= v[i];
    while(mixed != 0){ 
        if (mixed & 1 == 1)
            counter++;
        mixed>>=1;
    }
    return counter;
}

int main(){
    
    int n;
    cin>>n;
    vector<int> v(n);
    for (int i = 0;i<n;i++)
        cin>>v[i];
    int left = 0, right = 0;
    int max_bit_1 = 0;
    int min_length = n;
    while(right < n){
        int cur_sum_or = calculate_or(v, left, right);
        if (cur_sum_or > max_bit_1) {
            max_bit_1 = cur_sum_or;
            min_length = right - left + 1;
        }
        if(cur_sum_or == max_bit_1){ 
            if (right - left + 1 < min_length)
                min_length = right - left + 1;
        }
        // right右移变大：右移right  
        if (calculate_or(v,left,right + 1) > calculate_or(v,left,right)){ 
            right++;
            continue;
        }
        // left右移不变：右移left
        if(left + 1 <= right && calculate_or(v,left+1,right) == calculate_or(v,left,right)){ 
            left++;
            continue;
        }
        //right右移不变大，left左移不变小:右移right
        right++;
    }

    cout<<min_length<<endl;
    return 0;
}