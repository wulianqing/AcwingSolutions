#include<iostream>
#define BSIZE 10

//判断bit[i]是否为1
unsigned long bitmap[BSIZE] = {1, 0 ,1 ,1 ,1 , 0, 1, 1, 0, 0};
#define IFBITISONE(i) (bitmap[i] == 1 ? true : false)

int main()
{
    int bitmap_2[5] = {1, 2, 3, 4, 5};

    std::cout << "#define: " << IFBITISONE(4) << std::endl;

    auto fun = [](int i, int bitmap[]) { return bitmap[i]; };
    std::cout << "lambda: " << fun(4, bitmap_2) << std::endl;

    std::cout << "lambda directly: " << [](int i, int bitmap[]) { return bitmap[i]; }(3, bitmap_2) << std::endl;

    //腾讯面试题
    std::cout << (long)((int *)0 + 32) << std::endl;
    long a = (long)((int *)0 + 4);
    std::cout << a << std::endl;
}
