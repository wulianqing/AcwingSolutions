#include "0_0_bmpstruct.h"
#include <string>
#include <vector>
#include <cmath>
#define PI 3.1415926535
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

//将水印信息滚动重复到指定图像的最大嵌入容量
char* enlargeMessage(char* msg_txt,int img_capacity){
    std::string msg_txt_s = msg_txt;
    int msg_size = msg_txt_s.size();        
    int msg_bit_size = msg_size * 8;
    //嵌入信息不断重复滚动，直到达到最大容量（可防止几何切割）
    //可重复 max_embedd_capacity / msg_bit_size 次
    for (int i = 0; i < img_capacity / msg_bit_size;i++)
        msg_txt_s += msg_txt_s;
    return const_cast<char *>(msg_txt_s.c_str());
}

//dct变换：生成辅助矩阵A (参数：4或8，表示4*4 和 8*8)
std::vector<std::vector<double>> createMatrixA(int num){
    if(!(num == 4 || num == 8))
        throw "dct变换：生成辅助矩阵A (参数：4或8，表示4*4 和 8*8)";

    std::vector<std::vector<double>> matrix_a(num, std::vector<double>(num, 0));
    for (int i = 0; i < num;i++)
        for (int j = 0; j < num;j++){
            double a = 0;
            if (i == 0)
                a = sqrt((double)1 / num);
            else
                a = sqrt((double)2 / num);
            matrix_a[i][j] = a * cos(((double)j + (double)1 / 2) * i * PI / num);
        }

    return matrix_a;
}

//dct变换：通过辅助矩阵A生成A‘
std::vector<std::vector<double>> createMatrixAT(std::vector<std::vector<double>> matrix_a){
    for (int i = 0; i < matrix_a.size();i++)
        for (int j = 0; j < i;j++){
            std::swap(matrix_a[i][j], matrix_a[j][i]);
        }
    return matrix_a;
}

//dct变换：矩阵相乘
std::vector<std::vector<double>> matrixMulti(std::vector<std::vector<double>> matrix_a,std::vector<std::vector<double>> matrix_b){
    int matrix_a_height = matrix_a.size();
    int matrix_a_width = matrix_a[0].size();
    int matrix_b_height = matrix_b.size();
    int matrix_b_width = matrix_b[0].size();

    //ret matrix
    std::vector<std::vector<double>> matrix_c(matrix_a_height, std::vector<double>(matrix_b_width,0));
    for (int i = 0; i < matrix_c.size();i++)
        for (int j = 0; j < matrix_c[0].size();j++){
            double sum = 0;
            for (int k = 0; k < matrix_a_width;k++)
                sum += matrix_a[i][k] * matrix_b[k][j];
            matrix_c[i][j] = sum;
        }
    return matrix_c;
}

//执行函数
void doIt(char* img_path,char* msg_txt){
    //取得bitmap数据__data
    //图像
    
    bmp::bitbmp my_img;
    my_img.read(img_path);
    //输出image信息
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

    //计算最大嵌入容量
    int max_embeded_capacity = my_img.height / 8 * my_img.width / 8;

    //判断：水印是否超过最大嵌入容量
    if(max_embeded_capacity < strlen(msg_txt) * 8){
        std::cout << "message is too large for embedding." << std::endl;
        return;
    }

    char *enlarged_msg_txt = enlargeMessage(msg_txt,max_embeded_capacity);
    //将重复滚动的文本水印信息转化是ASCII的比特信息
    std::vector<bool> bit_msg = charStartoBit(enlarged_msg_txt);
    reverseBit(bit_msg);

    //将__data的蓝色分量转入matrix
    std::vector<std::vector<char>> blue_matrix(my_img.height, std::vector<char>(my_img.width, 0));
    for (int i = 0; i < my_img.height;i++)
        for (int j = 0; j < my_img.width;j++)
            blue_matrix[i][j] = my_img.__data[i * j].Blue;

    //遍历蓝色分量矩阵 将8*8分块做dct变换
    //8*8dct变换中 内嵌4*4

    //



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
    std::vector<std::vector<double>> m_x = {{61, 19, 50, 20}, {82, 26, 61, 45}, {89, 90, 82, 43}, {93, 59, 53, 97}};
    std::vector<std::vector<double>> m_a = createMatrixA(4);
    std::vector<std::vector<double>> m_a_t = createMatrixAT(m_a);
    std::vector<std::vector<double>> m_y = matrixMulti(matrixMulti(m_a, m_x), m_a_t);

    std::cout << "X :" << std::endl;
    for (int i = 0; i < m_x.size(); i++)
    {
        for (int j = 0; j < m_x.size();j++){
            std::cout.width(8);
            std::cout << m_x[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    
    std::cout << "A :" << std::endl;
    for (int i = 0; i < m_a.size();i++){
        for (int j = 0; j < m_a.size();j++){
            std::cout.width(8);
            std::cout << m_a[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "A' :" << std::endl;
    for (int i = 0; i < m_a_t.size();i++){
        for (int j = 0; j < m_a_t.size();j++){
            std::cout.width(8);
            std::cout << m_a_t[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    
    std::cout << "Y :" << std::endl;
    for (int i = 0; i < m_y.size();i++){
        for (int j = 0; j < m_y.size();j++){
            std::cout.width(8);
            std::cout << m_y[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}