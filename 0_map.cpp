#include<iostream>
#include<map>
#include<string>
using namespace std;
int main(){
    map<int,string> m;
    m[1] = "Apple";
    m[5] = "Busket";
    m[3] = "Cannon";
    for(map<int, string>::iterator it = m.begin(); it != m.end();it++)
        cout << it->first <<" "<< it->second << endl;
    for(map<int, string>::iterator it = m.begin(); it != m.end(); )
        m.erase(it++);
    for(map<int, string>::iterator it = m.begin(); it != m.end();it++)
        cout << it->first <<" "<< it->second << endl;    
    if(m.empty() == true)
        cout << "map is empty now." << endl;
    return 0;
}