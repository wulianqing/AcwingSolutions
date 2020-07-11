#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
bool operator==(vector<int>& v1,vector<int>& v2){
    if(v1.size() != v2.size())
        return false;
    else{
        for (int i = 0; i < v1.size();i++)
            if(v1[i] != v2[i])
                return false;
        return true;
    }
}
int main(){
    unordered_map<vector<int>, bool> hm;
    vector<vector<int>> v = {{1, 2, 3}, {1, 2}, {1, 2, 3}};
    for (int i = 0; i < v.size(); i++)
        if(hm.find(v[i]) == hm.end())
            hm[v[i]] = true;
    for (unordered_map<vector<int>, bool>::iterator it; it != hm.end();it++){
        for (int i = 0; i < it->first.size();i++)
            cout << it->first[i] << ",";
        cout << ": " << it->second << endl;
    }
    return 0;
}