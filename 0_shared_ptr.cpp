#include<iostream>
#include<memory>

int main() {
    //new一次，make_shared就是解决new两次的问题的
    auto sp1 = std::make_shared<int>(5);
    std::cout << "before sp1 size: " << sizeof(sp1) << std::endl;
    
    //new两次
    auto sp2 = std::shared_ptr<int>(new int(5));

    
    auto sp3 = sp1;
    int *ip1 = new int(5);
    //sp1,sp2大小应该都是16 Byte，64bit电脑，指针为8 Btye,
    // ！！！ 原因：shared_ptr需要一个裸指针，还需要一个指向引用计数器的指针
    std::cout << "sp1 size: " << sizeof(sp1) << std::endl
              << "sp2 size: " << sizeof(sp3) << std::endl
              << "pointer size: " << sizeof(ip1) << std::endl;

    return 0;
}