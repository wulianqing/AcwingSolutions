#include<iostream>
#include<list>
#include<unordered_map>
using namespace std;

struct listNode {
    int key;
    int value;
    listNode(int k,int v){
        key = k;
        value = v;
    }
};
class LRUCache {
    
    private:
        list<listNode> lt;
        unordered_map<int, list<listNode>::iterator> ump;
        int sz;
    
    public:
        //构造函数
        LRUCache(int capability){
            sz = capability;
            lt.resize(sz,listNode(-1, -1));
         }

        //get
        int get(int k){
            //已存在: lt对应元素移到前面（lt的删除+添加）
            if(ump.find(k) != ump.end()){
                listNode temp = listNode(ump[k]->key,ump[k]->value);
                lt.erase(ump [k]);
                lt.push_front(temp);
                return temp.value;
            }
             //目前不存在: 返回-1
            return -1;
        }

        //put  ！！！！！这个写法非常重要！！！！！！
        void put(int k,int v){
            //已存在: 先删掉lt对应元素
            if(ump.find(k) != ump.end() && ump.find(k)->second != lt.end()) //&& 后面的条件 重要!!!
                lt.erase(ump[k]);
            
            //判断是不是不存在（如果经过上面删掉对应元素，而size==sz说明没经过删除，说明不存在：需要删除lt最后元素，ump也要处理）
            if(lt.size() == sz){
                ump[lt.back().key] = lt.end();
                lt.pop_back();
            }

            //添加到最前面
            lt.push_front(listNode(k,v));
            ump[k] = lt.begin();
        }
        void getState(){
            cout<<"list: ";
            for(list<listNode>::iterator it = lt.begin();it != lt.end();it++)
                cout<<'['<<it->key<<','<<it->value<<"] ";
            cout<<endl<<"hash map: ";
            for(unordered_map<int,list<listNode>::iterator>::iterator it = ump.begin();it != ump.end();it++)
                cout<<'['<<it->first<<'['<<it->second->key<<','<<it->second->value<<"]] ";
            cout<<endl;
        }
};


int main(){
    int capa; 
    cin>>capa;
    LRUCache my_lru(capa);
    string commd;
     while(cin>>commd){
        if(commd == "get"){
            int k;
            cin>>k;
            cout<<my_lru.get(k)<<endl;
            my_lru.getState();
        }
        else if(commd == "put"){
            int k,v;
            cin>>k>>v;
            my_lru.put(k,v);
            my_lru.getState();
         }
        else  if(commd == "stop")
            break;    
    }
    return 0;
}             