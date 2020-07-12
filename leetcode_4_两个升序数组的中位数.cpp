#include<iostream>
#include<vector>
using namespace std;
class Solution
{
public:
    int findKthNumber(vector<int>& nums1,vector<int> & nums2,int k){
        int n = nums1.size();
        if (k <= nums2.size() && nums1[0] > nums2[k - 1])
            return nums2[k - 1];
        if(nums1[nums1.size() - 1] < nums2[k - n -1])
            return nums2[k - n - 1];
        int left = 0, right = n - 1;
        int mid;
        while(left < right){
            mid =  left + (right - left) / 2;
            if(nums1[mid - 1] > nums2[k - mid - 1]){
                right = mid;
                continue;
            }
            if(nums1[mid] < nums2[k - mid - 2]){
                left = mid + 1;
                continue;
            }
            return min(nums1[mid], nums2[k - mid - 1]);
        }
    }
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        
    }
};
int main(){
    vector<int> nums1 = {1, 3, 7, 8};
    vector<int> nums2 = {2, 6, 9, 10, 11};
    int k = 4;
    Solution solu;
    cout << solu.findKthNumber(nums1, nums2, k) << endl;
    return 0;
}