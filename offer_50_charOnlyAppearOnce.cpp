#include<iostream>
#include<map>
using namespace std;

class Solution {
public:
    char firstUniqChar(string s) {
        //char value, if unique
        map<char,bool> my_map;
        for(int i =0;i<s.size();i++){
            //is not exist
            if(my_map.find(s[i])==my_map.end())
                my_map.insert(make_pair(s[i],true));
            //is exist
            else
                my_map.find(s[i])->second = false;
        }
        string ch_appear_once;
        for(int i = 0;i<s.size();i++){
            if(my_map[s[i]] == true)
                ch_appear_once += my_map.find(s[i])->first;
                //cout<<"insert: "<< my_map.find(s[i])->first << "\tcurrent string: "<< ch_appear_once<<endl;
        }
        return s[s.find_first_of(ch_appear_once)];
    }
};

int main(){
    string s = "leetcode";
    Solution solu;
    cout << "first position of appear-once char: " << solu.firstUniqChar(s) << endl;
    return 0;
}