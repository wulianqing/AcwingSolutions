#include<iostream>
#include<memory>

int main() {
    auto sp1 = std::make_shared<int>(5);
    std::cout << "before sp1 size: " << sizeof(sp1) << std::endl;
    auto sp2 = sp1;
    int *ip1 = new int(5);
    //sp1,sp2大小应该都是16 Byte，64bit电脑，指针为8 Btye,shared_ptr需要一个裸指针，还需要一个指向引用计数器的指针
    std::cout << "sp1 size: " << sizeof(sp1) << std::endl
              << "sp2 size: " << sizeof(sp2) << std::endl
              << "pointer size: " << sizeof(ip1) << std::endl;

    return 0;
}