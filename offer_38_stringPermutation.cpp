#include<iostream>
#include<vector>
#include<string>
#include<map>
using namespace std;
class Solution
{
public:
    void backTrack(string s,vector<string> & ans,map<string,int> & assistant_map){
        if(s.size() == 0)
            return;
        for (int i = 0; i < s.size();i++){
            string temp = s[i];
            backTrack(s.erase(i),ans,assistant_map)
        }
    }
    vector<string> permutation(string s) {
        vector<string> ans;
        map<string, int> assistant_map;
        
    }
};