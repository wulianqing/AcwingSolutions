#include<iostream>
#include<vector>

int main(){
    std::vector<int> v = {1, 3, 2, 4, 5, 7};
    int even = 0, odd = 0;

    //find the first even num
    while(v[even] % 2 == 1)
        even++;
    
    odd = even;
    while(odd < v.size()){
        //find odd number
        while(v[odd] % 2 == 0)
            odd++;

        int temp_odd = v[odd];
        for (int i = odd; i > even && i > 0;i--)
            v[i] = v[i - 1];
        v[even] = temp_odd;
        even++;
        odd++;
    }
    for (int i = 0; i < v.size();i++)
        std::cout << v[i] << ' ';
    std::cout << std::endl;
    return 0;
}