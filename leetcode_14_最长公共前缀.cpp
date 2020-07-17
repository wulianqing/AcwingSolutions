#include<iostream>
#include<string>
#include<vector>
using namespace std;
class Solution
{
public:
    string longestCommonPrefix(vector<string>& strs) {
        string ans = "";
        if(strs.size() == 0)
            return ans;
        //i:表示第i个字符，j表示第j个字符串
        for(int i = 0;;i++){
            for(int j = 0;j<strs.size();j++){
                if(i >= strs[j].size() || (i < strs[j].size() && strs[0][i] != strs[j][i]))
                    return ans;
            }
            ans = ans + strs[0][i];
        }
        return ans;
    }
};
int main(){
    vector<string> strs = {"abc", "abb"};
    Solution solu;
    cout << solu.longestCommonPrefix(strs) << endl;
    return 0;
}