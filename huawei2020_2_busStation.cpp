#include<iostream>
#include<string>
#include<unordered_map>

using namespace std;
int main(){
    string station_pos_0;
    string lamp_pos_0;
    cin>>station_pos_0>>lamp_pos_0;
    char* station_pos = (char*)station_pos_0.c_str();
    char *lamp_pos = (char*)lamp_pos_0.c_str();
    int max_distance=0;
    unordered_map<int, int> station, lamp;
    const char *d = ",";
    char *p;
    p = strtok(station_pos, d);
    while(p){
        //cout << p << endl; 
        station.insert(make_pair(atoi(p),1));
        p = strtok(NULL, d);
    }
    
    p = strtok(lamp_pos, d);
    while(p){
        //cout << p << endl;
        lamp.insert(make_pair(atoi(p),1));
        p = strtok(NULL, d);
    }

    //遍历所有车站
    for (unordered_map<int,int>::iterator it = station.begin(); it != station.end();it++){
        int distance=0;
        //车站有灯
        if (lamp.find(it->first) != lamp.end())
        {
            continue;
        }
        //车站没灯
        else{
            //找最近灯
            for (int left = it->first - 1, right = it->first + 1; 1;left--,right++)
            {
                if((lamp.find(left) == lamp.end()) && (lamp.find(right) == lamp.end())){
                    distance++;
                }
                else{
                    distance++;
                    break;
                }
            }
            if(distance > max_distance)
                max_distance = distance;
        }
    }
    cout << max_distance << endl;
    return 0;
}