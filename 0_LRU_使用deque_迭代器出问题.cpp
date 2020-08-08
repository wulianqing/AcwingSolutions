#include<iostream>
#include<deque>
#include<unordered_map>
using namespace std;
struct keyValue
{
    int key;
    int value;
    keyValue(int k, int v) { key = k, value = v; }
};
class LRUCache {
private:
    int cap;
    unordered_map<int, deque<keyValue>::iterator> hm;
    deque<keyValue> q;

public:
    LRUCache(int capacity) {
        cap = capacity;
    }
    void getDeque(){
        cout << "deque: ";
        for (deque<keyValue>::iterator it = q.begin(); it != q.end(); it++)
            cout << "<" << it->key << "," << it->value << "> ";
        cout << endl;
    }
    void getHashmap(){
        cout << "hashmap: ";
        for (unordered_map<int, deque<keyValue>::iterator>::iterator it = hm.begin(); it != hm.end(); it++)
            cout << "[" << it->first << ",<" << it->second->key<<','<<it->second->value << ">] ";
        cout << endl;
    }
    int get(int key) {
        //不存在
        if(hm.find(key) == hm.end())
            return -1;
        //存在: 目标调到最前
        else{
            int ret = hm[key]->value;
            deque<keyValue>::iterator it = hm[key];
            hm.erase(key);
            q.erase(it);
            q.push_front(keyValue(key,ret));
            hm[key] = q.begin();
            return ret;
        }
    }

    void put(int key, int value) {
        //不存在: 插入到最前
        if(hm.find(key) == hm.end()){
            if(q.size() == cap){
                //删deque和hashmap
                hm.erase(hm.find(q.rbegin()->key));
                q.erase(q.end() - 1);
            }
            q.insert(q.begin(), keyValue(key,value));
            hm.insert(make_pair(key, q.begin()));
        }
        //存在: 调到最前
        else{
            deque<keyValue>::iterator temp = hm[key];
            hm.erase(key);
            q.erase(temp);
            q.push_front(keyValue(key,value)); //!!! 这一步有问题: 应该是deque内部会移动元素内容造成的
            //hm[key] = q.begin();
            
        }
    }
};
int main(){
    LRUCache lru(10);
    string s;
    while(cin>>s){
        if(s == "end")
            break;
        else if(s == "get"){
            int k;
            cin >> k;
            cout<<lru.get(k)<<endl;
            lru.getDeque();
            lru.getHashmap();
        }
        else if(s == "put"){
            int k, v;
            cin >> k >> v;
            lru.put(k, v);
            lru.getDeque();
            lru.getHashmap();
        }
        else if(s == "state"){
            lru.getDeque();
            lru.getHashmap();
        }
    }
    return 0;
}
