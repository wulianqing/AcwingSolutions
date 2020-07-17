#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
using namespace std;
class Solution
{
private:
    bool dfs(string s,unordered_map<char,vector<string>> & hm,unordered_map<string,bool> & memo){
        char first_char = s[0];
        //第一个字母 字典中没有以之为开头的
        if(hm.find(first_char) == hm.end())
            return false;
        //有以第一个字母开头的 遍历它们
        for (vector<string>::iterator it = hm[first_char].begin(); it != hm[first_char].end(); it++)
        {
            //直接完全匹配
            if(s == *it){
                memo[*it] = true;
                return true;
            }       
            //待匹配的比较长, 且前几个字母与字典当前单词匹配
            else if(s.size() > (*it).size() && s.substr(0,(*it).size()).compare(*it) == 0){
                //在memo查得到当前单词, 且能匹配
                if(memo.find(*it) != memo.end() && memo[*it] == true){
                    memo[*it] = true;
                    return true;
                }
                //memo还没有,不知道能否匹配,需要继续dfs看看
                else if(memo.find(*it) == memo.end()){
                    bool temp = dfs(s.substr((*it).size()), hm, memo);
                    memo[*it] = temp;
                    if(temp == true)
                        return true;
                }
                //memo查得到,不能匹配
                else if(memo.find(*it) != memo.end() && memo[*it] == false){
                    memo[*it] = false;
                    return false;
                }
            }
            //带匹配比已有的都短 继续遍历    
        }
        memo[s] = false;
        return false;
    }

public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_map<char, vector<string>> hm;
        unordered_map<string, bool> memo;
        for (int i = 0; i < wordDict.size(); i++)
        {
            if(hm.find(wordDict[i][0]) == hm.end()){
                vector<string> temp;
                temp.push_back(wordDict[i]);
                hm.insert(make_pair(wordDict[i][0], temp));
            }
            else
                hm[wordDict[i][0]].push_back(wordDict[i]);
        }
        return dfs(s, hm,memo);
    }
};
int main(){
    string s = "imaaronng";
    vector<string> wordDict = {"imab","im","aaron","ronng","ng"};
    Solution solu;
    cout << solu.wordBreak(s, wordDict) << endl;
    return 0;
}