#include<iostream>
#include<string>
using namespace std;

int isSpecialYear(int year){
    if(year%4 == 0)
        return 1;
    else
        return 0;
}

int main(){
    int month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; //Feb:29 in Special year
    string input;
    while(getline(cin,input)){
        int diff_days=0;
        int year1, month1, day1, date1, year2, month2, day2, date2;
        year1 = atoi((input.substr(0, 4)).c_str());
        month1 =atoi((input.substr(5, 7)).c_str());
        day1 = atoi((input.substr(8, 10)).c_str());
        date1 = atoi((input.substr(11, 12)).c_str());
        year2 = atoi((input.substr(13, 17)).c_str());
        month2 = atoi((input.substr(18, 20)).c_str());
        day2 = atoi((input.substr(21,23)).c_str());
        //compare years
        if(year1 != year2){
            int diff_year = year2 - year1-1;
            int diff_4_years = diff_year / 4;
            int left_diff_years = diff_year % 4;
            diff_days += diff_4_years * 365 * 4 + 1;
            for (int i = 0; i < left_diff_years;i++){
                if((year1+i)%4==0){
                    diff_days += 366;
                }
                else
                    diff_days += 365;
            }
            //第一年里剩余月的天数
            for (int i = month1; i < 12;i++){
                diff_days += month[i];
                if (year1%4 == 0 && i==1)
                    diff_days += 1;
            }
            //第一年当月剩余天数
            for (int i = day1; i < month[month1];i++){
                diff_days ++;
            }
            if(year1%4 == 0 && month1==1)
                diff_days += 1;
        }

        //月份之间
    }
}