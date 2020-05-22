#include<iostream>
#include<vector>
#include<algorithm>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct DATA_t{
    int key;
    int value;
    DATA_t(int a=0,int b=0){
        key = a;
        value = b;
    }
    void setData(int a,int b){
        key = a;
        value = b;
    }
};

//comparer of std::sort, parameter need &
bool comparer(DATA_t & a,DATA_t & b){
        return a.value < b.value;
}

int main()
{
    //init: build the vector of DATA_t
    vector<DATA_t> datas;
    cout << "length of datas" << endl;
    int length_datas;
    cin >> length_datas;
    for (int i = 0; i < length_datas;i++){
        int a, b;
        cin >> a >> b;
        datas.push_back(DATA_t(a, b));
    }

    //put those key==0 to the end of vector
    int counter_zero = 0;
    vector<DATA_t>::iterator it = datas.begin();

    for (int i = 0; i < length_datas; i++)
    {
        //key==0的项会被交换到最后,后面的前移,故而it会原来指向原来的下一项,不用再++
        if (it->key == 0){
            int temp_key = it->key;
            int temp_value = it->value;
            datas.erase(it);
            datas.push_back(DATA_t(temp_key,temp_value));
            counter_zero++;
        }
        else
            it++; 
    }

    //sort those key!=0
    //注意compare()的写法,需要加引用
    std::sort(datas.begin(), datas.begin() + (length_datas - counter_zero + 1), comparer);

    //check algorithm
    cout <<"counter_zero: "<<counter_zero << endl;
    for (int i = 0; i < length_datas; i++)
    {
        cout << datas[i].key << ' '<<datas[i].value<<endl;
    }
    return 0;
}
