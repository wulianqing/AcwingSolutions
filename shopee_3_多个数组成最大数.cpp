#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<algorithm>
using namespace std;
bool cmp(string & a,string & b){
    if(a.size() == b.size()){
        if(a.compare(b) < 0)
            return a < b;
        else if(a.compare(b) > 0)
            return a > b;
    }
    else if(a.size() < b.size()){
        string b_cross = b.substr(0, a.size());
        if(a.compare(b_cross) < 0)
            return a < b;
        else if(a.compare(b_cross) > 0)
            return a > b;
        //a == b_cross
        else{
            for (int i = a.size(); i < b.size();i++){
                if(b[i] > b[i-1]){
                    return a < b;
                    break;
                }
                else if(b[i] < b[i-1]){
                    return a < b;
                    break;
                }
                else
                    return a > b;
            }
        }
    }
    //
    else if(a.size() > b.size()){
        string a_cross = a.substr(0, a.size());
        if(b.compare(a_cross) < 0)
            return a > b;
        else if(b.compare(a_cross) > 0)
            return a < b;
        //a_cross == b
        else{
            for (int i = b.size(); i < a.size();i++){
                if(a[i] > a[i-1]){
                    return a > b;
                    break;
                }
                else if(a[i] < a[i-1]){
                    return a > b;
                    break;
                }
                else
                    return a < b;
            }
        }
    }
}
int main(){
    int n;
    cin >> n;
    vector<string> nums;
    string s;
    cin >> s;
    stringstream input(s);
    string temp;
    while(getline(input,temp,',')){
        nums.push_back(temp);
    }
    sort(nums.begin(), nums.begin() + nums.size(), cmp);
    string ans;
    for (int i = 0; i < nums.size(); i++)
    {
        ans = ans.append(nums[i]);
    }
    cout << ans << endl;
    return 0;
}