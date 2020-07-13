#include<iostream>
#include<vector>
using namespace std;
class Solution{
public:
    int trap(vector<int>& height) {
        int n = height.size();
        int counter = 0;
        vector<int> left_max(n);
        vector<int> right_max(n);
        //先建立right_max
        for (int i = n - 1; i >= 0;i--)
        {
            if(i == n - 1)
                right_max[i] = height[i];
            else
                right_max[i] = max(height[i], right_max[i + 1]);
        }
        //left_max的建立和water_counter的遍历一起进行
        for (int i = 0; i < n; i++)
        {
            if(i == 0)
                left_max[i] = height[i];
            if (i - 1 >= 0 && i + 1 < n)
            {
                int diff = min(left_max[i - 1], right_max[i + 1]) - height[i];
                if (diff > 0)
                    counter += diff;
                left_max[i] = max(height[i], left_max[i - 1]);
            }
        }
        return counter;
    }
};
int main(){
    vector<int> height = {2,0,2};
    Solution solu;
    cout << solu.trap(height) << endl;
    return 0;
}