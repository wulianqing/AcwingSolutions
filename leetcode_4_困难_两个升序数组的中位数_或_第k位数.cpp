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
        while(left <= right ){
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
        return 0;
    }
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size();
        int n2 = nums2.size();
        if((n1 + n2) % 2 == 1)
            return findKthNumber(nums1, nums2, (n1 + n2) / 2 + 1);
        else
            return (double)(findKthNumber(nums1, nums2, (n1 + n2) / 2) + findKthNumber(nums1, nums2, (n1 + n2) / 2 + 1))/2;
    }
};
int main(){
    vector<int> nums1 = {1, 3, 7, 8};
    vector<int> nums2 = {2, 6, 9, 10, 11,12};
    vector<int> nums3 = {1, 3};
    vector<int> nums4 = {2};
    int k = 6;
    Solution solu;
    cout << solu.findKthNumber(nums1, nums2, k) << endl;
    cout << solu.findMedianSortedArrays(nums3, nums4) << endl;
    return 0;
}