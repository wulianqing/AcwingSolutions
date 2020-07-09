#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
using namespace std;
class Solution
{
public:
    int respace(vector<string>& dictionary, string sentence) {
        int length = sentence.size();
        unordered_map<char, vector<string>> hm;
        vector<int> dp(length + 1); //dp[0]无意义,只是为了方便统一边界, dp从1开始
        dp[0] = 0;
        //build hashmap
        for (vector<string>::iterator it = dictionary.begin(); it != dictionary.end();it++){
            //found
            if(hm.find((*it)[0]) != hm.end()){
                //insert
                hm[(*it)[0]].push_back(*it);
            }
            //not found
            else{
                vector<string> temp;
                temp.push_back(*it);
                hm.insert(make_pair((*it)[0],temp));
            }
        }
        //calculate dp[i]
        for (int i = 1; i <= length;i++){
            //先假设没有匹配,后面如果当前字符能匹配,会覆盖掉
            dp[i] = dp[i - 1] + 1;
            //当前字符及后续字符串是否能匹配, 注意dp i==1 在sentence就是i == 0
            //found
            if(hm.find(sentence[i-1]) != hm.end()){
                //遍历对应以sentence[i-1]为首的单词,即vector<string>
                vector<string> &temp_vector = hm[sentence[i - 1]];
                int length_cur_vector = temp_vector.size();
                for (int j = 0; j < length_cur_vector;j++){
                    //sentense与vector里面的string对比
                    //如果相等,相等compare()返回0
                    if(sentence.substr(i - 1, temp_vector[j].size()).compare(temp_vector[j]) == 0){
                        //dp[i]~dp[i+ n - 1] = dp[i-1]
                        for (int k = i; k < i + temp_vector[j].size();k++)
                            dp[k] = dp[i - 1];
                        //直接跳过
                        i = i + temp_vector[j].size() - 1;
                    }
                }
            }
        }
        return dp[length];
    }
};
int main(){
    vector<string> dictionary = {"frrrbbrrbfrfqqbbbrb","qr","b","rf","qqbbbbfrqbrrqrffbrqqqbqqfqfrr","ffqq","bffbqfqqbrrrf","fq","qfr","fr","rqrrbfbfq","r","qbqbrbrbqfqbbbfbbbfbq","bqqbbbqrbbrf","f"};
    string sentence = "bqqffbqbbfqrfrrrbbrrbfrfqqbbbrbfqfffffrfqfqfffffrrfqfrrqbqfrbfrqqrfrbrbbqbqbqqfqrfbfrfr";
    Solution solu;
    cout << solu.respace(dictionary, sentence) << endl;
    return 0;
}
/*
["frrrbbrrbfrfqqbbbrb","qr","b","rf","qqbbbbfrqbrrqrffbrqqqbqqfqfrr","r","ffqq","bffbqfqqbrrrf","fq","qfr","fr","rqrrbfbfq","r","f","qbqbrbrbqfqbbbfbbbfbq","bqqbbbqrbbrf","f"]
"bqqffbqbbfqrfrrrbbrrbfrfqqbbbrbfqfffffrfqfqfffffrrfqfrrqbqfrbfrqqrfrbrbbqbqbqqfqrfbfrfr"
*/