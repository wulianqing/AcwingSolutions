#include<iostream>
#include<string>
#include<unordered_map>
using namespace std;

class Solution {
public:
    bool isMatched(string s,unordered_map<char,bool> & ump){
        for (int i = 0; i < s.size();i++){
            if(ump[s[i]] == true)
                return false;
        }
        return true;
    }

    int getMaxMul(string str) {
        // write code here
        unordered_map<char,bool> ump;
        int counter_char = 0;
        //统计出现的字母
        for (int i = 0; i < str.size(); i++)
        {
            if (ump.find(str[i]) == ump.end()){
                ump.insert(make_pair(str[i],false));
                counter_char++;
            }
        }

        int max_multi = 0;
        int n = str.size();
        //先取一个子串，统计用了几个字母，剩下几个可用，用可用的最长能多长，更新max_multi
        for (int left = 0; left < n - 1;left++){
            for (int right = left; right < n - 1;right++){
                //刷新哈希表
                for (unordered_multimap<char, bool>::iterator it = ump.begin(); it != ump.end();it++)
                    it->second = false;
                //统计第一个子串用了几个字符
                for (int i = left; i <= right;i++)
                    ump[str[i]] = true;
                //第一个子串的长度
                int length_1 = right - left + 1;
                //看第二个是不是匹配
                int max_length_second = 0;
                for (int k = right + 1; k < n; k++)
                {
                    for (int l = n - 1; l >= k;l--){
                        //剪枝
                        if(l - k + 1 <= max_length_second)
                            break;
                        else{
                            string temp_str = str.substr(k, l + 1);
                            if (isMatched(temp_str,ump))
                                if(temp_str.size() > max_length_second)
                                    max_length_second = temp_str.size();
                        }
                    }
                }
                //看是否更新最大乘积
                if(length_1 * max_length_second > max_multi)
                    max_multi = length_1 * max_length_second;
            }
        }
        return max_multi;
    }
};

int main(){
    Solution solu;
    //string s = "adcbadcbedbadedcbacbcadbc";
    string s = "abcde";
    cout << solu.getMaxMul(s) << endl;
}
