#include "0_0_bmpstruct.h"
#include<string>
#include<vector>

//把嵌入信息char*转化为ASCII的比特信息(每个ASCII码8bit)
std::vector<bool> charStartoBit(char *msg) {
    std::string s = msg;
    int msg_size = s.size();
    std::vector<bool> bit_msg(msg_size * 8);
    for (int i = 0; i < msg_size;i++)
    {
        for (int j = 0; j < 8;j++)
        {
            bit_msg[8 * i + j] = s[i] & 1;
            s[i] >>= 1;
        }
    }
    return bit_msg;
}

//ASCII比特信息是按从低位到高位存储的 需要做翻转
std::vector<bool> &  reverseBit(std::vector<bool> & bit_msg){
    reverse(bit_msg.begin(), bit_msg.end());
    return bit_msg;
}

//

void doIt(char* img_path,char* msg_txt){
    //取得bitmap数据__data
    //图像
    
    bmp::bitbmp my_img;
    my_img.read(img_path);
    std::cout << "image height: " << my_img.height << std::endl
              << "image width: " << my_img.width << std::endl
              << "image bits: " << my_img.info.biBitCount << std::endl;
    
    //水印信息(图像)
    /*
    bmp::bitbmp my_msg_bmp;
    my_msg_bmp.read("/Users/wubaobao/GoogleCloud-aaedu/Dropbox/ProjectCodeFolder/VSCode/AcwingSolutions/image/t.bmp");
    std::cout << "image height: " << my_msg_bmp.height << std::endl
              << "image width: " << my_msg_bmp.width << std::endl
              << "image bits: " << my_msg_bmp.info.biBitCount << std::endl;
    */

    std::string msg_txt_s = msg_txt;
    int msg_size = msg_txt_s.size();        
    int msg_bit_size = msg_size * 8;
    std::cout << "message size: " << msg_size << std::endl
              << "bits of message: " << msg_bit_size << std::endl;

    //计算最大嵌入容量
    int max_embedd_capacity = my_img.height / 8 * my_img.width / 8;

    //判断水印是否超过最大嵌入容量
    if(max_embedd_capacity < msg_bit_size){
        std::cout << "message is too large for embedding." << std::endl;
        return;
    }

    //嵌入信息不断重复滚动，直到达到最大容量（可防止几何切割）
    //可重复 max_embedd_capacity / msg_bit_size 次
    for (int i = 0; i < max_embedd_capacity / msg_bit_size;i++)
        msg_txt_s += msg_txt_s;

    int repeated_msg_txt_size = msg_txt_s.size();
    std::cout << "repeated message size: " << repeated_msg_txt_size * 8 << std::endl;

    //将重复滚动的文本水印信息转化是ASCII的比特信息
    std::vector<bool> bit_msg = charStartoBit(const_cast<char*>(msg_txt_s.c_str()));
    reverseBit(bit_msg);

    //将__data的蓝色分量转入matrix
    std::vector<std::vector<char>> blue_matrix(my_img.height, std::vector<char>(my_img.width, 0));
    for (int i = 0; i < my_img.height;i++)
        for (int j = 0; j < my_img.width;j++)
            blue_matrix[i][j] = my_img.__data[i * j].Blue;

    //计算分块的定位点（分块大小8*8，定位点为每个分块的左上角像素）
    int y_block_locator = my_img.height / 8;
    int x_block_locator = my_img.width / 8;
    //分块定位表 
    /*
    std::vector<std::vector<std::pair<int,int>>> block_locator(y_block_locator,std::vector<std::pair<int,int>>(x_block_locator,0));
    for (int i = 0; i < y_block_locator;i++)
        for (int j = 0; j < x_block_locator;j++)
            block_locator[i][j] = std::make_pair(8 * i, 8 * j);
    */


    my_img.save("/Users/wubaobao/GoogleCloud-aaedu/Dropbox/ProjectCodeFolder/VSCode/AcwingSolutions/image/test.bmp");
    
}



int main(){
    //char *img_path = "/Users/wubaobao/GoogleCloud-aaedu/Dropbox/ProjectCodeFolder/VSCode/AcwingSolutions/image/oldmanjourney.bmp";
    //char *msg_txt = "To me, you are still nothing more than a little boy who is just like a hundred thousand other little boys. And I have no need of you. And you, on your part, have no need of me. To you, I am nothing more than a fox like a hundred thousand other foxes. But if you tame me, then we shall need each other. To me, you will be unique in all the world. To you, I shall be unique in all the world";
    //std::cout << "输入图像路径 和 嵌入文本: " << std::endl;
    //std::cin >> img_path >> msg_txt;
    //doIt(img_path, msg_txt);

    /* 测试将字符串 -> ASCII的比特信息
    char *msg = "hello";
    std::vector<bool> bit_msg = charStartoBit(msg);
    reverseBit(bit_msg);
    for (int i = 0; i < bit_msg.size(); i++)
    {
        std::cout << bit_msg[i] << ' ';
        if((i + 1) % 8 == 0)
            std::cout << std::endl;
    }
    */
    return 0;
}