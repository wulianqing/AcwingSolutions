#include "0_0_bmpstruct.h"
#include <string>
#include <vector>
#include <cmath>
#define PI 3.1415926535
#define BITCAPACITY 4000
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
std::string enlargeMessage(char* msg_txt,int img_capacity){
    std::string msg_ret;
    std::string msg_txt_s = msg_txt;
    int msg_size = msg_txt_s.size();        
    int msg_bit_size = msg_size * 8;
    //嵌入信息不断重复滚动，直到达到最大容量（可防止几何切割）
    //可重复 max_embedd_capacity / msg_bit_size 次
    for (int i = 0; i < img_capacity / msg_bit_size;i++)
        msg_ret += msg_txt_s;
    //return const_cast<char *>(msg_ret.c_str());
    return msg_ret;
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

//遍历蓝色分量矩阵 将8*8分块做dct变换(注意输入的矩阵的元素为char，即8位信息)
std::vector<std::vector<double>> dct_2_stage(std::vector<std::vector<double>> matrix_total){
    //matrix for return 
    //std::vector < std::vector<double>> matrix_ret(matrix_sum.size(), std::vector<double>(matrix_sum[0].size(), 1));
    int counter = 0; //只需要做最多BITCAPACITY个分块（最多嵌入BITCAPACITYbit）
    for (int i = 0; 8 * i + 7 < matrix_total.size(); i++)
        for (int j = 0; 8 * j + 7 < matrix_total[0].size();j++){
            //matrix_sum[i][j]指的是某8*8的左上角
            
            //8*8dct变换中 内嵌4*4
            std::vector<std::vector<double>> matrix_x_8(8, std::vector<double>(8, 0));//新建8*8初始矩阵
            //拷贝数据：8 * 8矩阵
            for (int k = 0; k < 8;k++)
                for (int l = 0; l < 8;l++)
                    matrix_x_8[k][l] = matrix_total[8 * i + k][8 * j + l];

            //dct一级分解：8 * 8
            //一级分解完成的矩阵:matrix_y_8
            std::vector<std::vector<double>> matrix_a_8 = createMatrixA(8);
            std::vector<std::vector<double>> matrix_a_t_8 = createMatrixAT(matrix_a_8);
            std::vector<std::vector<double>> matrix_y_8 = matrixMulti(matrixMulti(matrix_a_8, matrix_x_8), matrix_a_t_8);
                    
                
            //取 4 * 4 左上角 低频 matrix_y_8[i][j] 
            std::vector<std::vector<double>> matrix_xx_4(4, std::vector<double>(4, 0));//新建4*4初始矩阵
            //拷贝数据：4 * 4矩阵
            for (int k = 0; k < 4;k++)
                for (int l = 0; l < 4;l++)
                    matrix_xx_4[k][l] = matrix_y_8[k][l];
            
            //dct二级分解：4 * 4
            //二级分解完成的矩阵: matrix_yy_4
            std::vector<std::vector<double>> matrix_a_4 = createMatrixA(4);
            std::vector<std::vector<double>> matrix_a_t_4 = createMatrixAT(matrix_a_4);
            std::vector<std::vector<double>> matrix_yy_4 = matrixMulti(matrixMulti(matrix_a_4, matrix_xx_4), matrix_a_t_4);
            
            //4*4写入8*8左上角 matrix_xx_4 -> matrix_y_8
            for (int k = 0; k < 4;k++)
                for (int l = 0; l < 4;l++)
                    matrix_y_8[k][l] = matrix_xx_4[k][l];

            //8*8分块写回总矩阵 matrix_y_8 -> matrix_sum
            for (int k = 0; k < 8;k++)
                for (int l = 0; l < 8;l++)
                    matrix_total[8 * i + k][8 * j + l] = matrix_x_8[k][l];

            counter++;
            if(counter % 100 == 0)
                std::cout << "decomposed block: " << counter << std::endl;
            if (counter == BITCAPACITY)
                return matrix_total;
        }
    return matrix_total;
}

//嵌入信息：遍历前4000个8*8分块，取左上4*4中LH,HL,HH三个2*2的分块，分别称为b2,b3,b4
//计算Eb2,Eb3,Eb4
//排序 -> 引用E1 > E2 > E3
//根据嵌入信息，算E2偏移值(可写成函数)
//改变E2对应2*2矩阵的值
std::vector<std::vector<double>> embedMessage(std::vector<std::vector<double>> matrix_total){
    
    //遍历前BITCAPACITY个8*8矩阵，取左上4*4中的LH,HL,HH三个2*2的分块，分别称为b2,b3,b4
    int counter = 0;
    for (int i = 0; 8 * i + 7 < matrix_total.size(); i++){
        for (int j = 0; 8 * j + 7 < matrix_total[0].size();j++){
            //只嵌入前BITCAPACITY个分块
            if(counter == BITCAPACITY)
                break;
            
            //初始矩阵
            std::vector<std::vector<double>> b2(2, std::vector<double>(2, 0));
            std::vector<std::vector<double>> b3(2, std::vector<double>(2, 0));
            std::vector<std::vector<double>> b4(2, std::vector<double>(2, 0));

            //2*2分块均值：Eb2~Eb4
            double Eb2 = 0, Eb3 = 0, Eb4 = 0;
            
            //拷贝至3个2*2矩阵
            for (int k = 0; k < 2;k++)
                for (int l = 0; l < 2;l++){
                    b2[k][l] = matrix_total[8 * i + k][8 * j + 2 + l];
                    b3[k][l] = matrix_total[8 * i + 2 + k][8 * j + l];
                    b4[k][l] = matrix_total[8 * i + 2 + k][8 * j + 2 + l];
                    Eb2 += b2[k][l];
                    Eb3 += b3[k][l];
                    Eb4 += b4[k][l];
                }
            Eb2 /= 4;
            Eb3 /= 4;
            Eb4 /= 4;

            //排序
        }
        if(counter == BITCAPACITY)
            break;
    }
}






//执行函数
void doIt(char* img_path,char* msg_txt){
    //取得bitmap数据__data
    bmp::bitbmp my_img;
    my_img.read(img_path);
    //输出image信息
    std::cout << "image height: " << my_img.height << std::endl
              << "image width: " << my_img.width << std::endl
              << "image bits: " << my_img.info.biBitCount << std::endl;
    
    //水印信息(图像)
    /*
    bmp::bitbmp my_msg_bmp;
    my_msg_bmp.read("/Users/wubaobao/GoogleCloud-aaedu/Dropbox/ProjectCodeFolder/VSCode/AcwingSolutions/image/oldmanjourney.bmp");
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

    //最多嵌入BITCAPACITYbit，500Byte 500个char
    std::string enlarged_msg_txt = enlargeMessage(msg_txt,std::min(max_embeded_capacity,BITCAPACITY));
    char *c_enlarged_msg_txt = const_cast<char *>(enlarged_msg_txt.c_str());
    //test msg
    std::cout << "massage: " << msg_txt << std::endl;
    //std::cout << "enlarged message: " << enlarged_msg_txt << std::endl;

    //将重复滚动的文本水印信息转化是ASCII的比特信息
    std::vector<bool> bit_msg = charStartoBit(c_enlarged_msg_txt);
    reverseBit(bit_msg);

    //将__data的蓝色分量转入matrix
    std::vector<std::vector<double>> blue_matrix(my_img.height, std::vector<double>(my_img.width, 0));
    for (int i = 0; i < my_img.height;i++){
        for (int j = 0; j < my_img.width;j++){
            blue_matrix[i][j] = (double)my_img.__data[i * j].Blue;
            //std::cout << blue_matrix[i][j] << " ";
        }
        //std::cout << std::endl;
    }

    //dct: vector<vector<char>>  ->  vector<vector<double>>
    std::vector<std::vector<double>> dct_matrix_blue = dct_2_stage(blue_matrix);

    std::ofstream outfile("/Users/wubaobao/Desktop/test_outfile.txt");
    for (int i = 0; i < dct_matrix_blue.size();i++){
        for (int j = 0; j < dct_matrix_blue[0].size();j++){
            outfile.width(8);
            outfile << dct_matrix_blue[i][j] << " ";
        }
        outfile << std::endl;
    }
    outfile.close();
    

    //my_img.save("/Users/wubaobao/GoogleCloud-aaedu/Dropbox/ProjectCodeFolder/VSCode/AcwingSolutions/image/test.bmp");
}



int main(){
    //读图像 读文本
    char *img_path = "/Users/wubaobao/GoogleCloud-aaedu/Dropbox/ProjectCodeFolder/VSCode/AcwingSolutions/image/lena.bmp";
    char *msg_txt = "To me, you are still nothing more than a little boy who is just like a hundred thousand other little boys. And I have no need of you. And you, on your part, have no need of me. To you, I am nothing more than a fox like a hundred thousand other foxes. But if you tame me, then we shall need each other. To me, you will be unique in all the world. To you, I shall be unique in all the world";
    //To me, you are still nothing more than a little boy who is just like a hundred thousand other little boys. And I have no need of you. And you, on your part, have no need of me. To you, I am nothing more than a fox like a hundred thousand other foxes. But if you tame me, then we shall need each other. To me, you will be unique in all the world. To you, I shall be unique in all the world
    //std::cout << "输入图像路径 和 嵌入文本: " << std::endl;
    //std::cin >> img_path >> msg_txt;
    doIt(img_path, msg_txt);

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

    /* 测试dct变换
    //std::vector<std::vector<double>> m_x = {{61, 19, 50, 20}, {82, 26, 61, 45}, {89, 90, 82, 43}, {93, 59, 53, 97}};
    std::vector<std::vector<double>> m_x = 
        {{61,19,50,20,44,144,255,13},
        {82,26,61,45,28,43,233,41},
        {89,90,82,43,173,75,21,90},
        {93,59,53,97,23,43,86,54},
        {161,49,50,20,44,14,55,13},
        {182,56,61,47,8,43,33,41},
        {189,90,65,43,73,175,21,90},
        {193,59,53,97,23,43,86,54}};
    std::vector<std::vector<double>> m_a = createMatrixA(8);
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
    */

}