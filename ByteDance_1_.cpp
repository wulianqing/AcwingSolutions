#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;
int main() {
    //unordered_map: 1:visited
    unordered_map<char,int> visited;
    visited.insert(make_pair('a',0));
    visited.insert(make_pair('b',0));
    visited.insert(make_pair('c',0));
    visited.insert(make_pair('d',0));
    string s = "tbcacbdata";
    //pionter:left , right init
    int left = 0;
    int right = 0;
    //stop: when found or traval to the end
    while(!((right == s.size()) && right == left)){
        // not in visited map
        if(visited.find(s[right]) == visited.end()){
            //cout<<s[right]<<":not in visited"<<endl;
            left = ++right;
        }
        else{
            //if current char was visited
            if(visited[s[right]] == 1){
                //move left 
                //cout<<s[right]<<" was visited"<<endl;
                while(s[left] != s[right]){
                    visited[s[left]] = 0;
                    left++;
                }
                left++;
                right++;
                //cout<<s[left]<<" "<<s[right]<<endl;
            }
            //if current char was not visited
            else{
                //cout<<"not visited: "<<s[right]<<endl;
                visited[s[right]] = 1;
                right++;
                cout<<"current length: "<<right - left<<endl;
                //if found
                if(right - left == 4){
                    cout<<left<<endl;
                    return 0;
                }
            }
        //if found: break
        }
    }
    cout<<-1<<endl;
    return 0;
}