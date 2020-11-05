#include<iostream>
#include<vector>
#include<time.h>
#include<stdlib.h>

int main(){
    std::vector<std::string> menu = {
        "忆聚香鸡公煲",
        "杨铭宇黄焖鸡",
        "濠尚牛肉粿条",
        "芳芳餐厅",
        "张老坎儿麻辣烫",
        
        "忆聚香鸡公煲",
        "杨铭宇黄焖鸡",
        "濠尚牛肉粿条",
        "芳芳餐厅",
        "张老坎儿麻辣烫",

        "小南国",
        "食堂猪脚饭",
        "快乐川菜",
        "啵啵鱼"
    };
    srand((unsigned)time(NULL));
    std::cout << "输入1以随机输出今天吃什么/输入0以结束程序:" << std::endl;
    int input;
    while(std::cin >> input)    
        std::cout << menu[rand() % menu.size()] << std::endl;
    return 0;
}
