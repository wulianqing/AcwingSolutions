#include<iostream>
#include<unordered_map>
#include<string.h>
using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    int** stu_grades = new int* [n];
    for (int i = 0; i < n;i++){
        stu_grades[i] = new int[m];
    }
    int count_stu_price = 0;
    int count_stu_same_top;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m;j++){
            cin >> stu_grades[i][j];
        }
    }
    int top;//record the top grade
    int top_list[n];//serveral students have the same top grade
    unordered_map<int, int> priceowner_list; //<student,1>
    for (int i = 0; i < m;i++){
        //init
        top = 0;
        memset(top_list,-1,n);
        count_stu_same_top = 0;
        for (int j = 0; j < n; j++)
        {
            if(stu_grades[i][j]>top){
                top = stu_grades[i][j];
                memset(top_list,-1,n);
                top_list[0] = j;
                count_stu_same_top = 1;

            }
            else if(stu_grades[i][j]==top){
                top_list[count_stu_same_top] = j;
                //cout << i << " "<<j <<":="<< endl;
                count_stu_same_top++;
            }
        }
        for (int i = 0; i < count_stu_same_top;i++){
            if(priceowner_list.find(top_list[i])==priceowner_list.end()){
                priceowner_list.insert(make_pair(top_list[i], 1));
                count_stu_price++;
                //cout << top_list[i] << endl;
            }
        }
    }
    cout << count_stu_price;
    return 0;
}