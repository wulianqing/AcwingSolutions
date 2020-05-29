#include<iostream>
#include<map>
using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::map;
using std::multimap;
using std::string;
/*
map的用法: map, multimap, unordered_map, ordered_map
测试内容:
multimap是否有count
*/
int main()
{
    multimap<int, string> mul_map;
    //不能这样插入mul_map[1] = "Jimmy",因为multimap允许多个,二义性
    mul_map.insert(make_pair(1, "Jimmy"));
    mul_map.insert(make_pair(2, "Bob"));
    mul_map.insert(make_pair(3, "Aaron"));
    mul_map.insert(make_pair(4, "Lisa"));
    mul_map.insert(make_pair(4, "Lisa"));
    mul_map.insert(make_pair(4, "Mike"));
    //count():只能按key
    cout<<"number of element with key of 4: "<<mul_map.count(4)<<endl;
    multimap<int, string>::iterator it = mul_map.find(4);
    for (int i = 0; i < mul_map.count(4);i++){
        cout << it->second << endl;
        it++;
    }
    return 0;
}