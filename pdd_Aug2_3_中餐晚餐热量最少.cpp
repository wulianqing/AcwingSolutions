#include<iostream>
#include<vector>
#include<algorithm>
#include<limits.h>
using namespace std;
struct food{
    int energy;
    int taste_value;
};
bool cmp(food a,food b){
    if(a.taste_value < b.taste_value)
        return true;
    else if(a.taste_value > b.taste_value)
        return false;
    //taste_value ==
    else{
        if(a.energy > b.energy)
            return true;
        else
            return false;
    }
}
int main()
{
    int lunch_kinds, dinner_kinds, value;
    cin >> lunch_kinds >> dinner_kinds >> value;

    //init
    vector<food> lunch(lunch_kinds);
    vector<food> dinner(dinner_kinds);
    for(int i = 0;i<lunch_kinds;i++)
        cin >> lunch[i].energy >> lunch[i].taste_value;
    for (int i = 0; i < dinner_kinds;i++)
        cin >> dinner[i].energy >> dinner[i].taste_value;

    //exception: value == 0
    if (value == 0)
    {
        cout << 0 << endl;
        return 0;
    }

    //sort
    sort(lunch.begin(), lunch.begin() + lunch_kinds, cmp);
    sort(dinner.begin(), dinner.begin() + dinner_kinds, cmp);

    //
    int least_value = INT_MAX;

    //only lunch
    for (int i = lunch_kinds - 1; i >= 0;i--){
        if(lunch[i].taste_value >= value)
            if(lunch[i].energy < least_value)
                least_value = lunch[i].energy;  
        //taste_value < value
        else
            break;
    }

    //only dinner
    for (int i = dinner_kinds - 1; i >= 0;i--){
        if(dinner[i].taste_value >= value)
            if(dinner[i].energy < least_value)
                least_value = dinner[i].energy;  
        //taste_value < value
        else
            break;
    }

    //both lunch & dinner
    for (int i = dinner_kinds - 1; i >= 0;i--){
        for (int j = lunch_kinds - 1; j >= 0;j--){
            if(dinner[i].taste_value + lunch[j].taste_value >= value){
                if(dinner[i].energy + lunch[j].energy < least_value)
                    least_value = dinner[i].energy + lunch[j].energy;    
            }
            else
                break;
        }
        continue;
    }
    if(least_value == INT_MAX)
        cout << -1 << endl;
    else 
        cout << least_value << endl;
    return 0;
}